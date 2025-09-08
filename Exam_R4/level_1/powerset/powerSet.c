#include <stdio.h>
#include <stdlib.h>

void print_subset(int *subset, int subset_size) {
    for (int i = 0; i < subset_size; i++) {
        printf("%d", subset[i]);
        if (i < subset_size - 1)
            printf(" ");
    }
    printf("\n");
}

// Quick function to calculate sum of current subset
int calculate_sum(int *subset, int subset_size) {
    int sum = 0;
    for (int i = 0; i < subset_size; i++) {
        sum += subset[i];
    }
    return sum;
}

void find_subsets(int *set, int set_size, int *subset, int subset_size, 
                  int start_index, int target_sum) {
    
    // Calculate current sum
    int current_sum = calculate_sum(subset, subset_size);
    
    // If we found the target sum, print the subset
    if (current_sum == target_sum) {
        print_subset(subset, subset_size);
        return;
    }
    
    // Loop through remaining elements starting from start_index
    for (int i = start_index; i < set_size; i++) {
        // Skip Duplications
        if (i > start_index && set[i] == set[i - 1]) 
            continue;

        // Include current element set[i] in the subset
        subset[subset_size] = set[i];
        
        // Recursively find subsets starting from next element (i+1)
        find_subsets(set, set_size, subset, subset_size + 1, 
                    i + 1, target_sum);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <target_sum> <number1> <number2> ...\n", argv[0]);
        return 1;
    }

    int target_sum = atoi(argv[1]);
    int set_size = argc - 2;
    
    int *set = malloc(set_size * sizeof(int));
    if (!set) {
        return 1;
    }

    int *subset = malloc(set_size * sizeof(int));
    if (!subset) {
        free(set);
        return 1;
    }

    for (int i = 0; i < set_size; i++) {
        set[i] = atoi(argv[i + 2]);
    }

    find_subsets(set, set_size, subset, 0, 0, target_sum);
    
    free(set);
    free(subset);
    return 0;
}
