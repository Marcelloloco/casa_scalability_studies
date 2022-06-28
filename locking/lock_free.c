#include "stack.h"
#include <pthread.h>

_Atomic lfstack_t top = {0, NULL};
int limit_numbers = 100;
int num_threads = 10;

 
void *push(void *input)
{
    for(int i=0; i<limit_numbers; i++)
    {
        lfstack_push(&top, i);
        printf("push %d\n",i);
    }    
    pthread_exit(NULL);
}

void *pop(void *input)
{
    for(int i=0; i<limit_numbers;)
    {
        int result;
        result = lfstack_pop(&top);
        if(result == -1)
            printf("the stack is empty\n");
        else
        {
            i++;
        }

    }
    pthread_exit(NULL);
}

int main()
{
    int num_twice = num_threads*2;
    pthread_t tid[num_twice];

    for(int i=0; i<num_threads; i++)
        pthread_create(&tid[i],NULL,push,NULL);
    for(int i=num_threads; i<num_twice; i++)
        pthread_create(&tid[i],NULL,pop,NULL);
    for(int i=0; i<num_twice; i++)
        pthread_join(tid[i],NULL);  
    return 0;
}
