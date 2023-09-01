/**
 * @author 4Zephyr.
 * @date 2023-08-17.
 */

#define _FILE_OFFSET_BITS 64

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define err_exit(...)                                                                              \
    do {                                                                                           \
        printf(__VA_ARGS__);                                                                       \
        _exit(-1);                                                                                 \
    } while (0);

#define perror_exit(s)                                                                             \
    do {                                                                                           \
        perror(s);                                                                                 \
        _exit(-1);                                                                                 \
    } while (0);

#define ASSERT(v)                                                                                  \
    do {                                                                                           \
        if (v)                                                                                     \
            perror_exit("ASSERT");                                                                 \
    } while (0);

int main(int argc, char **argv)
{
    if (argc < 3)
        err_exit("Not enough args provided!\n");

    int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ASSERT(!fd);

    off_t off = atoll(argv[2]);
    ASSERT(lseek(fd, off, SEEK_SET) < 0);

    ASSERT(write(fd, "test", 4) < 0);

    return 0;
}
