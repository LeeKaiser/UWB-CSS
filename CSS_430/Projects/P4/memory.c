// ============================================================================
// Memo.c : simulation of a memory allocator
// ============================================================================

#include "memory.h"

// ============================================================================
// Allocate memory from the pool: 'size' bytes for process 'name', using
// algorithm 'algo'.  For example: A B 25 F
// ============================================================================
void doAlloc(char* mem, char name, int size, char algo) {
  PAIR* pair = NULL;                            // winning pair
  if (algo == 'F') {                            // First fit
    pair = doAllocFirst(mem, size);
  } else if (algo == 'B') {
    pair = doAllocBest(mem, size);              // Best fit
  } else if (algo == 'W') {
    pair = doAllocWorst(mem, size);             // Worst fit
  } 
  
  if (pair) {
    stomp(mem, name, pair->s, size);            // grab that memory
    free(pair);
  } else {
    printf("Cannot find %d free bytes \n", size);
  }
}

//occupy space
void stomp(char* mem, char name, int start, int size){
  for (int i = start; i < start + size; i++)
  {
    mem[i] = name;
  }
}

// ============================================================================
// Find a big enough hole in 'mem', for 'size' bytes, using Best-Fit
// ============================================================================
PAIR* doAllocBest(char* mem, int size) {
  //go through memory and find the minimal space that still fits
  //the best candidate for index start
  int indexBest = -1;
  int countBest = 0;
  //current index start
  int indexStart = -1; //start of free space
  int count = 0; //size of free space

  //loop through list
  for (int i = 0; i < MEMSIZE; i++) {
    //if free, start recording new index candidate
    if (mem[i] == FREE) {
      //mark start of free
      if (indexStart == -1) {
        indexStart = i; 
      }
      //count up
      count++;
    } else {
      //check if the indexStart is good for indexBest
      if (countBest == 0 & count >= size){ //if no previous free section and it is larger than size
        indexBest = indexStart;
        countBest = count;
      } else if (count < countBest && count >= size){ //if it is better candidate
        indexBest = indexStart;
        countBest = count;
      }
      // Reset and search again
      indexStart = -1;
      count = 0;
    }
  }
  //set size outside of loop if nessecary
  if (countBest == 0 && count >= size){ //if no previous free section and it is larger than size
    indexBest = indexStart;
    countBest = count;
  } else if (count < countBest && count >= size){ //if it is better candidate
    indexBest = indexStart;
    countBest = count;
  }

  if (indexBest == -1 && countBest == 0)
  { //no candidate found
    return NULL;
  } else {
    PAIR* ret = (PAIR*) malloc(sizeof(PAIR));
    ret->s = indexBest;
    ret->e = indexBest + size - 1;
    return ret;
  }
}


// ============================================================================
// Find a big enough hole in 'mem', for 'size' bytes, using the First-Fit
// ============================================================================
PAIR* doAllocFirst(char* mem, int size) {
  //go through memory and find the first free big enough to fit
  int indexStart = -1; //start of free space
  int count = 0; //size of free space

  for (int i = 0; i < MEMSIZE; i++) {
    //if at free
    if (mem[i] == FREE) {
      //mark start of free
      if (indexStart == -1) {
        indexStart = i; 
      }
      //count up
      count++;
      //return if count is complete
      if (count == size) {
        PAIR* ret = (PAIR*) malloc(sizeof(PAIR));
        ret->s = indexStart;
        ret->e = indexStart + size - 1;
        return ret;
      }
    } else {
      // Reset and search again
      indexStart = -1;
      count = 0;
    }
  }

  // No suitable block found
  return NULL;
  
}

// ============================================================================
// Find a big enough hole in 'mem', for 'size' bytes, using Worst-Fit
// ============================================================================
PAIR* doAllocWorst(char* mem, int size) {
  //go through entire memory and find the largest space
  //the worst candidate for index start
  int indexWorst = -1;
  int countWorst = 0;
  //current index start
  int indexStart = -1; //start of free space
  int count = 0; //size of free space

  //loop through list
  for (int i = 0; i < MEMSIZE; i++) {
    //if free, start recording new index candidate
    if (mem[i] == FREE) {
      //mark start of free
      if (indexStart == -1) {
        indexStart = i; 
      }
      //count up
      count++;
    } else {
      //check if the indexStart is good for indexWorst 
      if (count > countWorst && count >= size)
      {
        indexWorst = indexStart;
        countWorst = count;
      }
      // Reset and search again
      indexStart = -1;
      count = 0;
    }
  }
  //set size outside of loop if nessecary
  //check if the indexStart is good for indexWorst 
  if (count > countWorst && count >= size)
  {
    indexWorst = indexStart;
    countWorst = count;
  }

  if (indexWorst == -1 && countWorst == 0)
  { //no candidate found
    return NULL;
  } else {
    PAIR* ret = (PAIR*) malloc(sizeof(PAIR));
    ret->s = indexWorst;
    ret->e = indexWorst + size - 1;
    return ret;
  }
}

// ============================================================================
// free memory used by owner indicated by name
// ============================================================================
void doFree(char* mem, char name){
  for (int i = 0; i < MEMSIZE; i++){
    if (mem[i] == name){
      mem[i] = FREE;
    }
  }
}

// ============================================================================
// Execute the user's command.  For example: A B 20 F
// ============================================================================
void doCommand(char* mem, char* cmd) {
  char* op = strtok(cmd, " \t");

  switch(*op) {
    case 'A': // Allocate
      char *nameStr = strtok(NULL, " \t");
      char *sizeStr = strtok(NULL, " \t");
      char *algoStr = strtok(NULL, " \t");

      if (!nameStr || !sizeStr || !algoStr) {
        printf("Error: Invalid allocate format\n");
        return;
      }

      char name = toupper(nameStr[0]);
      int size = atoi(sizeStr);
      char algo = toupper(algoStr[0]);

      doAlloc(mem, name, size, algo);    
      break;
    
    case 'F': // Free
      char* pname = strtok(NULL, " \t"); 
      if (!nameStr) {
        printf("Error: Missing name for Free\n");
        return;
      }
      name = toupper(pname[0]);
      doFree(mem, name);
      break;

    case 'S': // Show
      doShow(mem);          
      break;

    case 'C': // Compact
      doCompact(mem);       
      break;
    
    case 'R': // Read
      char* filename = strtok(NULL, " \t\n");
      if (!filename) {
        printf("Error: Missing file name for read\n");
        return;
      }
      doRead(mem, filename);     
      break;

    case 'E': // exit
      memset(mem, FREE, MEMSIZE);
      exit(0);             
      break;
  }
}



// ============================================================================
// Compact the memory pool: slide all allocations to the 'left', keeping the
// free memory on the 'right'
// ============================================================================
void doCompact(char* mem) {
  int writeIndex = 0;

  for (int i = 0; i < MEMSIZE; i++){
    if (mem[i] != FREE)
    {
      if (writeIndex != i)
      {
        mem[writeIndex] = mem[i];
        mem[i] = FREE;
      }
      writeIndex++;
    }
  }
}

// ============================================================================
// Open the file called 'filename' and execute each command in that script.
// Any line start with a # is treated as a comment, and skipped
// ============================================================================
void doRead(char* mem, char* filename) {
  FILE *in= fopen(filename,"r");
  char task[LINESIZE];
  //in  //open file
  //when file fails to open
  if (!in) {
    printf("Error: File not found: %s.", filename);
    return;
  }

  //if file is present
  while (fgets(task,LINESIZE,in) != NULL) {
    doCommand(mem, task);
  }

  fclose(in);
}


// ============================================================================
// Show the memory layout.  For example:
//    AAABB....CCCCCC..DDDDDEE.FFF.......GGGGGGGH........II.JJJJJJJJJ.....
// ============================================================================
void doShow(char* mem) {
  for (int i = 0; i < MEMSIZE; i++) {
  printf("%c", mem[i]);
  }
  printf("\n");
}

// ============================================================================
// Main function - driver for the "memo" allocator
// ============================================================================
int main() {
  char mem[MEMSIZE];  
  memset(mem, FREE, MEMSIZE); // prepare the mem by setting FREE
  
  while (1) {
    printf("Memo> ");
    char cmd[LINESIZE];
    fgets(cmd, sizeof(cmd), stdin);
    doCommand(mem, cmd);
  }
}


