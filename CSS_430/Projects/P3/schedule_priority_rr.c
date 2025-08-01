#include "schedulers.h"

int taskCount = 0; //amount of task present

struct node *g_head; //head of list

// add a task to the list 
void add(char *name, int priority, int burst){
    //make task object
    struct task *newTask = malloc(sizeof(struct task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = taskCount;
    taskCount++;
    //insert to list
    insert(&g_head, newTask);
}


// based on traverse from list.c
// finds the task whose name comes first in dictionary
Task *pickNextTask() {
  // if list is empty, nothing to do
  if (!g_head)
    return NULL;

  struct node *temp;
  temp = g_head;
  Task *best_sofar = temp->task;
    //for priority round robin, select highest priority task in list and increase prioirty in the rest
  while (temp != NULL) {
    //if the next task has greater priority, set best so far to it
    if (best_sofar->priority < 10){
        temp->task->priority += 1;
    }
    if (temp->task->priority > best_sofar->priority) {
        best_sofar = temp->task;
    } 
    
    temp = temp->next;
  }
  
  
  // delete the node from list, Task will get deleted later
  delete (&g_head, best_sofar);
  
  return best_sofar;
}

// invoke the scheduler
void schedule(){
    //first come first serve
    //do until all tasks has run
    int taskDone = 0;
    int timeRun = 0;
    int totalTime = 0;
    while (g_head != NULL)
    {
        //find task to run
        Task *target = pickNextTask();
        //do task. run for the entire duration
        int runDuration = QUANTUM;
        if (target->burst < QUANTUM)
        {
            runDuration = target->burst;
        }
        run (target, runDuration);
        timeRun += runDuration;
        totalTime += runDuration + 1;
        taskDone += 1;
        printf("        Time is now: %d \n", timeRun);
        //reduce task burst by quantum
        target->burst -= QUANTUM;
        //reduce priority
        target->priority = 1;
        //delete the task if burst is less than 0. otherwise add back to list
        if (target->burst <= 0)
        {
        free(target->name);
        free(target);
        } else {
            //add back
            insert(&g_head, target);
        }
    }
    //calculate cpu utilization for extra credit
    if (totalTime > 0){
      float CPUUtil = ((float)timeRun / ((float)totalTime - 1))*100 ;
      printf("CPU Utilization: %.2f%% \n", CPUUtil);
    }
}