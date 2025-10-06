/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:59:01 by aakritah          #+#    #+#             */
/*   Updated: 2025/10/04 18:59:31 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

									// Mine:

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

void ft_solve(int n, int *t, int *t2, int *lock, int s, int x, int i, int sum)
{
    if (sum == n)
    {
        if (x != 0) 
        {
            for (int j = 0; j < x; j++)
                printf("%d ", t2[j]);
            printf("\n");
        }
    }

    while (i < s)
    {
        if (lock[i])
        {
            i++;
            continue;
        }
        lock[i] = 1;
            t2[x] = t[i];
            ft_solve(n, t, t2, lock, s, x + 1, i + 1, sum + t[i]);
        lock[i] = 0;
        i++;
    }
}

int main(int ac, char **ar)
{
    if (ac < 2)
        return 1;

    int s = ac - 2;
    int *t = calloc(s, sizeof(int));
    int *t2 = calloc(s, sizeof(int));
    int *lock = calloc(s, sizeof(int));
    if (!t || !t2 || !lock)
        return (free(t),free(t2),free(lock), 1);
    int n = atoi(ar[1]);
    for (int j = 0; j < s; j++)
        t[j] = atoi(ar[j + 2]);

    ft_solve(n, t, t2, lock, s, 0, 0, 0);

    free(t);
    free(t2);
    free(lock);
    return 0;
}
