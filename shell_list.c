//preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"
#include "shell_list.h"

//constants
#define FALSE 0
#define TRUE 1

//helper function declarations
Node * Create_Node();
void Print_List(Node * head);
void Swap_Nodes(Node * prev1, Node * prev2);
Node * Create_List(long * array, int size);
int Get_List_Size(Node * head);

//create new empty node with NULL next field
Node * Create_Node()
{
    Node * newNode = malloc(sizeof(Node));
    newNode -> next = NULL;

    return newNode;
}

/* Swap_Nodes
   ~~~~~~~~~~
   inputs: Node * prev1, Node * prev2
   
   prev1: the prior to the first node being swapped
   prev2: the prior to the second node being swapped
   
   instance variables: Node * curr1, Node * curr2, Node * temp
   
   curr1: first node being swapped
   curr2: second node being swapped
   temp: placeholder node to be used in swapping

   functionality:

   set curr1 and curr2 equal to the respective next fields of prev1 and prev2
   set the next fields of prev1 and prev2 the curr2 and curr1 respectively, swapping the previous memory locations
   instantiate temp to the next field of curr2
   set next field of curr2 to next field of curr1
   set next field of curr1 to temp, which was the next field of curr2
   */
void Swap_Nodes(Node * prev1, Node * prev2)
{
    Node * curr1 = prev1 -> next;
    Node * curr2 = prev2 -> next;

    prev2 -> next = curr1;
    prev1 -> next = curr2;

    Node * temp = curr2 -> next;
    curr2 -> next = curr1 -> next;
    curr1 -> next = temp;
}

/*Create_List
  ~~~~~~~~~~~
  inputs: long * array, int size
  
  array: array to be stored in list
  size: size of array
  
  instance variables: Node * head, Node * curr
  
  head: node pointing to head of list
  curr: node pointing to current list location
  
  functionality: 
  
  a function used solely for test purposes
  takes in an array and itterates through it
  creating list nodes for each array value
  finally returning the head pointer of the list
  */
Node * Create_List(long * array, int size)
{
    Node * head = Create_Node();
    head -> value = array[0];
    Node* curr = head;
    for(int i = 1; i < size; i++)
    {
        curr -> next = Create_Node();
        curr = curr -> next;
        curr -> value = array[i];
    }
    return head;
}

/*Print_List
  ~~~~~~~~~~
  inputs: Node * head
  
  head: the pointer to the head of the list to be printed
  
  instance variables: Node * curr
  
  curr: pointer to the current node being printed
  
  functionality:
  
  test function.
  prints node values until the node is NULL
  */
void Print_List(Node * head)
{
    Node * curr = head;
    while(curr != NULL)
    {
        printf("%ld, ", curr -> value);
        curr = curr -> next;
    }
}

/*Get_List_Size
  ~~~~~~~~~~~~~
  inputs: Node * head
  
  head: pointer to head of list
  
  instance variables: int size, Node * curr
  
  size: variable to hold size of list
  curr: pointer to current node
  
  functionality:
  
  uses while loop to itterate through linked list using curr
  itterates size by 1 for each time looping
  returns size
  */
int Get_List_Size(Node * head)
{
    int size = 0;
    Node * curr = head;

    while(curr != NULL)
    {
        curr = curr -> next;
        size ++;
    }

    return size;
}

/* List_Load_From_File
   ~~~~~~~~~~~~~~~~~~~
   inputs: char * filename
   
   filename: holds character array of the input file's location
   
   instance variables: FILE * fptr, Node * head, Node * curr, size_t count
   
   fptr: pointer to file
   head: head of linked list
   curr: pointer to current linked list node
   count: size of data in fptr
   
   functionality:
   
   opens filename in read mode as fptr
   checks for fopen failure
   uses fseek to find EOF, and then ftell to get file size in bytes
   resets the file's pointer using rewind
   next, for loop from 0 to count itterating through fptr's data and saving 
   the data to the value field of new nodes
   save new node as curr's next field
   itterate curr to be the new node
   close file
   return head*/
Node *List_Load_From_File(char *filename)
{
    FILE * fptr = fopen(filename, "r");

    if(fptr == NULL)
    {
        fprintf(stderr, "\nfopen fail line 58 shell_list\n");
        return NULL;
    }

    Node * head = Create_Node();

    Node * curr = head;
    fseek(fptr, 0, SEEK_END);
    size_t count = ftell(fptr) / sizeof(long);
    rewind(fptr);

    for(int x = 0; x < count; x++)
    {
        curr -> next =  Create_Node();
        curr = curr -> next;
        if(fread(&(curr -> value), sizeof(long), 1, fptr) != 1)
        {
            fclose(fptr);
            fprintf(stderr, "\nfread fail in List_Load_From_File\n");
            return head;
        }
    }
    fclose(fptr);
    return head;
}

/* List_Save_To_File
   ~~~~~~~~~~~~~~~~~
   inputs: char * filename, Node * list
   
   filename: character array holding output file's location
   list: pointer to head of list to be written to file
   
   instance variables: int correctly_written, File * fptr, Node * curr
   
   correctly_written: holds the number of data values successfuly written to fptr
   fptr: pointer to file
   curr: pointer to current node being saved from list
   
   functionality:
   
   open filename in write mode as fptr, and test for success
   itterate through list using curr, writing each data value to fptr
   each successfully written value, itterate correctly_written by 1
   close fptr
   return correctly_written
   */
int List_Save_To_File(char * filename, Node * list)
{
    int correctly_written = 0;
    FILE * fptr = fopen(filename, "w");

    if(fptr == NULL)
    {
        fprintf(stderr, "\nfopen fail line 88 shell_list\n");
    }

    Node * curr = list;

    while(curr != NULL)
    {
        if(fwrite(&(curr -> value), sizeof(long), 1, fptr) == 1)
        {
            correctly_written += 1;
        }
        curr = curr -> next;
    }

    fclose(fptr);
    return correctly_written;
}

/*List_Shellsort
  ~~~~~~~~~~~~~~
  inputs: Node * list, long * n_comp
  
  list: pointer to list head
  n_comp: pointer to variable holding number of comparisons made in function
  
  instance variables: Node * k_ptr, Node * curr, int seq_size, int list_size, long k, long * sequence
  
  k_ptr: pointer to node at current shell_sequence value k
  curr: pointer to current node being compared
  seq_size: size of shell sor sequence
  list_size: size of the linked list
  k: current shell_sequence value
  sequence: array of shell sort values

  functionality:

  first get size of linked list
  generate shell sequence using Generate_2p3q_Seq
  outer loop: loop through sequence values, largest to smallest
  initialize k_ptr and curr to the head of the list each itteration
  itterate through list to find k_th node using for loop and save as k_ptr
  inner loop: itterate from k_value to end of list
  itterate n_comp before each instance of the if statement
  check if the current value is larger than the value at k_ptr
  if larger, call swap on curr and k_ptr
  itterate curr
  if curr and k_ptr are adjacent (if k == 1) set k_ptr to curr -> next instead of itterating
  else itterate k_ptr
  exit all loops, free the sequence and return the head of the now sorted list 
  */
Node * List_Shellsort(Node * list, long * n_comp)
{
    *n_comp = 0;
    Node * k_ptr;
    Node * curr;
    int seq_size;
    int list_size = Get_List_Size(list -> next);
    long k;

    
    long * sequence = Generate_2p3q_Seq(list_size, &seq_size);
    for(int x = seq_size - 1; x >= 0; x--)
    {
        k_ptr = list;
        curr = list;
        k = sequence[x];
        for(int y = 0; y < k; y++)
        {
            k_ptr = k_ptr -> next;
        }

        while(k_ptr -> next != NULL)
        {
            *n_comp += 1;

            if((curr -> next -> value) > (k_ptr -> next -> value))
            {
                Swap_Nodes(curr, k_ptr);
            }
            curr = curr -> next;
            if(k == 1)
            {
                k_ptr = curr;
            }
            k_ptr = k_ptr -> next;
        }
        
    }
    free(sequence);
    return list;
}