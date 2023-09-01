/**
 * @author 4Zephyr.
 * @date 2023-08-22.
 */

#include <fcntl.h>
#include <stdio.h>
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
    int fd1, fd2, fd3;

    if (argc < 2)
        err_exit("Specify filename\n");

    ASSERT((fd1 = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 0600)) < 0);
    ASSERT((fd2 = dup(fd1)) < 0);
    ASSERT((fd3 = open(argv[1], O_RDWR)) < 0);

    /* File becomes something like: hello,world\n */
    ASSERT(write(fd1, "hello,", 6) < 0);
    ASSERT(write(fd2, "world\n", 7) < 0);

    /* Set seek to begining of the file for fd1 and its duplicate fd2 */
    ASSERT(lseek(fd2, 0, SEEK_SET) < 0);

    /* Output will be overwritten */
    ASSERT(write(fd1, "HELLO", 6) < 0);

    /* Output will be overwritten again */
    ASSERT(write(fd3, "GIDDY", 6) < 0);

    return 0;
}
