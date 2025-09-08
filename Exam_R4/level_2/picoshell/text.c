#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/wait.h>

int picoshell(char **cmds[]) {

    int cmd_index = 0;
    int prev = -1;
    int fds[2];
    pid_t pid, last_pid;
    int status = 0;

    int max = 0;
    for (max = 0; cmds[max]; max++)
        continue;

    while (cmds[cmd_index]) {

        if (cmds[cmd_index + 1]) {
            if (pipe(fds) == -1) return -1; 
        }

        pid = fork();
        if (pid == -1) return -1;

        if (pid == 0) {
            // child
            if (cmd_index == 0) {
                close(fds[0]);
                dup2(fds[1], 1);
                close(fds[1]);
            } else if (cmd_index == max - 1) {
                dup2(prev, 0);
                close(prev);
            } else {
                dup2(prev, 0);
                close(prev);
                dup2(fds[1], 1);
                close(fds[1]);
            }
            execvp(cmds[cmd_index][0], cmds[cmd_index]);
            // perror("execvp");
            exit(1);
        }
        if (prev != -1) close(prev);
        if (cmds[cmd_index + 1]) {
            close(fds[1]);
            prev = fds[0];
        }
        last_pid = pid;
    
        cmd_index ++;
    }

    waitpid(last_pid, &status, 0);
    if (WIFEXITED(status))
        status = WEXITSTATUS(status);
    while (wait(NULL) > 0);

    return status;
}

// DANON watching after me that why i love danon

int main(int argc, char **argv)
{
    int cmds_size = 1;
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "|"))
            cmds_size++;
    }
    char ***cmds = calloc(cmds_size + 1, sizeof(char **));
    if (!cmds)
    {
        dprintf(2, "Malloc error: %m\n");
        return 1;
    }
    cmds[0] = argv + 1;
    int cmds_i = 1;
    for (int i = 1; i < argc; i++)
        if (!strcmp(argv[i], "|"))
        {
            cmds[cmds_i] = argv + i + 1;
            argv[i] = NULL;
            cmds_i++;
        }
    int ret = picoshell(cmds);
    if (ret)
        perror("picoshell");
    free(cmds);
    return ret;
}