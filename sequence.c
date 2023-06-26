//preprocessor directives
#include "sequence.h"
#include<stdio.h>
#include<stdlib.h>

//helper function declarations
int log_2(int n);

/* calculate log base 2 of n by 
    continuously dividing n by 2 
    until n is lessthan or equal to 1
*/
int log_2(int n)
{
    int logn = 0;

    while (n > 1)
    {
        n /= 2;
        logn++;
    }

    return logn;
}

/* Generate_2p3q_Seq
   ~~~~~~~~~~~~~~~~~
   inputs: int n, int * seq_size
   
   n: size of array sequence is being generated for
   seq_size: pointer to location where sequence size will be stored
   
   instance variables: int index_3, int index_2, int index_curr, long val_3, long val_2, int logn, long * seq
   
   index_3: index of the most recent base 3 value calculated
   index_2: index of the most recent base 2 value calculated
   index_curr: index of the current sequence value
   val_3: most recent base 3 value calculated
   val_2: most recent base 2 value calculated
   logn: log_2 of n
   seq: array to hold the sequence values
   
   functionality:
   
   preliminarily set seq_size to log_2 n squared to allocated sufficient memory
   initialize index 0 of seq to 1
   do-while loop, itterating as long as the current seq index's value is less than n, the array size
   first, itterate the current index to 1 because 0 was initialized
   set val_3 to the most recent base 3 index * 3
   set val_2 to the most recent base 2 index * 2
   if val_3 is less than val_2, set the current index of seq to val_3, otherwise set it to val_2
   itterate index_3 if val_3 was less than val_2, and do the inverse for index_2
   exit loop
   set seq_size to the last index, index_curr and return the sequence
   */
long *Generate_2p3q_Seq(int n, int *seq_size)
{
    int index_3 = 0;
    int index_2 = 0;
    int index_curr = 0;
    long val_3;
    long val_2;
    int logn = log_2(n);
    *seq_size = logn * logn;

    long * seq = malloc(sizeof(long) * (*seq_size));
    seq[0] = 1;
    
    do
    {
        index_curr++;
        val_3 = seq[index_3] * 3;
        val_2 = seq[index_2] * 2;

        (val_3 <= val_2) ? (seq[index_curr] = val_3): (seq[index_curr] = val_2);

        index_3 += val_3 <= val_2;
        index_2 += val_2 <= val_3;
    }while (seq[index_curr] < n);
    
    *seq_size = index_curr;
    return seq;
}