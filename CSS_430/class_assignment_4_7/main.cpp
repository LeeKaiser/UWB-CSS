#include <stdlib.h>  //exit
#include <stdio.h>   //perror
#include <unistd.h>  //fork, pipe
#include <sys/wait.h>   //wait

// #define READ = 0
// #define WRITE = 1
int main() {
    
 enum { READ, WRITE };
 pid_t pid;
 int pipeFD[2];

 if (pipe(pipeFD) < 0) {
   perror("Error in creating pipe");
   exit(EXIT_FAILURE);
 }

 pid = fork();
 if (pid < 0) {
   perror("Error during fork");
   exit(EXIT_FAILURE);
 }

 if (pid == 0) {
   // Child
   close(pipeFD[READ]);
   dup2(pipeFD[WRITE], 1);   // stdout is now child's write pipe

   int rc = execlp("/bin/ls", "ls", "-l", (char *)0);
   if (rc == -1)
   {
       fprintf(stderr, "Error on execl\n");
   }
   // If exec() succeeds, it never returns
   // the line below would only get executed if exec failed
   printf("Child failed\n");
   exit(EXIT_SUCCESS);
   
 } else {
   //Parent
   close(pipeFD[WRITE]);
   
   char buf[256];
   int n = read(pipeFD[READ], buf, 256);
   buf[n] = '\0';
   for (int i = 0; i < n; ++i) {
     printf("%c ", buf[i]);
   }   

   wait(NULL);
   printf("Parent exiting\n");
 }
 exit(EXIT_SUCCESS);
}