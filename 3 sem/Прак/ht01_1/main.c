#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/mman.h>

enum
{
    BIG_BITS = 0x1ff,
    LITTLE_BITS = 9,
    FILE_SIZE = 64 * 1024,
};

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1){
        fprintf(stderr, "Open fd Error\n");
        return 0;
    }
    uint8_t *n = mmap(NULL, FILE_SIZE, PROT_READ, MAP_PRIVATE, fd, 0);
    if (n != MAP_FAILED) {
        uint16_t tlb;
        sscanf(argv[2], "%"SCNx16, &tlb);
        uint16_t vpn = 0;
        while (scanf("%"SCNx16, &vpn) == 1) {
            uint16_t poz = vpn & BIG_BITS;
            printf("%"PRIu16"\n", *(uint16_t *)(n + (*(uint16_t *)(n + tlb + 2 * (vpn >> LITTLE_BITS)) | poz)));
        }
        close(fd);
        munmap(n, FILE_SIZE);
    }
    return 0;
}
