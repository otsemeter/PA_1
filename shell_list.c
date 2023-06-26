#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"
#include "shell_list.h"
#define FALSE 0
#define TRUE 1

Node * Create_Node();
void Print_List(Node * head);
void Swap_Nodes(Node * prev1, Node * prev2);
Node * Create_List(long * array, int size);
int Get_List_Size(Node * head);

Node * Create_Node()
{
    Node * newNode = malloc(sizeof(Node));
    newNode -> next = NULL;

    return newNode;
}

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

void Print_List(Node * head)
{
    Node * curr = head;
    while(curr != NULL)
    {
        printf("%ld, ", curr -> value);
        curr = curr -> next;
    }
}

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
        fread(&(curr -> value), sizeof(long), 1, fptr);
    }

    Print_List(head -> next);

    fclose(fptr);
    return head;
}

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
    Print_List(list -> next);
    return list;
}