#include <stdio.h>
#include <unistd.h>

int main() {

        FILE *fd = fopen("/lfs/mtrattner/in.dat", "r");
        char *line = NULL;
        size_t  len = 0,  nr;

        
        // Fork
        int nf = fork();

        
        if ( nf > 0 ) // Elternprozess
        {
           nr = getline(&line, &len, fd); 
           printf("ID: %d, nr = %d \n", getpid(), (int) nr);
           printf("%s", line);
           usleep(10L);
           nr = getline(&line, &len, fd); 
           printf("ID: %d, nr = %d \n", getpid(), (int) nr);
           printf("%s", line);
        }

        
        if ( nf ==  0 ) // Kindprozess
        {
           nr = getline(&line, &len, fd); 
           printf("id: %d, nr = %d \n", getpid(), (int) nr); 
           printf("%s", line);
           usleep(10L);
           nr = getline(&line, &len, fd);
           printf("id: %d, nr = %d \n", getpid(), (int) nr);
           printf("%s", line);
        }

        pclose (fd);
}