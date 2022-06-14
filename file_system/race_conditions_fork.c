#include <stdio.h>
#include <unistd.h>

int main() {
        FILE *fp;
        fp = fopen("/lfs/mtrattner/test.txt","r"); 
        fseek(fp, 3L, SEEK_SET); 

        // Fork
        int nf = fork();
        
        if ( nf > 0 ) // Elternprozess
        {
           printf("%c | Akt.Pos. = %li, ID: %d\n", getc(fp), ftell(fp), getpid());
           //usleep(250000L);

           printf("%c | Akt.Pos. = %li, ID: %d\n", getc(fp), ftell(fp), getpid());
        }

        
        if ( nf ==  0 ) // Kindprozess
        {
           printf("%c | Akt.Pos. = %li, ID: %d\n", getc(fp), ftell(fp), getpid());
           //usleep(250000L);

           printf("%c | Akt.Pos. = %li, ID: %d\n", getc(fp), ftell(fp), getpid());
        }

        pclose (fp);
}