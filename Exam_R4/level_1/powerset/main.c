#include <stdio.h>
#include <stdlib.h>

void print_subset(int *subset, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d", subset[i]);
        if (i < size - 1)
            printf(" ");
    }
    printf("\n");
}

void find_subsets(int *set, int set_size, int target_sum, int *subset, int subset_size, int index)
{
    int sum = 0;
    for (int i = 0; i < subset_size; i++) 
        sum += subset[i];
    if (sum == target_sum)
        print_subset(subset, subset_size);


    for (int i = index; i < set_size; i++)
    {
        if (i > index && set[i] == set[i - 1]) 
            continue;
        subset[subset_size] = set[i];
        find_subsets(set, set_size, target_sum, subset, subset_size + 1, i + 1);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
        return 1;



    
    int target_sum = atoi(argv[1]);
    int set_size = argc - 2;
    int *set = malloc(set_size * sizeof(int));
    if (!set)
        exit(1);




    for (int i = 0; i < set_size; i++)
        set[i] = atoi(argv[i + 2]);
    int *subset = malloc(set_size * sizeof(int));
    if (!subset) 
    {
        free(set);
        exit(1);
    }



    find_subsets(set, set_size, target_sum, subset, 0, 0);
    free(set);
    free(subset);

    return 0;
}