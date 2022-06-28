#include<stdio.h>
#include<stdatomic.h>
#include<stdlib.h>

//the node type in the stack
typedef struct _Node
{
    int data;
    struct _Node* next;
}Node;

//the stack
typedef struct _lfstack_t
{
    int tag;
    Node *head;
}lfstack_t;

//the push function
void lfstack_push(_Atomic lfstack_t *lfstack, int value)
{
    lfstack_t next, orig = atomic_load(lfstack);
    Node *node = malloc(sizeof(Node));
    node->data = value;
    do{
        node->next = orig.head;
        next.head = node;
        //next.tag = orig.tag+1; //increase the "tag"
    }while(!atomic_compare_exchange_weak(lfstack,&orig,next));
}

int lfstack_pop(_Atomic lfstack_t *lfstack)
{
    lfstack_t next, orig = atomic_load(lfstack);
    do{
       if(orig.head == NULL)
       {
            return -1;
       }
       next.head = orig.head->next;
       //next.tag = orig.tag+1; //increase the "tag"
    }while(!atomic_compare_exchange_weak(lfstack,&orig,next));
    printf("poping value %d\n",orig.head->data);
    free(orig.head);
    return 0;
}