// Sudoku puzzle verifier and solver

//to compile: use following commands:
//rm -f sudoku
//gcc -Wall -Wextra sudoku.c -o sudoku
//./sudoku puzzle2-invalid.txt

#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//global mutex
pthread_mutex_t g_mutex;

//function for getting square root of a number
int int_sqrt(int n) { 
  int x = n;
  int y = (x + 1) / 2;
  while (y < x) {
      x = y;
      y = (x + n / x) / 2;
  }
  return x;
}

/* structure for passing data to threads */
typedef struct {
  int psize;
  int **grid; 
  int *result; // 0 = invalid, 1 = valid, 2 = incomplete
} parameters;

typedef struct {
  int psize;
  int squareNum;
  int **grid; 
  int *result;
  int squareX; //start of the sub section of the square's x
  int squareY; //start of the sub section of the square's y
} parametersHelper;

//helper function to check a square section of the puzzle
void* checkInSquareSect(void* arg){
  parametersHelper* param = (parametersHelper*)arg;
  //generate a bool list the size of psize 
  bool* allNums = malloc((param->psize + 1) * sizeof(bool));

  if (allNums == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }

  // Set all values to false
  for (int i = 0; i <= param->psize; i++) {
    allNums[i] = false;
  }

  //do a double nested forloop to check each coordinate of the square
  //if there is a 0, then abort with result as incomplete(2)
  for (int x = param->squareX; x < param->squareX + param->squareNum; x++){
    for (int y = param->squareY; y < param->squareY + param->squareNum; y++){
      int noAtGrid = param->grid[x][y];
      if (noAtGrid == 0){ //is incomplete
        pthread_mutex_lock(&g_mutex);
        *param->result = 2;
        pthread_mutex_unlock(&g_mutex);
        return NULL;
      }

      if ((noAtGrid < 1 || noAtGrid > param->psize) && *param->result != 2) {
        pthread_mutex_lock(&g_mutex);
        *param->result = 0; // invalid number in the puzzle, less than 1 or greater than psize
        pthread_mutex_unlock(&g_mutex);
        free(allNums);
        return NULL;
      }
      
      allNums[noAtGrid] = true;
    }
  }

  //check if any of the values in allNums is false. if there is false, return as invalid solution (1)
  for (int i = 1; i <= param->psize; i++){
    if (!allNums[i] && *param->result != 2){
      //if one of the number is not present, it is invalid
      pthread_mutex_lock(&g_mutex);
      *param->result = 0; 
      pthread_mutex_unlock(&g_mutex);
    }
  }
  //reach here with result untouched if valid. result is set to 1 on its initializaton

  return NULL;
}

//helper function checks in a 3x3 square
void* checkInSquare(void* arg){
  parameters* param = (parameters*)arg;
  //decide amount of loops it needs to make to check every square sect
  int squareNum; 
  squareNum = int_sqrt(param->psize);

  pthread_t threads[param->psize];
  parametersHelper* paramHelp[param->psize];

  //nested loop through each section of the square
  for (int x = 1; x <= squareNum; x++)
  {
    for (int y = 1; y <= squareNum; y++)
    {
      int index = (x - 1) * squareNum + (y - 1);
      //make a thread to check the section
      //squareX is x*squareNum + 1
      //squareY is y*squareNum + 1
      paramHelp[index] = malloc(sizeof(parametersHelper));
      paramHelp[index]->grid = param->grid;
      paramHelp[index]->psize = param->psize;
      paramHelp[index]->result = param->result;
      paramHelp[index]->squareNum = squareNum;
      paramHelp[index]->squareX = (x - 1) * squareNum + 1;
      paramHelp[index]->squareY = (y - 1) * squareNum + 1;
      //make thread to check that section
      pthread_create(&threads[index], NULL, checkInSquareSect, paramHelp[index]);
      
    }
  }
  //join all threads
  for (int i = 0; i < param->psize; i++){
    pthread_join(threads[i], NULL);
    free(paramHelp[i]);
  }

  return NULL;
}

//helper function to check a horizontal section of the puzzle
void* checkInHorizSect(void* arg){
  parametersHelper* param = (parametersHelper*)arg;
  //generate a bool list the size of psize 
  bool* allNums = malloc((param->psize + 1) * sizeof(bool));

  if (allNums == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }

  // Set all values to false
  for (int i = 0; i <= param->psize; i++) {
    allNums[i] = false;
  }

  //do a forloop to check each coordinate of the square
  //if there is a 0, then abort with result as incomplete(2)
  for (int x = 1; x <= param->psize; x++)
  {
    int noAtGrid = param->grid[x][param->squareY];
      if (noAtGrid == 0){ //is incomplete
        pthread_mutex_lock(&g_mutex);
        *param->result = 2; 
        pthread_mutex_unlock(&g_mutex);
        return NULL;
      }

      if (noAtGrid < 1 || noAtGrid > param->psize) {
        pthread_mutex_lock(&g_mutex);
        *param->result = 0; // invalid number in the puzzle, less than 1 or greater than psize
        pthread_mutex_unlock(&g_mutex);
        free(allNums);
        return NULL;
      }
      
      allNums[noAtGrid] = true;
  }

  //check if any of the values in allNums is false. if there is false, return as invalid solution (1)
  for (int i = 1; i <= param->psize; i++){
    if (!allNums[i]){
      //if one of the number is not present, it is invalid
      pthread_mutex_lock(&g_mutex);
      *param->result = 0; 
      pthread_mutex_unlock(&g_mutex);
    }
  }
  //reach here with result untouched if valid. result is set to 1 on its initializaton

  return NULL;
}

//helper function checks in a horizontal line
void* checkInHorizontal(void* arg){
  parameters* param = (parameters*)arg;

  pthread_t threads[param->psize];
  parametersHelper* paramHelp[param->psize];
  //loop through each y axis
  for (int y = 1; y <= param->psize; y++){
    //make a thread to the helper function that checks the horizontal row
    //squareX is 1
    //squareY is y
    //make a thread to check the section
    int index = y - 1;
      paramHelp[index] = malloc(sizeof(parametersHelper));
      paramHelp[index]->grid = param->grid;
      paramHelp[index]->psize = param->psize;
      paramHelp[index]->result = param->result;
      paramHelp[index]->squareNum = 0;
      paramHelp[index]->squareX = 1;
      paramHelp[index]->squareY = y;
      //make thread to check that section
      pthread_create(&threads[index], NULL, checkInHorizSect, paramHelp[index]);

  }

  //join all threads
  for (int i = 0; i < param->psize; i++){
    pthread_join(threads[i], NULL);
    free(paramHelp[i]);
  }

  return NULL;
}

//helper function to check a vertical section of the puzzle
void* checkInVertSect(void* arg){
  parametersHelper* param = (parametersHelper*)arg;
  //generate a bool list the size of psize 
  bool* allNums = malloc((param->psize + 1) * sizeof(bool));

  if (allNums == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }

  // Set all values to false
  for (int i = 0; i <= param->psize; i++) {
    allNums[i] = false;
  }

  //do a forloop to check each coordinate of the square
  //if there is a 0, then abort with result as incomplete(2)
  for (int y = 1; y <= param->psize; y++)
  {
    int noAtGrid = param->grid[param->squareX][y];
      if (noAtGrid == 0){ //is incomplete
        pthread_mutex_lock(&g_mutex);
        *param->result = 2; 
        pthread_mutex_unlock(&g_mutex);
        return NULL;
      }

      if (noAtGrid < 1 || noAtGrid > param->psize) {
        pthread_mutex_lock(&g_mutex);
        *param->result = 0; // invalid number in the puzzle, less than 1 or greater than psize
        pthread_mutex_unlock(&g_mutex);
        free(allNums);
        return NULL;
      }
      
      allNums[noAtGrid] = true;
  }

  //check if any of the values in allNums is false. if there is false, return as invalid solution (1)
  for (int i = 1; i <= param->psize; i++){
    if (!allNums[i]){
      //if one of the number is not present, it is invalid
      pthread_mutex_lock(&g_mutex);
      *param->result = 0; 
      pthread_mutex_unlock(&g_mutex);
    }
  }
  //reach here with result untouched if valid. result is set to 1 on its initializaton

  return NULL;
}

//helper function checks in a vertical line
void* checkInVertical(void* arg){
  parameters* param = (parameters*)arg;

  pthread_t threads[param->psize];
  parametersHelper* paramHelp[param->psize];
  //loop through each y axis
  for (int x = 1; x <= param->psize; x++){
    //make a thread to the helper function that checks the vertical column
    //squareX is x
    //squareY is 1
    int index = x - 1;
    paramHelp[index] = malloc(sizeof(parametersHelper));
    paramHelp[index]->grid = param->grid;
    paramHelp[index]->psize = param->psize;
    paramHelp[index]->result = param->result;
    paramHelp[index]->squareNum = 0;
    paramHelp[index]->squareX = x;
    paramHelp[index]->squareY = 1;
    //make thread to check that section
    pthread_create(&threads[index], NULL, checkInVertSect, paramHelp[index]);
  }
  //join all threads
  for (int i = 0; i < param->psize; i++){
    pthread_join(threads[i], NULL);
    free(paramHelp[i]);
  }

  return NULL;

}

// takes puzzle size and grid[][] representing sudoku puzzle
// and two booleans to be assigned: complete and valid.
// row-0 and column-0 is ignored for convenience, so a 9x9 puzzle
// has grid[1][1] as the top-left element and grid[9]9] as bottom right
// A puzzle is complete if it can be completed with no 0s in it
// If complete, a puzzle is valid if all rows/columns/boxes have numbers from 1
// to psize For incomplete puzzles, we cannot say anything about validity
void checkPuzzle(int psize, int **grid, bool *complete, bool *valid) {
  // YOUR CODE GOES HERE and in HELPER FUNCTIONS
  //thread prep
  pthread_t threadSquares, threadVert, threadHoriz;
  parameters* paramSquare = malloc(sizeof(parameters));
  paramSquare->grid = grid;
  paramSquare->psize = psize;
  int resultSquare = 1;
  paramSquare->result = &resultSquare;
  parameters* paramVert = malloc(sizeof(parameters));
  paramVert->grid = grid;
  paramVert->psize = psize;
  int resultVert = 1;
  paramVert->result = &resultVert;
  parameters* paramHoriz = malloc(sizeof(parameters));
  paramHoriz->grid = grid;
  paramHoriz->psize = psize;
  int resultHoriz = 1;
  paramHoriz->result = &resultHoriz;

  pthread_mutex_init(&g_mutex, NULL);

  //make a thread to check the squares
  pthread_create(&threadSquares, NULL, checkInSquare, paramSquare);
  //make a thread to check horizontally if valid
  pthread_create(&threadHoriz, NULL, checkInHorizontal, paramHoriz);
  //make a thread to check vertically if valid
  pthread_create(&threadVert, NULL, checkInVertical, paramVert);
  
  //join all threads
  pthread_join(threadSquares, NULL);
  pthread_join(threadVert, NULL);
  pthread_join(threadHoriz, NULL);

  //set valid and complete based on result (1 is valid, 0 is invalid, 2 is incomplete)
  if (resultSquare == 1 && resultHoriz == 1 && resultVert == 1)
  {
    // is valid
    *valid = true;
    *complete = true;
  } else if(resultSquare == 2 || resultHoriz == 2 || resultVert == 2){
    // is incomplete
    *valid = false;
    *complete = false;
  } else{
    // is invalid, not all 1 and no 2
    *valid = false;
    *complete = true;
  }
  
  free(paramSquare);
  free(paramHoriz);
  free(paramVert);
}

// takes filename and pointer to grid[][]
// returns size of Sudoku puzzle and fills grid
int readSudokuPuzzle(char *filename, int ***grid) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Could not open file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  int psize;
  fscanf(fp, "%d", &psize);
  int **agrid = (int **)malloc((psize + 1) * sizeof(int *));
  for (int row = 1; row <= psize; row++) {
    agrid[row] = (int *)malloc((psize + 1) * sizeof(int));
    for (int col = 1; col <= psize; col++) {
      fscanf(fp, "%d", &agrid[row][col]);
    }
  }
  fclose(fp);
  *grid = agrid;
  return psize;
}

// takes puzzle size and grid[][]
// prints the puzzle
void printSudokuPuzzle(int psize, int **grid) {
  printf("%d\n", psize);
  for (int row = 1; row <= psize; row++) {
    for (int col = 1; col <= psize; col++) {
      printf("%d ", grid[row][col]);
    }
    printf("\n");
  }
  printf("\n");
}

// takes puzzle size and grid[][]
// frees the memory allocated
void deleteSudokuPuzzle(int psize, int **grid) {
  for (int row = 1; row <= psize; row++) {
    free(grid[row]);
  }
  free(grid);
}

// expects file name of the puzzle as argument in command line
int main(int argc, char **argv) {
  if (argc != 2) {
    printf("usage: ./sudoku puzzle.txt\n");
    return EXIT_FAILURE;
  }
  // grid is a 2D array
  int **grid = NULL;
  // find grid size and fill grid
  int sudokuSize = readSudokuPuzzle(argv[1], &grid);
  bool valid = false;
  bool complete = false;
  checkPuzzle(sudokuSize, grid, &complete, &valid);
  printf("Complete puzzle? ");
  printf(complete ? "true\n" : "false\n");
  if (complete) {
    printf("Valid puzzle? ");
    printf(valid ? "true\n" : "false\n");
  }
  printSudokuPuzzle(sudokuSize, grid);
  deleteSudokuPuzzle(sudokuSize, grid);
  return EXIT_SUCCESS;
}