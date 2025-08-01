#include "task.h"
#include "cpu.h"
#include "list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

// add a task to the list 
void add(char *name, int priority, int burst);

// invoke the scheduler
void schedule();
