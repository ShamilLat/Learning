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
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char *argv[])
{
    struct mymsg {
        long mtype;
        long long v1;
        long long v2;
    } buf;
    key_t key;
    int n;
    long long value1, value2, maxval;
    sscanf(argv[1], "%d", &key);
    sscanf(argv[2], "%d", &n);
    sscanf(argv[3], "%lld", &value1);
    sscanf(argv[4], "%lld", &value2);
    sscanf(argv[5], "%lld", &maxval);

    struct sembuf up;
    up.sem_num = 0;
    up.sem_op = 1;
    up.sem_flg = 0;
    
    struct sembuf down;
    down.sem_num = 0;
    down.sem_op = -1;
    down.sem_flg = 0;

    buf.v1 = value1;
    buf.v2 = value2;

    int *pid = malloc(n * sizeof(*pid));

    uint32_t *check = mmap(NULL, sizeof(*check), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    *check = 0;

    int stack = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
    int sid = semget(key, n, 0666 | IPC_CREAT | IPC_EXCL);

    for (int i = 0; i < n; i++) {
        pid[i] = fork();
        if (pid[i] < 0) {
            free(pid);
            exit(1);
        }
        if (!pid[i]) {
            down.sem_num = i;
            while(1) {
                semop(sid, &down, 1);
                
                if (*check == -1) {
                    exit(0);
                }

                msgrcv(stack, &buf, sizeof(value1) + sizeof(value2), 1, 0);
                int v = buf.v1 + buf.v2;
                printf("%d %d\n", i, v);
                
                if (v > maxval) {
                    *check = -1;
                    for (int j = 0; j < n; j++) {
                        up.sem_num = j;
                        semop(sid, &up, 1);
                    }
                    exit(0);
                } 

                buf.v1 = buf.v2;
                buf.v2 = v;

                msgsend(stack, &buf, sizeof(buf), 0);
                up.sem_num = v % n;
                semop(sid, &up, 0);
            }
        }
    }
    msgsend(stack, &buf, sizeof(buf), 0);
    semop(sid, &up, 1);

    while(wait(0) != -1){}

    semctl(sid, IPC_RMID, 0);
    msgctl(stack, IPC_RMID, 0);

    free(pid);
    munmap(check, sizeof(*check));
    return 0;
}