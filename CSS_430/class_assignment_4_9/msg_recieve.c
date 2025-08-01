#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h> // IPC_CREAT flag
#include <sys/msg.h> // msgget, msgrcv

const int MSG_SIZE = 128;
typedef struct
{
   long msgType;
   char msgText[128];
} message_buf;

int main()
{
   int msgID;
   size_t msgSize;
   int msgFlags = IPC_CREAT | 0666;
   message_buf message;

   key_t key = 777;
   msgID = msgget(key, msgFlags);
   if (msgID == -1)
   {
      perror("Error on msgget");
      exit(EXIT_FAILURE);
   }

   printf("IPC_NOWAIT %d\n", IPC_NOWAIT);
   int rc = msgrcv(msgID, &message, MSG_SIZE, 1, 0);
   if (rc == -1)
   {
      perror("Error on msgrv");
      exit(EXIT_FAILURE);
   }
   printf("msg_rcv: %s\n", message.msgText);
}