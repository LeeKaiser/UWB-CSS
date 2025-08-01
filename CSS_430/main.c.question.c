#include <assert.h>  // assert
#include <fcntl.h>   // O_RDWR, O_CREAT
#include <stdbool.h> // bool
#include <stdio.h>   // printf, getline
#include <stdlib.h>  // calloc
#include <string.h>  // strcmp
#include <unistd.h>  // execvp
#include <wait.h>    // wait

#define MAXLINE 256

bool equal(char *a, char *b) 
{
    return strcmp(a,b) == 0;
}

int fetchline(char **line)
{
    size_t len = MAXLINE;
    int n = getline (line, &len, stdin);
    if (n>0){
        (*line) [n-1] = '\0';
    }
    return n;
}

void capitalize(char *line)
{
    for (int i = 0; line[i] != '\0'; i++)
    {
        line[i] = line[i] + ('A' - 'a');
    }
}

void parrot()
{
  char *line = calloc(MAXLINE, sizeof(char));
  while (true)
  {
    printf("parrot> ");
    fflush(stdout);
    int n = fetchline(&line);
    // ^D results in n = -1
    if (n < 0 || equal(line, "exit"))
    {
      break;
    }
    if (equal(line, ""))
    {
      continue;
    }
    capitalize(line);
    printf("%s\n", line);
  }
  free(line);
}

int main()
{
  parrot();
  exit(EXIT_SUCCESS);
}