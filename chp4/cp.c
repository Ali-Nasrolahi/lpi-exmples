/**
 * @file cp.c
 * @author Ali Nasrolahi (a.nasrolahi01@gmail.com)
 * @date 2023-08-02.
 */
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define ASSERT(expr)                                                                               \
    do {                                                                                           \
        if ((expr) < 0) {                                                                          \
            perror("Error");                                                                       \
            _exit(1);                                                                              \
        }                                                                                          \
    } while (0)

struct stat st;
char buff[1024], *src_f, *dst_f;
int src_fd, dst_fd, bytes;

int main(int argc, char **argv)
{
    argc < 3 ? _exit(-1), 0 : 0;

    src_f = argv[1];
    dst_f = argv[2];

    src_fd = open(src_f, O_RDONLY);
    ASSERT(src_fd);

    stat(src_f, &st);

    dst_fd = open(dst_f, O_CREAT | O_WRONLY, S_IWUSR);
    ASSERT(dst_fd);
    chmod(dst_f, st.st_mode);

    while ((bytes = read(src_fd, buff, 1024)))
        ASSERT(write(dst_fd, buff, bytes));

    ASSERT(bytes);

    close(src_fd);
    close(dst_fd);

    printf("File copied successfully\n");

    return 0;
}
