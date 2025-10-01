#include <stdio.h>

void solve(char *str, int pos, int open, int to_remove, char *tmp)
{
    if (!str[pos])
    {
        if (open == 0 && to_remove == 0)
        {
            tmp[pos] = '\0';
            puts(tmp);
        }
        return;
    }
    if (to_remove > 0)
    {
        tmp[pos] = ' ';
        solve(str, pos + 1, open, to_remove - 1, tmp);
    }
    if (str[pos] == '(')
    {
        tmp[pos] = '(';
        solve(str, pos + 1, open + 1, to_remove, tmp);
    }
    else if (str[pos] == ')')
    {
        if (open > 0)
        {
            tmp[pos] = ')';
            solve(str, pos + 1, open - 1, to_remove, tmp);
        }
    }
    else
    {
        tmp[pos] = str[pos];
        solve(str, pos + 1, open, to_remove, tmp);
    }
}

int total_removals(char *str)
{
    int open = 0, close = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == '(')
            open++;
        else if (str[i] == ')')
        {
            if (open > 0)
                open--;
            else
                close++;
        }
    }
    return open + close;
}

int main(int ac, char *av[])
{
    if (ac != 2)
        return (1);

    char *str = av[1];
    int n = 0;
    while (str[n])
        n++;

    char temp[n + 1];
    solve(str, 0, 0, total_removals(str), temp);
}