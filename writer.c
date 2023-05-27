#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define SHM_SIZE 1024

int main(int argc, char *argv[])
{

    key_t key = ftok("/tmp", 0);
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    char *shmaddr = shmat(shmid, NULL, 0);

    strcpy(shmaddr, "Message");

    if (shmdt(shmaddr) == -1)
    {
        perror("shmdt");
        exit(1);
    }

    return 0;
}