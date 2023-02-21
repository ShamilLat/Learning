#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/mman.h>

enum {
    PAGE_MASK = 0b1111111000000000,
};

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Open fd Error\n");
        return 0;
    }
    void *n = mmap(NULL, 64 * 1024, PROT_READ, MAP_PRIVATE, fd, 0);
    if (n != MAP_FAILED) {
        uint16_t tlb;
        sscanf(argv[2], "%"SCNx16, &tlb);
        uint16_t vpn = 0;
        while (scanf("%"SCNx16, &vpn) == 1) {
            uint16_t poz = vpn ^ (vpn & PAGE_MASK);
            printf("%"PRIu16"\n", *(uint16_t *)(n + (*(uint16_t *)(n + tlb + 2 * (vpn >> 9)) | poz)));
        }
        close(fd);
        munmap(n, 64 * 1024);
    }
    return 0;
}
