#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdatomic.h>
#include <pthread.h>


int lock = 0;
int locked_count = 0;
int unlocked_count = 0;


void* count(void *var) {
    pid_t x = syscall(__NR_gettid);
    int limit = *((int*) var);

    int expected = 0;
    for (size_t i = 0; i < limit; i++)
    {   
        usleep(100L);
        unlocked_count++;
        while(!atomic_compare_exchange_weak(&lock,&expected,1)) //if the lock is 0(unlock), then set it to 1(lock).
            expected = 0; //if the CAS fails, the expected will be set to 1, so we need to change it to 0 again.

        locked_count++;
        lock = 0;
    }
    
    return NULL;
}

int main(int argc, char const *argv[])
{
    int limit = 10000;

    pthread_t thread_1;
    pthread_t thread_2;

    pthread_create(&thread_1, NULL, count, (void*) &limit);
    pthread_create(&thread_2, NULL, count, (void*) &limit);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    printf("The final result of unlocked_count: %i\n", unlocked_count);
    printf("The final result of locked_count: %i\n", locked_count);
    return 0;
}
