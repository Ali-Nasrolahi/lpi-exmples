/**
 * @author 4Zephyr.
 * @date 2023-08-22.
 */
#include <sys/uio.h>
#include <unistd.h>

#if R_IOV
#define rw_iov _readv
#define rw_c read
#else
#define rw_iov _writev
#define rw_c write
#endif

int rw_iov(int fd, const struct iovec *iov, int iovcnt)
{
    int i, b;
    for (b = i = 0; b > -1 && i < iovcnt; i++)
        b = rw_c(fd, iov[i].iov_base, iov[i].iov_len);

    return b < 0;
}

int main(int argc, char **argv) { return 0; }
