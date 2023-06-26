#include "shell_array.h"
#include "shell_list.h"
#include<stdlib.h>
#include<stdio.h>

/* main function
   ~~~~~~~~~~~~~~
   instance variables: int size, long n_comp
   
   size represents the array's size should the -a option be chosen
   n_comp represents the number of comparisons made in the sorting algorithm
   
   tests if there are 4 input arguments: ./pa1, option -a or -l, input file, output file
   
   checks for chosen option and makes appropriate function calls
   if incorrect option chosen throw error and return EXIT_FAILURE
   
   print number of comparisons to stdout
   
   return EXIT_SUCCESS
   */
int main(int argc, char ** argv)
{
    int size;
    long n_comp;

    if(argc != 4)
    {
        fprintf(stderr, "expected 3 inputs");
        return EXIT_FAILURE;
    }

    if(argv[1][1] == 'a')
    {
        long * arr = Array_Load_From_File(argv[2], &size);
        Array_Shellsort(arr, size, &n_comp);
        Array_Save_To_File(argv[3], arr, size);
        free(arr);
    }
    else if(argv[1][1] == 'l')
    {
        Node * head = List_Load_From_File(argv[2]);
        head = List_Shellsort(head, &n_comp);
        List_Save_To_File(argv[3], head -> next);
        Node * temp = head;
        while(head != NULL)
        {
            temp = head -> next;
            free(head);
            head = temp;
        }
    }
    else
    {
        fprintf(stderr, "expected '-a' or '-l' as option in arguments\n");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "\n%ld\n", n_comp);
    return EXIT_SUCCESS;
}