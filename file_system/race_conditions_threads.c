#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>

void* access_file(void *stream) {
    pid_t x = syscall(__NR_gettid);
    FILE *fp = (FILE*) stream;

    fseek(fp, 3L, SEEK_SET); 
    usleep(10L);

    printf("%c | Akt.Pos. = %li, ID: %d\n", getc(fp), ftell(fp), x); 
    
    return NULL;
}

int main() {
    FILE *fp;
    fp = fopen("/lfs/mtrattner/test.txt","r"); 

    pthread_t thread_1;
    pthread_t thread_2;

    pthread_create(&thread_1, NULL, access_file, (void*) fp);
    pthread_create(&thread_2, NULL, access_file, (void*) fp);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    pclose (fp);
}