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