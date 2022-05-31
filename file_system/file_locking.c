#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(){
    int fd, N_bytes=16;
    char *map_addr;
    fd = open( "test.txt", O_RDWR);
    map_addr = mmap(0,N_bytes,PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);

    //*(map_addr+1) = '_';
    write(1,map_addr, N_bytes);

    munmap(map_addr, N_bytes);
    return(0);
}