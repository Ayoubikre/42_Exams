/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:59:49 by aakritah          #+#    #+#             */
/*   Updated: 2025/10/04 18:59:53 by aakritah         ###   ########.fr       */
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

void ft_solve(char *t, char *t2, int *lock, int s, int x)
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
        if (lock[i])
        {
            i++;
            continue;
        }

        lock[i] = 1;
            t2[x] = t[i];
            ft_solve(t, t2, lock, s, x + 1);
        lock[i] = 0;

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
    int *lock = calloc(s, sizeof(int));
    if (!t || !t2 || !lock)
        return (free(t),free(t2),free(lock), 1);

    strcpy(t, ar[1]);
    ft_sort(t, s);
    ft_solve(t, t2, lock, s, 0);

    free(t);
    free(t2);
    free(lock);
    return 0;
}
