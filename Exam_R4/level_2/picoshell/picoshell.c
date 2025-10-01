#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

// int picoshell(char **cmds[])
// {
//     int res = 0;
//     int i = 0;
//     int prv_fd = -1;
//     int st;
//     int fd[2];
//     pid_t pid;
    
    
//     while (cmds[i])
//     {
//         if(cmds[i + 1])
//             pipe(fd);
//         pid = fork();
//         if(pid == -1)
//             return 1;
            
//         if (pid == 0)
//         {
//             if(prv_fd != -1)
//             {
//                 dup2(prv_fd, 0);
//                 close(prv_fd);
//             }
//             if(cmds[i + 1])
//             {
//                 dup2(fd[1], 1);
//                 close(fd[1]);
//             }
//             execvp(cmds[i][0], cmds[i]);
//             return 1;
//         }
    
//         while (wait(&st) == -1)
//         {
//             if(WIFEXITED(st) && WEXITSTATUS(st) == 0)
//                 res = 1;
//         }
//         if(prv_fd != -1)
//             close(prv_fd);
//         if(cmds[i + 1])
//         {
//             close(fd[1]);
//             prv_fd = fd[0];
//         }
//         i++;
//     }
//     return res;
// }

// int main()
// {
//     char *c[2] = {"ls", NULL};
//     char **cmds[] = {c, NULL};
//     printf("<%d>\n", picoshell(cmds));
// }