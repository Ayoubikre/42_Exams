/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brocken_gnl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:05:13 by mlaffita          #+#    #+#             */
/*   Updated: 2025/04/29 19:28:23 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

				    				// Mine:

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
        return (NULL);
        
    i = 0;
    while (str[i] != '\0')
    {
        t[i] = str[i];
        i++;
    }
    t[i] = '\0';
    
    return (t);
}

char    *get_next_line(int fd)
{
    static char t[BUFFER_SIZE];
           char line[100001];
    static int a;
    static int z;
           int i;

    if(fd<0 || BUFFER_SIZE <1)
        return NULL;
    
    i=0;
    while(1)
    {
        if(a>=z)
        {
            a=0;
            z=read(fd, t, BUFFER_SIZE);
            if(z<= 0)
            {
                a=0;
                z=0;
                break;
            }
        }
        line[i]=t[a];
        i++;
        a++;
        if(line[i-1]=='\n' || i>=100000)
            break;
    }
    line[i]='\0';
    if(i==0)
        return NULL;
    return (ft_strdup(line));
}

int main(int ac, char **av)
{
    char *t;
    
    while(1)
    {
        t=get_next_line(0);
        if(!t)
            break;
        printf("%s",t);
        free(t);
    }
    return 0;
}