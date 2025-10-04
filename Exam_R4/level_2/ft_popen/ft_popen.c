/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:14:09 by aakritah          #+#    #+#             */
/*   Updated: 2025/10/04 14:08:21 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

									// Mine:

int	ft_popen(const char *file, char *const argv[], char type)
{
	pid_t	pid;
	int		fd[2];

	if(!file || !argv || (type != 'w' && type != 'r'))
        return -1;
        
	if (pipe(fd) == -1)
		return (-1);
        
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		if (type == 'r'){            
			if(dup2(fd[1], STDOUT_FILENO) == -1)
                exit(-1);
        }
		else if (type == 'w'){
			if(dup2(fd[0],STDIN_FILENO) == -1)
                exit(-1);
        }
        close(fd[0]);
        close(fd[1]);
		if (execvp(file, argv) == -1)
			exit(-1);
	}
	if (type == 'r')
        return (close(fd[1]), fd[0]);
    return (close(fd[0]), fd[1]);
}

int main() 
{
    printf("fd : %d\n", ft_popen("ls", (char *const[]){"ls", NULL}, 'r'));
    printf("fd : %d\n", ft_popen("ls", (char *const[]){"ls", NULL}, 'w'));
}