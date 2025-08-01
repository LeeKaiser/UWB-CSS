/*
 * shm-client - client program to demonstrate shared memory.
 */
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ 27

int main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    key = 3456;

    /*
     * Get ID of segment
     */
    shmid = shmget(key, SHMSZ, 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    /*
     * Attach the segment to our data space.
     */
    shm = (char *)shmat(shmid, NULL, 0);
    printf("client: reading from shared memory\n");
    /*
     * Now read what the server put in the memory.
     */
    for (s = shm; *s != 0; s++)
    {
        putchar(*s);
    }
    putchar('\n');

    /*
     * Change the first character of the
     * segment to '*', indicating we have read the segment.
     */
    // *shm = '*';
    shm[0] = '*';
    exit(0);
}