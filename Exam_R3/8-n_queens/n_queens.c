/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:11:59 by mlaffita          #+#    #+#             */
/*   Updated: 2025/05/07 07:57:54 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

									// Mine:

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void ft_print(int *t, int s)
{
    int i=0;
    while(i<s)
    {
        fprintf(stdout,"%d",t[i]);
        if(i<s-1)
            fprintf(stdout," ");
        i++;
    }
        fprintf(stdout,"\n");
}

int ft_valid(int *t, int s, int row, int col)
{
    int i=0;
    while(i<row)
    {
        if(col==t[i])
            return 0;
        if(( t[i] - col == i-row )||(t[i] - col == row-i ))
            return 0;
        i++;
    }
    return 1;
}

void ft_solve(int s, int *t, int row)
{
    if(row==s)
    {
        ft_print(t, s);
        return ;
    }
    int i=0;
    while(i<s)
    {
        if(ft_valid(t, s, row, i))
        {
            t[row]=i;
            ft_solve(s, t, row+1);
        }
        i++;
    }
    return;
}

int main(int ac, char **ar)
{
    if(ac<2)
        return 1;
    
    int s=atoi(ar[1]);
    int t[s];
    int i=0;
    while(i<s)
        t[i++]=-1;
    ft_solve(s, t ,0);
    return 0;
}







