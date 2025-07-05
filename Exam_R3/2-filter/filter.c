/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:05:40 by mlaffita          #+#    #+#             */
/*   Updated: 2025/05/07 06:29:10 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

									// Mine:

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char    *ft_strdup(const char *str)
{
    char    *t;
    int        i;
    int        s;

    s=0;
    while(str[s])
        s++;
        
    t = malloc(s + 1);
    if (t == NULL)
        return (perror("ERROR : "), NULL);
        
    i = 0;
    while (str[i] != '\0')
    {
        t[i] = str[i];
        i++;
    }
    t[i] = '\0';
    
    return (t);
}

char	*ft_get_next_line(int fd)
{
	static 	char	t[BUFFER_SIZE];
			char	line[100001];
	static 	int		a;
	static 	int		z;
			int		i;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
		
	i = 0;
	while (1)
	{
		if (a >= z)
		{
			a = 0;
			z = read(fd, t, BUFFER_SIZE);
			if (z <= 0)
			{
				a = 0;
				z = 0;
				break ;
			}
		}
		line[i] = t[a];
		i++;
		a++;
		if (line[i - 1] == '\n' || i >= 100000)
			break ;
	}
	line[i] = '\0';
	
	if (i == 0)
		return (NULL);
		
	return (ft_strdup(line));
}

int ft_check(char *t, char *ar, int s)
{
	int i;
	
	if(!t || !ar)
		return -1;

	i=0;
	while(i<s && t[i]==ar[i])
		i++;
		
	if(i<s)
		return -1;
	return 1;
}

void ft_printf(char *t , char *ar)
{
	int i;
	int j;
	int s;
	
	s=0;
	while(ar[s])
		s++;
	
	i=0;
	while(t[i])
	{
		if(ft_check(t+i, ar, s)==1)
		{
			j=0;
			while(j<s)
			{
				t[i+j]='*';
				j++;
			}
		}
		write(1, &t[i], 1);
		i++;
	}
	return;
}

int	main(int ac, char **ar)
{
	char *t;

	if (ac != 2)
		return (1);

	while (1)
	{
		t = ft_get_next_line(0);
		if (!t)
			break ;
		ft_printf(t, ar[1]);
		free(t);
	}
	return (0);
}
