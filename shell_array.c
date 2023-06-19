#include<stdlib.h>
#include<stdio.h>
#include "shell_array.h"

long *Array_Load_From_File(char *filename, int *size)
{
    FILE * fptr = fopen(filename, "r");

    if(fptr == NULL)
    {
        fprintf(stderr, "\nfopen fail in Array_Load_From_File line 7\n");
        *size = 0;
        return NULL;
    }

    fseek(fptr, 0, SEEK_END);
    size_t count = ftell(fptr) / sizeof(long);
    *size = count;
    rewind(fptr);

    long *arr = malloc(sizeof(long) * count);

    if(arr == NULL)
    {
        fprintf(stderr, "\nmalloc fail line 19 in Array_Load_From_File\n");
        *size = 0;
        return NULL;
    }

    if(fread(arr, sizeof(long), count, fptr) != count)
    {
        fprintf(stderr, "\nfread fail in line 30 of Array_Load_From_File\n");
        return NULL;
    }

    fclose(fptr);

    return arr;
}

int Array_Save_To_File(char *filename, long *array, int size)
{
   FILE * fptr = fopen(filename, "w");
   if(fptr == NULL)
   {
        fprintf(stderr, "\nfopen fail in line 46 of Array_Save_To_File\n");
        return 0;
   }

    fwrite(array, sizeof(long), size, fptr);

    fclose(fptr);
    return size;
}

void Array_Shellsort(long *array, int size, long *n_comp)
{
    
}