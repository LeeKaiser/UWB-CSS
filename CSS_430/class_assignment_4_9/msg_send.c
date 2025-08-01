#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h> // IPC_CREAT flag
#include <sys/msg.h> // msgget, msgrcv
#include <string.h>

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

   printf("Sending message to msg Queue %d\n", key);
   strcpy(message.msgText, "Insert Message Here. Please.");
   msgSize = strlen(message.msgText) + 1;
   message.msgType = 1;

   int rc = msgsnd(msgID, &message, msgSize, IPC_NOWAIT);
   if (rc == -1)
   {
      perror("Error on msgrv");
      exit(EXIT_FAILURE);
   }
   printf("msg_snd\n");
}