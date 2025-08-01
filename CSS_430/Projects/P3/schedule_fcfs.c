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

bool comesBefore(char *a, char *b) { return strcmp(a, b) < 0; }

// based on traverse from list.c
// finds the task whose name comes first in dictionary
Task *pickNextTask() {
  // if list is empty, nothing to do
  if (!g_head)
    return NULL;

  struct node *temp;
  temp = g_head;
  Task *best_sofar = temp->task;

  while (temp != NULL) {
    if (comesBefore(temp->task->name, best_sofar->name))
      best_sofar = temp->task;
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
    while (taskDone < taskCount)
    {
        //find task to run
        Task *target = pickNextTask();
        //do task. run for the entire duration
        run (target, target->burst);
        timeRun += target->burst;
        totalTime += target->burst;
        totalTime ++;
        taskDone += 1;
        printf("        Time is now: %d \n", timeRun);
        //delete the task since it finished.
        free(target->name);
        free(target);
    }
    //calculate cpu utilization for extra credit
    if (totalTime > 1){
      float CPUUtil = ((float)timeRun / ((float)totalTime - 1))*100 ;
      printf("CPU Utilization: %.2f%% \n", CPUUtil);
    }
    
}