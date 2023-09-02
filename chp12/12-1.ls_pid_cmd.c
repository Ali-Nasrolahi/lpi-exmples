/**
 * @author 4Zephyr.
 * @date 2023-08-17.
 */

#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#define PROC_DIR "/proc/"

char tmp_buf[1 << 12] = PROC_DIR;

FILE *open_status(struct dirent *subdir)
{

    /* appending null to buf, becomes like '/proc/\000\000' */
    memset(tmp_buf + strlen(PROC_DIR), 0, sizeof(tmp_buf) - strlen(PROC_DIR));

    /* Appending pid */
    strcat(tmp_buf + strlen(PROC_DIR), subdir->d_name);

    /* Appending '/status' */
    strcat(tmp_buf + strlen(tmp_buf), "/status");

    return fopen(tmp_buf, "r");
}

int main(int argc, char **argv)
{
    FILE *f;
    uid_t uid;
    pid_t pid;
    size_t len;
    char *line = NULL;
    struct dirent *subdir;
    DIR *dir = opendir(PROC_DIR);
    char name[1024], pid_s[1024], uid_s[1024];

    if (argc < 2)
        err_exit("Not enough args provided!\n");

    struct passwd *pw = getpwnam(argv[1]);
    ASSERT(!pw);

    while ((subdir = readdir(dir))) {
        f = open_status(subdir);
        if (!f)
            continue;

        /* Pasrsing /proc/pid/status fields */
        while (getline(&line, &len, f) != -1) {
            char *tk = strtok(line, ":");
            if (!strcmp(tk, "Pid"))
                strncpy(pid_s, strtok(NULL, ":"), 1024);
            else if (!strcmp(tk, "Name"))
                strncpy(name, strtok(NULL, ":"), 1024);
            else if (!strcmp(tk, "Uid"))
                strncpy(uid_s, strtok(NULL, ":"), 1024);
        }

        /* Putting parsed string to actual struct */
        sscanf(uid_s, "%d", &uid);
        sscanf(pid_s, "%d", &pid);

        /* Checking for uid equality */
        if (pw->pw_uid == uid)
            printf("\n\nname:%spid: %d\nuid: %d\n\n", name, pid, uid);

        fclose(f);
    }

    free(line);
    closedir(dir);

    return 0;
}
