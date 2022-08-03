#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <mutex>

int counter = 0;
int num_threads, limit;
std::mutex mtx;

void* count(void *var) {
    int limit = *((int*) var);

    for (size_t i = 0; i < limit; i++)
    {
        mtx.lock();
        usleep(1L);
        counter++;
        mtx.unlock();
    }
    
    return NULL;
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        num_threads = 1;
    } else {
        num_threads = strtol(argv[1], NULL, 10);
    }

    limit = 1000000 / num_threads;
    pthread_t threads[num_threads];
    
    for (size_t i = 0; i < num_threads; i++)
    {
        pthread_create(&threads[i], NULL, count, (void*) &limit);
    }
    
    for (size_t i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Used number of threads: %i\n", num_threads);
    printf("The final result of unlocked_count: %i\n", counter);

    return 0;
}
