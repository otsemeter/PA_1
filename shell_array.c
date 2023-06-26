//preprocessor directives
#include<stdlib.h>
#include<stdio.h>
#include "shell_array.h"
#include "sequence.h"

//constants
#define FALSE  0
#define TRUE  1

//helper function declarations
void swap(long *array, int ind1, int ind2);
void printArray(long * array, int size);

/* swap
   ~~~~
   inputs: long * array, int ind1, int ind2
   
   array: array with values to be swapped
   ind1: first index being swapped
   ind2: second index being swapped
   
   instance varaibles: long temp
   
   temp: store temp array value when swapping
   
   functionality: 
   
   standard swap of two array data values using temp value
   */
void swap(long *array, int ind1, int ind2)
{
    long temp = array[ind1];
    array[ind1] = array[ind2];
    array[ind2] = temp;
}

/* Array_Load_From_File
   ~~~~~~~~~~~~~~~~~~~~
   inputs: char * filename, int * size
   
   filename: character array holding input file's location
   size: pointer to variable holding array's size
   
   instance variables: FILE * fptr, size_t count, long * arr
   
   fptr: pointer to file opened in read mode
   count: size of fptr in bytes
   arr: array being created from fptr data
   
   functionality: 
   
   open filename as fptr in read mode and check for success
   seek EOF and use ftell to find size of file, then rewind pointer to file start
   allocate sufficient memory for arr using count
   test for malloc succes
   read data from file using fread and save in arr, testing for success
   close file and return arr*/
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

    //printArray(arr, count);

    fclose(fptr);

    return arr;
}

/* Array_Save_To_File
  ~~~~~~~~~~~~~~~~~~~
  inputs: char * filename, long * array, int size
  
  filename: character array holding output file's location
  array: array to be saved to filename
  size: size of array
  
  instance variables: FILE * fptr
  
  fptr: pointer to filename opended in write mode
  
  functionality:
  
  open filename as fptr in write mode and test for success
  write contents of array to output file using fwrite
  close file and return the number of successfully saved data values
  */
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

/*test function for printing array contents*/
void printArray(long * array, int size)
{
    for(int x = 0; x < size; x++)
    {
        printf("%ld, ", array[x]);
    }
    printf("\n");
}

/* Array_Shellsort
   ~~~~~~~~~~~~~~~
   inputs: long * array, int size, long * n_comp
   
   array: array to be sorted
   size: size of array
   n_comp: pointer to number of comparisons made while sorting
   
   instance variables: int sorted, int last_exchange, int last_element, int seq_size, long k
   
   sorted: boolean that stores whether the array is completely sorted for current k value or not
   last_exchange: index value of the last swap made in the array
   last_element: index of last element to be checked
   seq_size: size of shell sequence
   k: holds current shell sequence value
   
   functionality:
   
   first generate shell sequence using Generate_2p3q_Seq
   outer loop: itterate from largest to smallest value of sequence
   set k to current sequence value
   set last_exhange to the size of the array minus 1 plus k to account for subtraction later
   set sorted to FALSE
   middle loop: continue sorting as long as sorted is FALSE
   set sorted to TRUE
   set last_element to last_exchange minus k to account for elements that are correctly placed
   inner loop: loop from current k value to the last_element
   itterate n_comp by 1 each loop
   if the current index is smaller than the index k elements prior, swap them
   set last exchange to the current index
   set sorted to FALSE again because a swap was made
   finally, free the sequence
   */
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
                *n_comp += 1;
                if(array[j - k] > array[j])
                {
                    swap(array, j, j - k);
                    last_exchange = j;
                    sorted = FALSE;
                }
            }
        }
    }

    free(sequence);
    
}