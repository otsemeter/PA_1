#include "sequence.h"
#include<stdio.h>
#include<stdlib.h>

int log_2(int n);
long *Generate_2p3q_Seq(int n, int *seq_size);

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

long *Generate_2p3q_Seq(int n, int *seq_size)
{
    int index_3 = 0;
    int index_2 = 0;
    *seq_size = 0;
    long val_3;
    long val_2;
    long curr = 1;
    int logn = log_2(n);

    long * seq = malloc(sizeof(long) * logn * logn);

    while (curr < n)
    {
        *seq_size++;
        *(seq + (*seq_size)) = curr;
        val_3 = *(seq + index_3) * 3;
        val_2 = *(seq + index_2) * 2;

        curr = val_3 <= val_2 ? val_3:val_2;

        index_3 += val_3 <= val_2;
        index_2 += val_2 <= val_3;
    }
    
    return seq;
}