#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

int son_num(int val, int nproc)
{
    return val % nproc * val % nproc * val % nproc * val % nproc;
}

int main(int argc, char *argv[])
{
    int nproc, maxval;
    key_t key;
    sscanf(argv[1], "%d", &nproc);
    sscanf(argv[2], "%d", &key);
    sscanf(argv[3], "%d", &maxval);
    
    struct sembuf up;
    up.sem_num = 0;
    up.sem_op = 1;
    up.sem_flg = 0;
    
    struct sembuf down;
    down.sem_num = 0;
    down.sem_op = -1;
    down.sem_flg = 0;

    int *pid = malloc((nproc + 1) * sizeof(*pid));

    int sid;
    sid = semget(key, nproc + 1, 0777 | IPC_CREAT | IPC_EXCL);
    if (sid == -1) {
        fprintf(stderr, "semget error\n%s\n\n", strerror(errno));
    }
    uint32_t *mem = mmap(NULL, sizeof(*mem), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    *mem = 0;
    
    uint32_t *adress = mmap(NULL, sizeof(*mem), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    *adress = 0;
    
    for (int i = 0; i < nproc; i++) {
        semctl(sid, i, SETVAL, (int) 0);
    }
    for (int i = 0; i < nproc; i++) {
        pid[i] = fork();
        if (!pid[i]) {
            down.sem_num = i;
            while (1) {
                semop(sid, &down, 1);
                
                if (*adress == -1) {
                    exit(0);
                }
                printf("%d %d %d\n", i + 1, *mem, *adress);
                fflush(stdout);
                if (*mem != maxval) {
                    (*mem)++;
                } else {
                    *adress = -1;
                    for (int j = 0; j < nproc; j++) {
                        up.sem_num = j;
                        semop(sid, &up, 1);
                    }
                    exit(0);
                }
                *adress = i + 1;
                up.sem_num = son_num(*mem, nproc);
                semop(sid, &up, 1);
            }
        }
    }
    semop(sid, &up, 1);
    
    while(wait(0) != -1){}

    semctl(sid, IPC_RMID, 0);
    free(pid);
    munmap(adress, sizeof(*adress));
    munmap(mem, sizeof(*mem));
    return 0;
}