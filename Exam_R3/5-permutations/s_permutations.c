
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void permutations(char *home, char *sub, int i, int size)
{
    int j;
    int k;
    k = 0;
    if(i == size)
        printf("%s\n", sub);
        
    while(k < size)
    {
        if(home[k] != '\0')
        {
            sub[i] = home[k];
            home[k] = '\0';
            permutations(home , sub, i + 1, size);
            home[k] = sub[i];
        }
        k++;
    }
}

int ft_strlen(char *s)
{

    int i = 0;
    if(!s)
        return(i);
    while(s[i])
        i++;
    return(i);
}

bool duplicat(char *str)
{
    int i = 0;
    int j;

    while(str[i])
    {
        j = 1;
        while(str[i + j])
        {   
            if(str[i] == str[i + j])
                return (true);
            j++;
        }
        i++;
    }
    return(false);
}

void set(char *tab, int one, int size)
{
    int i ;
    i = 0;
    // if(one != 0)
    // {
        while(one-- && one <= size)
        {
            tab[i] = '1';
            i++;
        }
    // }
    while(i < size)
    {
        tab[i] = '0';
        i++;
    }
    tab[i] = '\0';
}
int main(int argc, char **argv)
{
    int i = 0;
    int j = 8;
    int n = 0;
    int size;
    char *home;
    char *sub;
    // if(argc != 2)
    //     return (1);
    // if(duplicat(argv[1]))
    //     return (1);
    size = ft_strlen(argv[1]);
    size = 3;
    home = malloc(size + 1);
    sub = malloc(size + 1);
    // while(argv[1][i])
    // {
    //     home[i] = argv[1][i];
    //     i++;
    // }
    // home[i] = '\0';
    i = 0;
    while(i <= size)
    {
        set(home, i, size);
        // printf("%s\n", home);
        i++;
        permutations(home, sub, 0, size);   

    }
    return(0);
}