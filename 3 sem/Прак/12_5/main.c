#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <sys/signalfd.h>

enum
{
    BUF_SIZE = 32,
    BYTE_SIZE = 8,
    OLD_BIT = 0x80
};

int main(int argc, char *argv[])
{
    sigset_t s1, s2;
    sigemptyset(&s1);
    sigaddset(&s1, SIGUSR1);
    sigaddset(&s1, SIGUSR2);
    sigaddset(&s1, SIGIO);

    sigemptyset(&s2);
    sigaddset(&s2, SIGALRM);

    int pid1 = fork();
    if (pid1 < 0) {
        printf("pid1 error\n");
        fflush(stdout);
    }
    if (!pid1) {
        sigprocmask(SIG_BLOCK, &s1, 0);
        int sig1 = signalfd(-1, &s1, 0);
        struct signalfd_siginfo in;
        int pid_second = 0, flag = 1, byte = 0;

        unsigned char letter = 0;
        //printf("1 before while\n");
        while (read(sig1, &in, sizeof(in))) {
            if (flag) {
                flag = 0;
                pid_second = in.ssi_pid;
            }
            if (in.ssi_signo == SIGIO) {
                exit(0);
            }
            letter = letter >> 1;
            if (in.ssi_signo == SIGUSR2) {
                letter = letter | OLD_BIT;
            }
            byte++;
            if (byte == BYTE_SIZE) {
                //printf("pid1 %d %c\n", letter, letter);
                printf("%c", letter);
                fflush(stdout);
                byte = 0;
                letter = 0;
            }
            kill(pid_second, SIGALRM);
        }
        exit(0);
    }
    int pid2 = fork();
    if (!pid2) {
        sigprocmask(SIG_BLOCK, &s2, 0);
        int sig2 = signalfd(-1, &s2, 0);
        struct signalfd_siginfo out;

        int fd = open(argv[1], O_RDONLY);
        unsigned char buf[BUF_SIZE], cnt = 0;
 
        //printf("2 before while\n");
        while ((cnt = read(fd, buf, sizeof(buf))) > 0) {
            for (int i = 0; i < cnt; i++) {
                //printf("pid2 %c\n", buf[i]); fflush(stdout);
                for(int j = 0; j < BYTE_SIZE; j++) {
                    //printf("%d", buf[i] & 1); fflush(stdout);
                    if (buf[i] & 1) {
                        kill(pid1, SIGUSR2);
                    } else {
                        kill(pid1, SIGUSR1);
                    }
                    buf[i] = buf[i] >> 1;
                    //printf("2 in send signal\n");
                    read(sig2, &out, sizeof(out));
                    //printf("SIGALRM came\n");
                }
                //printf("\n"); fflush(stdout);
            }
        }
        kill(pid1, SIGIO);
        exit(0);
    }
    wait(0);
    wait(0);
    return 0;
}