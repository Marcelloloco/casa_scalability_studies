#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <mutex>

int counter = 0;
std::mutex mtx;

void* access_file(void *var) {
    pid_t x = syscall(__NR_gettid);
    int limit = *((int*) var);

    for (size_t i = 0; i < limit; i++)
    {
        mtx.lock();
        usleep(200L);
        counter++;
        mtx.unlock();
    }
    
    return NULL;
}

int main(int argc, char const *argv[])
{
    int limit = 100;

    pthread_t thread_1;
    pthread_t thread_2;

    pthread_create(&thread_1, NULL, access_file, (void*) &limit);
    pthread_create(&thread_2, NULL, access_file, (void*) &limit);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    printf("The final result: %i\n", counter);
    return 0;
}
