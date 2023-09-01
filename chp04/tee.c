/**
 * @file tee.c
 * @author Ali Nasrolahi (a.nasrolahi01@gmail.com)
 * @brief usage: tee -f [file] (truc) or tee -a [file] (append).
 * @date 2023-08-02.
 *
 */
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define ASSERT(expr)                                                                               \
    do {                                                                                           \
        if ((expr) < 0) {                                                                          \
            perror("Error");                                                                       \
            _exit(1);                                                                              \
        }                                                                                          \
    } while (0)

int opt, append = O_TRUNC;
char *fname, buff[1024];

int main(int argc, char **argv)
{
    while ((opt = getopt(argc, argv, ":a:f:")) != -1) {
        switch (opt) {
        case 'a':
            append = O_APPEND;
        case 'f':
            fname = optarg;
            break;
        default:
            printf("Bad option\n");
            _exit(1);
        }
    }

    int fd = open(fname, O_CREAT | O_WRONLY | append, S_IRWXU);
    ASSERT(fd);

    while (1) {
        int res = read(STDIN_FILENO, buff, 1024);
        if (res > 0) {
            ASSERT(write(fd, buff, res));
        } else {
            ASSERT(res);
            break;
        }
    }

    close(fd);

    return 0;
}
