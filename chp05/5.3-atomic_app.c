/**
 * @author 4Zephyr.
 * @date 2023-08-17.
 */

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
    int fd, size;
    int app_en;

    if (argc < 3)
        err_exit("Not enough args provided!\n");

    app_en = (argc == 3);
    size = atoi(argv[2]);

    if (app_en)
        fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    else
        fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ASSERT(!fd);

    while (size--) {
        if (!app_en)
            ASSERT(lseek(fd, 0, SEEK_END) < 0);

        ASSERT(write(fd, &size, 1) < 0);
    }

    return 0;
}
