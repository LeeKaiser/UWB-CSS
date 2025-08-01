#ifndef SHELL_H
#define SHELL_H

#include <assert.h>  // assert
#include <fcntl.h>   // O_RDWR, O_CREAT
#include <stdbool.h> // bool
#include <stdio.h>   // printf, getline
#include <stdlib.h>  // calloc
#include <string.h>  // strcmp
#include <unistd.h>  // execvp
#include <sys/wait.h>   //wait

#define MAXLINE 80
#define PROMPT "osh> "

#define RD 0
#define WR 1

bool equal(char *a, char *b);
int fetchline(char **line);
int interactiveShell();
int runTests();
void processLine(char *line);
int main();

//funcs for the project
int child(char **args);
void doCommand(char **args, int start, int end, bool waitfor);
int doPipe(char **args, int pipei);
bool parse(char **args, int start, int *end);
char **tokenize(char *line);




#endif