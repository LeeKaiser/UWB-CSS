#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int MEMSIZE = 80;
int LINESIZE = 100;
char FREE = '.';

// start end of a segment
typedef struct { int s, e; } PAIR;

void doAlloc(char* mem, char name, int size, char algo);
PAIR* doAllocBest(char* mem, int size);
PAIR* doAllocFirst(char* mem, int size);
PAIR* doAllocWorst(char* mem, int size);
void doCommand(char* mem, char* cmd);
void doCompact(char* mem);
void doRead(char* mem, char* name);
void doShow(char* mem);
void stomp(char* mem, char name, int start, int size);
void doFree(char* mem, char name);