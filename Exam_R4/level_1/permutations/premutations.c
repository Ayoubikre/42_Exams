#include <stdio.h>
#include <string.h>

// Simple bubble sort
void bubbleSort(char *str, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (str[j] > str[j + 1]) {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}

// Reverse part of string from index 'start' to end
void reverse(char *str, int start, int length) {
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Generate next permutation in lexicographic order
int nextPermutation(char *str, int length) {
    // Step 1: Find rightmost character that is smaller than its next character
    int i = length - 2;
    while (i >= 0 && str[i] >= str[i + 1]) {
        i--;
    }
    
    // If no such character found, we're at the last permutation
    if (i < 0) {
        return 0;  // No more permutations
    }
    
    // Step 2: Find rightmost character greater than str[i]
    int j = length - 1;
    while (str[j] <= str[i]) {
        j--;
    }
    
    // Step 3: Swap str[i] and str[j]
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    
    // Step 4: Reverse the suffix starting at str[i+1]
    reverse(str, i + 1, length);
    
    return 1;  // Successfully generated next permutation
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }
    
    char *str = argv[1];
    int length = strlen(str);
        
    // Sort to get the first permutation
    bubbleSort(str, length);
    
    printf("%s\n", str);  // Print first (sorted) permutation
    
    // Generate and print all remaining permutations
    while (nextPermutation(str, length)) {
        printf("%s\n", str);
    }
    
    return 0;
}
