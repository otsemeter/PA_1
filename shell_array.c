#include<stdlib.h>
#include<stdio.h>
#include "shell_array.h"
#include "sequence.h"
#define FALSE  0
#define TRUE  1

void swap(long *array, int ind1, int ind2);
void printArr(long * array, int size);

void swap(long *array, int ind1, int ind2)
{
    long temp = array[ind1];
    array[ind1] = array[ind2];
    array[ind2] = temp;
}

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

void printArray(long * array, int size)
{
    for(int x = 0; x < size; x++)
    {
        printf("%ld, ", array[x]);
    }
    printf("\n");
}

void Array_Shellsort(long *array, int size, long *n_comp)
{
    int sorted = FALSE;
    int last_exchange;
    int last_element;
    int seq_size;
    long k;
    *n_comp = 0;
    long * sequence = Generate_2p3q_Seq(size, &seq_size);

    for(int i = seq_size - 1; i >= 0; i--)
    {
        k = sequence[i];
        last_exchange = size + k - 1;
        sorted = FALSE;
        while(sorted == FALSE)
        {
            sorted = TRUE; 
            last_element = last_exchange - k;
            for(int j = k; j <= last_element; j++)
            {
                if(array[j - k] > array[j])
                {
                    *n_comp += 1;
                    swap(array, j, j - k);
                    last_exchange = j;
                    sorted = FALSE;
                }
            }
        }
    }

    free(sequence);
    
}