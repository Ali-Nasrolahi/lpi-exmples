/**
 * @author 4Zephyr.
 * @date 2023-08-22.
 */

#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

int cmp_fd(int fd1, int fd2)
{
    if (lseek(fd1, 0, SEEK_CUR) != lseek(fd2, 0, SEEK_CUR) ||
        fcntl(fd1, F_GETFL) != fcntl(fd2, F_GETFL))
        return -1;
    return 0;
}

int main(int argc, char **argv) { return 0; }
