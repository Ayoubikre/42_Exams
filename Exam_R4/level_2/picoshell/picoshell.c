/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:09:51 by aakritah          #+#    #+#             */
/*   Updated: 2025/10/04 16:23:33 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

									// Mine:

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int picoshell(char **cmds[])
{
    if (!cmds)
        return -1;
    
    int s=0;
    while(cmds[s])
        s++;
    
    int t[s-1][2];
    for(int i=0; i<s-1; i++)
        if(pipe(t[i])==-1)
            return -1;
    
    int i=0;
    pid_t pid;
    while(i<s)
    {
        pid=fork();
        if(pid==-1)
            exit(1);
        else if(pid==0)
        {
            if(i==0)
                dup2(t[i][1], 1);
            else if(i==s-1)
                dup2(t[i-1][0],0);
            else{
                dup2(t[i-1][0], 0);
                dup2(t[i][1], 1);
            }
            
            for(int i=0; i<s-1; i++){
                close(t[i][0]);    
                close(t[i][1]);    
            }
            execvp(cmds[i][0], cmds[i]);
            exit(-1);
        }
        i++; 
    }

    for(int i=0; i<s-1; i++){
        close(t[i][0]);    
        close(t[i][1]);    
    }

    for(int i=0; i<s; i++)
        wait(NULL);
    
    return 0;
}

int main()
{
    char *cmd1[] = {"echo", "squalala!", NULL};
    char *cmd2[] = {"cat", NULL};
    char *cmd3[] = {"sed", "s/a/b/g", NULL};

    // char **t[] = {cmd2, cmd3, NULL};
    char **t[] = {cmd1, cmd2, cmd3, NULL};
    picoshell(t);

    return 0;
}
