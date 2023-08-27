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
    if (argc < 2)
        err_exit("Not enough args provided!\n");

    int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ASSERT(!fd);
    ASSERT(write(fd, "some_data_before_test\n", 22) < 0);
    close(fd);

    ASSERT(!(fd = open(argv[1], O_RDWR | O_APPEND)));
    ASSERT(lseek(fd, 0, SEEK_SET) < 0);
    ASSERT(write(fd, "_some_data_with_append_", 23) < 0);

    return 0;
}
