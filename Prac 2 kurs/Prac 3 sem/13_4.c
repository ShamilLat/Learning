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

int main(int argc, char *argv[])
{
    setbuf(stdin, NULL);
    int count;
    sscanf(argv[1], "%d", &count);
    
    struct sembuf up;
    up.sem_num = 0;
    up.sem_op = 1;
    up.sem_flg = 0;
    
    struct sembuf down;
    down.sem_num = 0;
    down.sem_op = -1;
    down.sem_flg = 0;

    int *pid = malloc(count * sizeof(*pid));

    key_t key;
    int rfd = open("/dev/urandom", O_RDONLY);
    read(rfd, &key, sizeof(key));

    int sid;
    sid = semget(key, count, 0666 | IPC_CREAT | IPC_EXCL);
    if (sid == -1) {
        fprintf(stderr, "semget error\n%s\n\n", strerror(errno));
    }
    uint32_t *check = mmap(NULL, sizeof(*check), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    *check = 0;

    for (int i = 0; i < count; i++) {
        semctl(sid, i, SETVAL, (int) 0);
    }
    for (int i = 0; i < count; i++) {
        pid[i] = fork();
        if (!pid[i]) {
            down.sem_num = i;
            int num = 0;
            while (1) {
                semop(sid, &down, 1);
                
                if (*check == -1) {
                    exit(0);
                }

                if ((scanf("%d", &num)) != 1) {
                    *check = -1;
                    for (int j = 0; j < count; j++) {
                        up.sem_num = j;
                        semop(sid, &up, 1);
                    }
                    exit(0);
                }

                printf("%d %d\n", i, num);
                fflush(stdout);

                int r = (count + (num % count)) % count;
                
                up.sem_num = r;
                semop(sid, &up, 1);
            }
        }
    }
    semop(sid, &up, 1);
    
    while(wait(0) != -1){}

    semctl(sid, IPC_RMID, 0);
    free(pid);
    close(rfd);
    munmap(check, sizeof(*check));
    return 0;
}