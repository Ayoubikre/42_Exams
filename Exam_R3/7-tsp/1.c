//the code is already given you just need to write the following functions:
//tsp - calculate_path_length - swap - permute

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>


 
#include <errno.h>
#include <math.h>
#include <float.h>

float    distance(float a[2], float b[2])
{
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}


// void swap(int *a, int *b)
// {
//     int tmp = *a;
//     *a = *b;
//     *b = tmp;
// }
// float calculate_path_length(float (*array)[2], int *perm, ssize_t size)
// {
//     float length = 0.0f;
//     for (ssize_t i = 0; i < size - 1; i++)
//         length += distance(array[perm[i]], array[perm[i + 1]]);

//     length += distance(array[perm[size - 1]], array[perm[0]]);
//     return length;
// }

// void permute(float (*array)[2], int *perm, ssize_t size, ssize_t start, float *min_path)
// {
//     if (start == size)
//     {
//         float path_length = calculate_path_length(array, perm, size);
//         if (path_length < *min_path)
//             *min_path = path_length;
//         return;
//     }

//     for (ssize_t i = start; i < size; i++)
//     {
//         swap(&perm[start], &perm[i]);
//         permute(array, perm, size, start + 1, min_path);
//         swap(&perm[start], &perm[i]);
//     }
// }

// float tsp(float (*array)[2], ssize_t size)
// {
//     if (size < 2)
//         return 0.0f;
//     int *perm = malloc(sizeof(int) * size);
//     if (!perm)
//     {
//         perror("malloc");
//         return 0.0f;
//     }

//     for (ssize_t i = 0; i < size; i++)
//         perm[i] = i;
//     float shortest_length = FLT_MAX;
//     permute(array, perm, size, 0, &shortest_length);
//     free(perm);
//     return shortest_length;
// }




ssize_t    file_size(FILE *file)
{
    char    *buffer = NULL;
    size_t    n = 0;
    ssize_t ret;

    errno = 0;

    for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

    free(buffer);
    if (errno || fseek(file, 0, SEEK_SET))
        return -1;
    return ret;
}

int        retrieve_file(float (*array)[2], FILE *file)
{
    int tmp;
    for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++)
        if (tmp != 2)
        {
            errno = EINVAL;
            return -1;
        }
    if (ferror(file))
        return -1;
    return 0;
}

int        main(int ac, char **av)
{
    char *filename = "stdin";
    FILE *file = stdin;
    if (ac > 1)
    {
        filename = av[1];
        file = fopen(filename, "r");
    }

    if (!file)
    {
        fprintf(stderr, "Error opening %s: %m\n", filename);
        return 1;
    }

    ssize_t size = file_size(file);
    if (size == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", filename);
        fclose(file);
        return 1;
    }

    float (*array)[2] = calloc(size, sizeof (float [2]));
    if (!array)
    {
        fprintf(stderr, "Error: %m\n");
        fclose(file);
        return 1;
    }

    if (retrieve_file(array, file) == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", av[1]);
        fclose(file);
        free(array);
        return 1;
    }
    if (ac > 1)
        fclose(file);

    printf("%.2f\n", tsp(array, size));
    free(array);
}
