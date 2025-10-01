/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:12:17 by mlaffita          #+#    #+#             */
/*   Updated: 2025/05/07 12:06:37 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

									// Mine:

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void ft_sort(char *t, int s)
{
    int i = 0;
    while (i < s - 1)
    {
        int j = 0;
        while (j < s - i - 1)
        {
            if (t[j] > t[j + 1])
            {
                char tmp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}

void ft_solve(char *t, char *t2, int *used, int s, int x)
{
    if (x == s)
    {
        write(1, t2, s);
        write(1, "\n", 1);
        return;
    }

    int i=0;
    while(i<s)
    {
        if (used[i])
        {
            i++;
            continue;
        }

        used[i] = 1;
            t2[x] = t[i];
            ft_solve(t, t2, used, s, x + 1);
        used[i] = 0;

        i++;
    }
}

int main(int ac, char **ar)
{
    if (ac < 2)
        return 1;

    int s = strlen(ar[1]);
    if (s == 0)
        return 0;

    char *t = malloc(s + 1);
    char *t2 = malloc(s + 1);
    int *used = calloc(s, sizeof(int));
    if (!t || !t2 || !used)
        return 1;

    strcpy(t, ar[1]);
    ft_sort(t, s);
    ft_solve(t, t2, used, s, 0);

    free(t);
    free(t2);
    free(used);
    return 0;
}
