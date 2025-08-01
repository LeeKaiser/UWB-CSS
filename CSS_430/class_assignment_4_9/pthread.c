// File: pthread_example.c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// compile using: gcc -pthread pthread_example.c -o pthread_example

void *ThreadFunc(void *param); // the thread runner
int count = 0;

int main(int argc, char *argv[]) {
  int i;
  pthread_t tid;       // thread IDs
  pthread_attr_t attr; // attributes for each thread

  if (argc != 2) {
    fprintf(stderr, "usage: a.out <string>\n");
    return -1;
  }
  // get default attributes for the thread
  pthread_attr_init(&attr);

  // create the thread
  pthread_create(&tid, &attr, ThreadFunc, argv[1]);

  for (i = 0; i < 1000; i++) {
    // sleep(1);
    printf(" Master[%d]:%s\n", i, argv[1]);
    printf(" Master count %d\n", count++);
  }

  // now wait for the thread to exit
  pthread_join(tid, NULL);
  printf("Master synched with slave\n");
}

void *ThreadFunc(void *param) {
  int i;

  for (i = 0; i < 300; i++) {
    // sleep(2);
    printf(" Slave[%d]:%s\n", i, (char *)param);
    printf(" Slave count %d\n", count++);
  }
  pthread_exit(0);
}