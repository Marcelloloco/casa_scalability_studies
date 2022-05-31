/* https://stackoverflow.com/questions/26582920/mmap-memcpy-to-copy-file-from-a-to-b */
/* https://www.unix.com/programming/268879-c-unix-how-redirect-stdout-file-c-code.html */
/*https://jameshfisher.com/2017/01/27/mmap-file-read/*/
/*THIS APPLICATION DOES A MEMCPY WITH TWO MMAPFILES chunk_size=64 booksize 1024*/
#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <dirent.h>


void cflush(uint32_t *startAddr, int len)
{

    void *addr = startAddr;
    while (addr < (void *)((uint8_t *)(startAddr) + len))
    {
        uint32_t *endPtr;
        __asm__ __volatile__ (
        "clflush (%0)"
        :
        : "r" (addr)
        : "memory"
        );

    addr += 64;
    }
}

int main(int argc, char **argv){

    int sfd, dfd;
    char *src, *dest;

    struct timeval start, end;
    double delta;
    FILE * fpt;
    FILE * cfd;
    size_t filesize1;
    size_t i;


    DIR *folder;
    DIR *folder2;
    DIR *folder3;
    DIR *folder4;
    DIR *folder5;
    DIR *folder6;

    DIR *folder7;
    DIR *folder8;
    DIR *folder9;
    DIR *folder10;
    DIR *folder11;
    DIR *folder12;

    DIR *folder13;
    DIR *folder14;
    DIR *folder15;
    DIR *folder16;
    DIR *folder17;

    DIR *folder18;
    DIR *folder19;
    DIR *folder20;
    DIR *folder21;
    DIR *folder22;
    DIR *folder23;
    //DIR *folderSUB;


    struct dirent *entry;
    int files = 0;

    folder = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/");
    if(folder == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }

    while( (entry=readdir(folder)) )
    {
        files++;
        /*printf(" %s\n",
                entry->d_name
              );*/

        char fileName[255];
        strncpy(fileName, entry->d_name, 254); //strncpy(dest,src,number char)
        fileName[254] = '\0';

        char str1[] =".";
        char str2[] =".."; // in der directory werden auch . und ..gelesen
        // . und .. sollen nicht betrachtet werden, vergleich der strings
        char str3[] ="SOURCE";
        char str4[] = "POINTING";
        char str5[] = "HISTORY";
        char str6[] =  "ASDM_CALWVR";
        char str7[] = "SYSCAL";

        char str8[] ="OBSERVATION";
        char str9[] = "SORTED_TABLE";
        char str10[] = "WEATHER";
        char str11[] =  "FIELD";
        char str12[] = "FLAG_CMD";
        char str13[] ="SYSPOWER";
        char str14[] = "CALDEVICE";
        char str15[] = "ANTENNA";
        char str16[] =  "ASDM_RECEIVER";
        char str17[] = "SPECTRAL_WINDOW";
        char str18[] = "POLARIZATION";
        char str19[] = "ASDM_ANTENNA";
        char str20[] =  "ASDM_STATION";
        char str21[] = "STATE";
        char str22[] = "FEED";
        char str23[] = "DATA_DESCRIPTION";
        char str24[] = "PROCESSOR";
      //  char strsub[] = "SUBMSS";



        if (strcmp(fileName, str1) == 0){

        }
        else if (strcmp(fileName,  str2) == 0) {
          /* tue nichts, durchlaufe while weiter und hole neuen fileName */
        }
        else if (strcmp(fileName, str3)==0) {
          /* wenn Folder Source, dann gehe wieder durch den Ordner */

          folder2 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/SOURCE");
          if(folder2 == NULL)
          {
              perror("Unable to read directory");
              return(1);
          }
          while( (entry=readdir(folder2)) )
          {//while folder2 folder SOURCE
            files++;
            char fileName2[255];
            strncpy(fileName2, entry->d_name, 254); //strncpy(dest,src,number char)
            fileName2[254] = '\0';

            if (strcmp(fileName2, str1) == 0){

            }
            else if (strcmp(fileName2,  str2) == 0) {
              /* tue nichts, durchlaufe while weiter und hole neuen fileName */
            }
            else{

            //source sfd in writer_results.c in a variable stored
            char format_s[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
            char filename_s[sizeof format_s+100];
            sprintf(filename_s,format_s,fileName,fileName2);
            printf("%s\n", filename_s );

            //destination dfd in writer_results.c stored in a variable
            char format_s_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
            char filename_s_dfd[sizeof format_s_dfd+100];
            sprintf(filename_s_dfd,format_s_dfd,fileName,fileName2);
            printf("%s\n", filename_s_dfd );

            //from writer_results
            /* SOURCE */
            // variable here in open
            sfd = open(filename_s, O_RDONLY);

              if (sfd < 0)
            {
                perror("c1");
                exit(1);
            }
            printf("opened the fd = % d\n", sfd);

            filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
            lseek(sfd, 0, SEEK_SET);
            char *cpsrc, *cpdest;

            src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
            cpsrc = src;

            /* DESTINATION */
            // variable here in open
            dfd = open(filename_s_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

              if (dfd < 0)
            {
                perror("c1");
                exit(1);
            }
            printf("opened the dfd = % d\n", dfd);

            ftruncate(dfd, filesize1);

            dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
            cpdest = dest;

            if (dest == MAP_FAILED) {
              close(dfd);
              perror("Error mmapping the file");
              exit(EXIT_FAILURE);
            }
            /* COPY */
            {
            #define DEF_SIZE 64;
                  size_t chunk_size = DEF_SIZE;
                  char *odest = dest;
                  char *osrc = src;
                  for (i = 0; i < filesize1; i+= chunk_size)
                  {
                    if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
                    //cflush((uint32_t *)src, chunk_size);
                    memcpy(dest, src, chunk_size);
                    cflush((uint32_t *)dest, chunk_size);
              dest += chunk_size;
              src += chunk_size;

                  }
                }

            /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

            //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
              //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
            int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
              if (-1 == err) { perror("opening cerr.log"); return 255; }

            //int save_out = dup(fileno(stdout));
            int save_err = dup(fileno(stderr));

            //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
            if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

            fflush(stderr); close(err);

            //dup2(save_out, fileno(stdout));
            dup2(save_err, fileno(stderr));

            //close(save_out);
            close(save_err);

            munmap(cpsrc, filesize1);
            munmap(cpdest, filesize1);

            close(sfd);
            printf("closed the sfd = % d\n", sfd);
            close(dfd);
            printf("closed the dfd = % d\n", dfd);


          }

          }//while folder2
          closedir(folder2);
        }//elseif str3
        else if (strcmp(fileName, str4)==0) {
          /* wenn Folder Source, dann gehe wieder durch den Ordner */

          folder3 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/POINTING");
          if(folder3 == NULL)
          {
              perror("Unable to read directory");
              return(1);
          }
          while( (entry=readdir(folder3)) )
          {//while folder3 folder POINTING
            files++;
            char fileName3[255];
            strncpy(fileName3, entry->d_name, 254); //strncpy(dest,src,number char)
            fileName3[254] = '\0';

            if (strcmp(fileName3, str1) == 0){

            }
            else if (strcmp(fileName3,  str2) == 0) {
              /* tue nichts, durchlaufe while weiter und hole neuen fileName */
            }
            else{

            //source sfd in writer_results.c in a variable stored
            char format_p[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
            char filename_p[sizeof format_p+100];
            sprintf(filename_p,format_p,fileName,fileName3);
            printf("%s\n", filename_p );

            //destination dfd in writer_results.c stored in a variable
            char format_p_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
            char filename_p_dfd[sizeof format_p_dfd+100];
            sprintf(filename_p_dfd,format_p_dfd,fileName,fileName3);
            printf("%s\n", filename_p_dfd );

            //from writer_results
            /* SOURCE */
            // variable here in open
            sfd = open(filename_p, O_RDONLY);

              if (sfd < 0)
            {
                perror("c1");
                exit(1);
            }
            printf("opened the fd = % d\n", sfd);

            filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
            lseek(sfd, 0, SEEK_SET);
            char *cpsrc, *cpdest;

            src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
            cpsrc = src;

            /* DESTINATION */
            // variable here in open
            dfd = open(filename_p_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

              if (dfd < 0)
            {
                perror("c1");
                exit(1);
            }
            printf("opened the dfd = % d\n", dfd);

            ftruncate(dfd, filesize1);

            dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
            cpdest = dest;
            if (dest == MAP_FAILED) {
              close(dfd);
              perror("Error mmapping the file");
              exit(EXIT_FAILURE);
            }
            /* COPY */
            {
            #define DEF_SIZE 64;
                  size_t chunk_size = DEF_SIZE;
                  char *odest = dest;
                  char *osrc = src;
                  for (i = 0; i < filesize1; i+= chunk_size)
                  {
                    if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
                    //cflush((uint32_t *)src, chunk_size);
                    memcpy(dest, src, chunk_size);
                    cflush((uint32_t *)dest, chunk_size);
              dest += chunk_size;
              src += chunk_size;

                  }
                }

            /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

            //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
              //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
            int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
              if (-1 == err) { perror("opening cerr.log"); return 255; }

            //int save_out = dup(fileno(stdout));
            int save_err = dup(fileno(stderr));

            //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
            if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

            fflush(stderr); close(err);

            //dup2(save_out, fileno(stdout));
            dup2(save_err, fileno(stderr));

            //close(save_out);
            close(save_err);

            munmap(cpsrc, filesize1);
            munmap(cpdest, filesize1);

            close(sfd);
            printf("closed the sfd = % d\n", sfd);
            close(dfd);
            printf("closed the dfd = % d\n", dfd);


          }

        }//while folder3
        closedir(folder3);
        }//elseif str4 = POINTING

        else if (strcmp(fileName, str5)==0) {
          /* wenn Folder HISTORY, dann gehe wieder durch den Ordner */

          folder4 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/HISTORY");
          if(folder4 == NULL)
          {
              perror("Unable to read directory");
              return(1);
          }
          while( (entry=readdir(folder4)) )
          {//while folder4 folder HISTORY
            files++;
            char fileName5[255];
            strncpy(fileName5, entry->d_name, 254); //strncpy(dest,src,number char)
            fileName5[254] = '\0';

            if (strcmp(fileName5, str1) == 0){

            }
            else if (strcmp(fileName5,  str2) == 0) {
              /* tue nichts, durchlaufe while weiter und hole neuen fileName */
            }
            else{

            //source sfd in writer_results.c in a variable stored
            char format_h[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
            char filename_h[sizeof format_h+100];
            sprintf(filename_h,format_h,fileName,fileName5);
            printf("%s\n", filename_h );

            //destination dfd in writer_results.c stored in a variable
            char format_h_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
            char filename_h_dfd[sizeof format_h_dfd+100];
            sprintf(filename_h_dfd,format_h_dfd,fileName,fileName5);
            printf("%s\n", filename_h_dfd );

            //from writer_results
            /* SOURCE */
            // variable here in open
            sfd = open(filename_h, O_RDONLY);

              if (sfd < 0)
            {
                perror("c1");
                exit(1);
            }
            printf("opened the fd = % d\n", sfd);

            filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
            lseek(sfd, 0, SEEK_SET);
            char *cpsrc, *cpdest;
            src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
            cpsrc = src;

            /* DESTINATION */
            // variable here in open
            dfd = open(filename_h_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

              if (dfd < 0)
            {
                perror("c1");
                exit(1);
            }
            printf("opened the dfd = % d\n", dfd);

            ftruncate(dfd, filesize1);

            dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
            cpdest = dest;

            if (dest == MAP_FAILED) {
              close(dfd);
              perror("Error mmapping the file");
              exit(EXIT_FAILURE);
            }
            /* COPY */
            {
            #define DEF_SIZE 64;
                  size_t chunk_size = DEF_SIZE;
                  char *odest = dest;
                  char *osrc = src;
                  for (i = 0; i < filesize1; i+= chunk_size)
                  {
                    if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
                    //cflush((uint32_t *)src, chunk_size);
                    memcpy(dest, src, chunk_size);
                    cflush((uint32_t *)dest, chunk_size);
              dest += chunk_size;
              src += chunk_size;

                  }
                }

            /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

            //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
              //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
            int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
              if (-1 == err) { perror("opening cerr.log"); return 255; }

            //int save_out = dup(fileno(stdout));
            int save_err = dup(fileno(stderr));

            //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
            if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

            fflush(stderr); close(err);

            //dup2(save_out, fileno(stdout));
            dup2(save_err, fileno(stderr));

            //close(save_out);
            close(save_err);

            munmap(cpsrc, filesize1);
            munmap(cpdest, filesize1);

            close(sfd);
            printf("closed the sfd = % d\n", sfd);
            close(dfd);
            printf("closed the dfd = % d\n", dfd);


          }

        }//while folder4
        closedir(folder4);
      }//elseif str5 HISTORY

      else if (strcmp(fileName, str6)==0) {
        /* wenn Folder ASDM_CALWVR, dann gehe wieder durch den Ordner */

        folder5 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/ASDM_CALWVR");
        if(folder5 == NULL)
        {
            perror("Unable to read directory");
            return(1);
        }
        while( (entry=readdir(folder5)) )
        {//while folder4 folder HISTORY
          files++;
          char fileName6[255];
          strncpy(fileName6, entry->d_name, 254); //strncpy(dest,src,number char)
          fileName6[254] = '\0';

          if (strcmp(fileName6, str1) == 0){

          }
          else if (strcmp(fileName6,  str2) == 0) {
            /* tue nichts, durchlaufe while weiter und hole neuen fileName */
          }
          else{

          //source sfd in writer_results.c in a variable stored
          char format_as[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
          char filename_as[sizeof format_as+100];
          sprintf(filename_as,format_as,fileName,fileName6);
          printf("%s\n", filename_as );

          //destination dfd in writer_results.c stored in a variable
          char format_as_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
          char filename_as_dfd[sizeof format_as_dfd+100];
          sprintf(filename_as_dfd,format_as_dfd,fileName,fileName6);
          printf("%s\n", filename_as_dfd );

          //from writer_results
          /* SOURCE */
          // variable here in open
          sfd = open(filename_as, O_RDONLY);

            if (sfd < 0)
          {
              perror("c1");
              exit(1);
          }
          printf("opened the fd = % d\n", sfd);

          filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
          lseek(sfd, 0, SEEK_SET);
          char *cpsrc, *cpdest;
          src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
          cpsrc = src;

          /* DESTINATION */
          // variable here in open
          dfd = open(filename_as_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

            if (dfd < 0)
          {
              perror("c1");
              exit(1);
          }
          printf("opened the dfd = % d\n", dfd);

          ftruncate(dfd, filesize1);

          dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
          cpdest = dest;

          if (dest == MAP_FAILED) {
            close(dfd);
            perror("Error mmapping the file");
            exit(EXIT_FAILURE);
          }
          /* COPY */
          {
          #define DEF_SIZE 64;
                size_t chunk_size = DEF_SIZE;
                char *odest = dest;
                char *osrc = src;
                for (i = 0; i < filesize1; i+= chunk_size)
                {
                  if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
                  //cflush((uint32_t *)src, chunk_size);
                  memcpy(dest, src, chunk_size);
                  cflush((uint32_t *)dest, chunk_size);
            dest += chunk_size;
            src += chunk_size;

                }
              }

          /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

          //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
            //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
          int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
            if (-1 == err) { perror("opening cerr.log"); return 255; }

          //int save_out = dup(fileno(stdout));
          int save_err = dup(fileno(stderr));

          //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
          if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

          fflush(stderr); close(err);

          //dup2(save_out, fileno(stdout));
          dup2(save_err, fileno(stderr));

          //close(save_out);
          close(save_err);

          munmap(cpsrc, filesize1);
          munmap(cpdest, filesize1);

          close(sfd);
          printf("closed the sfd = % d\n", sfd);
          close(dfd);
          printf("closed the dfd = % d\n", dfd);


        }

      }//while folder5
      closedir(folder5);
    }//elseif str6 ASDM_CALWVR

    else if (strcmp(fileName, str7)==0) {
      /* wenn Folder SYSCAL, dann gehe wieder durch den Ordner */

      folder6 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/SYSCAL");
      if(folder6 == NULL)
      {
          perror("Unable to read directory");
          return(1);
      }
      while( (entry=readdir(folder6)) )
      {//while folder6 folder HISTORY
        files++;
        char fileName7[255];
        strncpy(fileName7, entry->d_name, 254); //strncpy(dest,src,number char)
        fileName7[254] = '\0';

        if (strcmp(fileName7, str1) == 0){

        }
        else if (strcmp(fileName7,  str2) == 0) {
          /* tue nichts, durchlaufe while weiter und hole neuen fileName */
        }
        else{

        //source sfd in writer_results.c in a variable stored
        char format_sy[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
        char filename_sy[sizeof format_sy+100];
        sprintf(filename_sy,format_sy,fileName,fileName7);
        printf("%s\n", filename_sy );

        //destination dfd in writer_results.c stored in a variable
        char format_sy_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
        char filename_sy_dfd[sizeof format_sy_dfd+100];
        sprintf(filename_sy_dfd,format_sy_dfd,fileName,fileName7);
        printf("%s\n", filename_sy_dfd );

        //from writer_results
        /* SOURCE */
        // variable here in open
        sfd = open(filename_sy, O_RDONLY);

          if (sfd < 0)
        {
            perror("c1");
            exit(1);
        }
        printf("opened the fd = % d\n", sfd);

        filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
        lseek(sfd, 0, SEEK_SET);
        char *cpsrc, *cpdest;
        src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
        cpsrc = src;

        /* DESTINATION */
        // variable here in open
        dfd = open(filename_sy_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

          if (dfd < 0)
        {
            perror("c1");
            exit(1);
        }
        printf("opened the dfd = % d\n", dfd);

        ftruncate(dfd, filesize1);

        dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
        cpdest = dest;

        if (dest == MAP_FAILED) {
          close(dfd);
          perror("Error mmapping the file");
          exit(EXIT_FAILURE);
        }
        /* COPY */
        {
        #define DEF_SIZE 64;
              size_t chunk_size = DEF_SIZE;
              char *odest = dest;
              char *osrc = src;
              for (i = 0; i < filesize1; i+= chunk_size)
              {
                if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
                //cflush((uint32_t *)src, chunk_size);
                memcpy(dest, src, chunk_size);
                cflush((uint32_t *)dest, chunk_size);
          dest += chunk_size;
          src += chunk_size;

              }
            }

        /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

        //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
          //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
        int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
          if (-1 == err) { perror("opening cerr.log"); return 255; }

        //int save_out = dup(fileno(stdout));
        int save_err = dup(fileno(stderr));

        //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
        if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

        fflush(stderr); close(err);

        //dup2(save_out, fileno(stdout));
        dup2(save_err, fileno(stderr));

        //close(save_out);
        close(save_err);

        munmap(cpsrc, filesize1);
        munmap(cpdest, filesize1);

        close(sfd);
        printf("closed the sfd = % d\n", sfd);
        close(dfd);
        printf("closed the dfd = % d\n", dfd);


      }

    }//while folder6
    closedir(folder6);
  }//elseif str7 SYSCAL fileName7

  else if (strcmp(fileName, str8)==0) {
    /* wenn Folder SYSCAL, dann gehe wieder durch den Ordner */

    folder7 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/OBSERVATION");
    if(folder7 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder7)) )
    {//while folder7 folder OBSERVATION
      files++;
      char fileName8[255];
      strncpy(fileName8, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName8[254] = '\0';

      if (strcmp(fileName8, str1) == 0){

      }
      else if (strcmp(fileName8,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_o[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_o[sizeof format_o+100];
      sprintf(filename_o,format_o,fileName,fileName8);
      printf("%s\n", filename_o );

      //destination dfd in writer_results.c stored in a variable
      char format_o_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_o_dfd[sizeof format_o_dfd+100];
      sprintf(filename_o_dfd,format_o_dfd,fileName,fileName8);
      printf("%s\n", filename_o_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_o, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_o_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder7
  closedir(folder7);
  }//elseif str8 OBSERVATION fileName8

  //SUBMS comes here for now ignore submss
  //else if (strcmp(fileName, strsub)==0) {
    /* wenn Folder SYSCAL, dann gehe wieder durch den Ordner */

    //folderSUB = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/SUBMSS");
    //if(folderSUB == NULL)
    //{
      //  perror("Unable to read directory");
        //return(1);
  //  }
    //closedir(folderSUB);

  //}//elseif strsub SUBMSS

  // SUBMS end here

  else if (strcmp(fileName, str9)==0) {
    /* wenn Folder SYSCAL, dann gehe wieder durch den Ordner */

    folder8 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/SORTED_TABLE");
    if(folder8 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder8)) )
    {//while folder8 folder SORTED_TABLE
      files++;
      char fileName9[255];
      strncpy(fileName9, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName9[254] = '\0';

      if (strcmp(fileName9, str1) == 0){

      }
      else if (strcmp(fileName9,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_st[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_st[sizeof format_st+100];
      sprintf(filename_st,format_st,fileName,fileName9);
      printf("%s\n", filename_st );

      //destination dfd in writer_results.c stored in a variable
      char format_st_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_st_dfd[sizeof format_st_dfd+100];
      sprintf(filename_st_dfd,format_st_dfd,fileName,fileName9);
      printf("%s\n", filename_st_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_st, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_st_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder8
  closedir(folder8);
  }//elseif str9 SORTED_TABLE fileName9

  else if (strcmp(fileName, str10)==0) {
    /* wenn Folder WEATHER, dann gehe wieder durch den Ordner */

    folder9 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/WEATHER");
    if(folder9 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder9)) )
    {//while folder9 folder SORTED_TABLE
      files++;
      char fileName10[255];
      strncpy(fileName10, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName10[254] = '\0';

      if (strcmp(fileName10, str1) == 0){

      }
      else if (strcmp(fileName10,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_w[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_w[sizeof format_w+100];
      sprintf(filename_w,format_w,fileName,fileName10);
      printf("%s\n", filename_w );

      //destination dfd in writer_results.c stored in a variable
      char format_w_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_w_dfd[sizeof format_w_dfd+100];
      sprintf(filename_w_dfd,format_w_dfd,fileName,fileName10);
      printf("%s\n", filename_w_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_w, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_w_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder9
  closedir(folder9);
  }//elseif str10 WEATHER fileName10

  else if (strcmp(fileName, str11)==0) {
    /* wenn Folder FIELD, dann gehe wieder durch den Ordner */

    folder10 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/FIELD");
    if(folder10 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder10)) )
    {//while folder10 folder FIELD
      files++;
      char fileName11[255];
      strncpy(fileName11, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName11[254] = '\0';

      if (strcmp(fileName11, str1) == 0){

      }
      else if (strcmp(fileName11,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_fie[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_fie[sizeof format_fie+100];
      sprintf(filename_fie,format_fie,fileName,fileName11);
      printf("%s\n", filename_fie );

      //destination dfd in writer_results.c stored in a variable
      char format_fie_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_fie_dfd[sizeof format_fie_dfd+100];
      sprintf(filename_fie_dfd,format_fie_dfd,fileName,fileName11);
      printf("%s\n", filename_fie_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_fie, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_fie_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder10
  closedir(folder10);
  }//elseif str11 FIELD fileName11

  else if (strcmp(fileName, str12)==0) {
    /* wenn Folder FLAG_CMD, dann gehe wieder durch den Ordner */

    folder11 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/FLAG_CMD");
    if(folder11 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder11)) )
    {//while folder11 folder FLAG_CMD
      files++;
      char fileName12[255];
      strncpy(fileName12, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName12[254] = '\0';

      if (strcmp(fileName12, str1) == 0){

      }
      else if (strcmp(fileName12,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_flag[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_flag[sizeof format_flag+100];
      sprintf(filename_flag,format_flag,fileName,fileName12);
      printf("%s\n", filename_flag );

      //destination dfd in writer_results.c stored in a variable
      char format_flag_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_flag_dfd[sizeof format_flag_dfd+100];
      sprintf(filename_flag_dfd,format_flag_dfd,fileName,fileName12);
      printf("%s\n", filename_flag_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_flag, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_flag_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder11
  closedir(folder11);
  }//elseif str12 FLAG_CMD fileName12

  else if (strcmp(fileName, str13)==0) {
    /* wenn Folder SYSPOWER, dann gehe wieder durch den Ordner */

    folder12 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/SYSPOWER");
    if(folder12 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder12)) )
    {//while folder12 folder SYSPOWER
      files++;
      char fileName13[255];
      strncpy(fileName13, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName13[254] = '\0';

      if (strcmp(fileName13, str1) == 0){

      }
      else if (strcmp(fileName13,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_sysp[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_sysp[sizeof format_sysp+100];
      sprintf(filename_sysp,format_sysp,fileName,fileName13);
      printf("%s\n", filename_sysp );

      //destination dfd in writer_results.c stored in a variable
      char format_sysp_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_sysp_dfd[sizeof format_sysp_dfd+100];
      sprintf(filename_sysp_dfd,format_sysp_dfd,fileName,fileName13);
      printf("%s\n", filename_sysp_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_sysp, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_sysp_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder12
  closedir(folder12);
  }//elseif str13 SYSPOWER fileName13

  else if (strcmp(fileName, str14)==0) {
    /* wenn Folder CALDEVICE, dann gehe wieder durch den Ordner */

    folder13 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/CALDEVICE");
    if(folder13 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder13)) )
    {//while folder13 folder CALDEVICE
      files++;
      char fileName14[255];
      strncpy(fileName14, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName14[254] = '\0';

      if (strcmp(fileName14, str1) == 0){

      }
      else if (strcmp(fileName14,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_cal[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_cal[sizeof format_cal+100];
      sprintf(filename_cal,format_cal,fileName,fileName14);
      printf("%s\n", filename_cal );

      //destination dfd in writer_results.c stored in a variable
      char format_cal_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_cal_dfd[sizeof format_cal_dfd+100];
      sprintf(filename_cal_dfd,format_cal_dfd,fileName,fileName14);
      printf("%s\n", filename_cal_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_cal, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_cal_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder13
  closedir(folder13);
  }//elseif str14 CALDEVICE fileName14

  else if (strcmp(fileName, str15)==0) {
    /* wenn Folder ANTENNA, dann gehe wieder durch den Ordner */

    folder14 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/ANTENNA");
    if(folder14 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder14)) )
    {//while folder14 folder ANTENNA
      files++;
      char fileName15[255];
      strncpy(fileName15, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName15[254] = '\0';

      if (strcmp(fileName15, str1) == 0){

      }
      else if (strcmp(fileName15,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_ant[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_ant[sizeof format_ant+100];
      sprintf(filename_ant,format_ant,fileName,fileName15);
      printf("%s\n", filename_ant );

      //destination dfd in writer_results.c stored in a variable
      char format_ant_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_ant_dfd[sizeof format_ant_dfd+100];
      sprintf(filename_ant_dfd,format_ant_dfd,fileName,fileName15);
      printf("%s\n", filename_ant_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_ant, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_ant_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder14
  closedir(folder14);
  }//elseif str15 ANTENNA fileName15

  else if (strcmp(fileName, str16)==0) {
    /* wenn Folder ASDM_RECEIVER, dann gehe wieder durch den Ordner */

    folder15 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/ASDM_RECEIVER");
    if(folder15 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder15)) )
    {//while folder15 folder ASDM_RECEIVER
      files++;
      char fileName16[255];
      strncpy(fileName16, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName16[254] = '\0';

      if (strcmp(fileName16, str1) == 0){

      }
      else if (strcmp(fileName16,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_asr[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_asr[sizeof format_asr+100];
      sprintf(filename_asr,format_asr,fileName,fileName16);
      printf("%s\n", filename_asr );

      //destination dfd in writer_results.c stored in a variable
      char format_asr_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_asr_dfd[sizeof format_asr_dfd+100];
      sprintf(filename_asr_dfd,format_asr_dfd,fileName,fileName16);
      printf("%s\n", filename_asr_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_asr, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_asr_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder15
  closedir(folder15);
  }//elseif str16 ASDM_RECEIVER fileName16

  else if (strcmp(fileName, str17)==0) {
    /* wenn Folder SPECTRAL_WINDOW, dann gehe wieder durch den Ordner */

    folder16 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/SPECTRAL_WINDOW");
    if(folder16 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder16)) )
    {//while folder16 folder SPECTRAL_WINDOW
      files++;
      char fileName17[255];
      strncpy(fileName17, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName17[254] = '\0';

      if (strcmp(fileName17, str1) == 0){

      }
      else if (strcmp(fileName17,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_spw[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_spw[sizeof format_spw+100];
      sprintf(filename_spw,format_spw,fileName,fileName17);
      printf("%s\n", filename_spw );

      //destination dfd in writer_results.c stored in a variable
      char format_spw_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_spw_dfd[sizeof format_spw_dfd+100];
      sprintf(filename_spw_dfd,format_spw_dfd,fileName,fileName17);
      printf("%s\n", filename_spw_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_spw, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_spw_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder16
  closedir(folder16);
  }//elseif str17 SPECTRAL_WINDOW fileName17

  else if (strcmp(fileName, str18)==0) {
    /* wenn Folder POLARIZATION, dann gehe wieder durch den Ordner */

    folder17 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/POLARIZATION");
    if(folder17 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder17)) )
    {//while folder17 folder POLARIZATION
      files++;
      char fileName18[255];
      strncpy(fileName18, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName18[254] = '\0';

      if (strcmp(fileName18, str1) == 0){

      }
      else if (strcmp(fileName18,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_pol[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_pol[sizeof format_pol+100];
      sprintf(filename_pol,format_pol,fileName,fileName18);
      printf("%s\n", filename_pol );

      //destination dfd in writer_results.c stored in a variable
      char format_pol_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_pol_dfd[sizeof format_pol_dfd+100];
      sprintf(filename_pol_dfd,format_pol_dfd,fileName,fileName18);
      printf("%s\n", filename_pol_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_pol, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_pol_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder17
  closedir(folder17);
  }//elseif str18 POLARIZATION fileName18

  else if (strcmp(fileName, str19)==0) {
    /* wenn Folder ASDM_ANTENNA, dann gehe wieder durch den Ordner */

    folder18 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/ASDM_ANTENNA");
    if(folder18 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder18)) )
    {//while folder18 folder ASDM_ANTENNA
      files++;
      char fileName19[255];
      strncpy(fileName19, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName19[254] = '\0';

      if (strcmp(fileName19, str1) == 0){

      }
      else if (strcmp(fileName19,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_aa[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_aa[sizeof format_aa+100];
      sprintf(filename_aa,format_aa,fileName,fileName19);
      printf("%s\n", filename_aa );

      //destination dfd in writer_results.c stored in a variable
      char format_aa_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_aa_dfd[sizeof format_aa_dfd+100];
      sprintf(filename_aa_dfd,format_aa_dfd,fileName,fileName19);
      printf("%s\n", filename_aa_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_aa, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_aa_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder18
  closedir(folder18);
  }//elseif str19 ASDM_ANTENNA fileName19

  else if (strcmp(fileName, str20)==0) {
    /* wenn Folder ASDM_STATION, dann gehe wieder durch den Ordner */

    folder19 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/ASDM_STATION");
    if(folder19 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder19)) )
    {//while folder19 folder ASDM_STATION
      files++;
      char fileName20[255];
      strncpy(fileName20, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName20[254] = '\0';

      if (strcmp(fileName20, str1) == 0){

      }
      else if (strcmp(fileName20,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_ast[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_ast[sizeof format_ast+100];
      sprintf(filename_ast,format_ast,fileName,fileName20);
      printf("%s\n", filename_ast );

      //destination dfd in writer_results.c stored in a variable
      char format_ast_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_ast_dfd[sizeof format_ast_dfd+100];
      sprintf(filename_ast_dfd,format_ast_dfd,fileName,fileName20);
      printf("%s\n", filename_ast_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_ast, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_ast_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder19
  closedir(folder19);
  }//elseif str20 ASDM_STATION fileName20

  else if (strcmp(fileName, str21)==0) {
    /* wenn Folder STATE, dann gehe wieder durch den Ordner */

    folder20 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/STATE");
    if(folder20 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder20)) )
    {//while folder20 folder STATE
      files++;
      char fileName21[255];
      strncpy(fileName21, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName21[254] = '\0';

      if (strcmp(fileName21, str1) == 0){

      }
      else if (strcmp(fileName21,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_state[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_state[sizeof format_state+100];
      sprintf(filename_state,format_state,fileName,fileName21);
      printf("%s\n", filename_state );

      //destination dfd in writer_results.c stored in a variable
      char format_state_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_state_dfd[sizeof format_state_dfd+100];
      sprintf(filename_state_dfd,format_state_dfd,fileName,fileName21);
      printf("%s\n", filename_state_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_state, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_state_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder20
  closedir(folder20);
  }//elseif str21 STATE fileName21

  else if (strcmp(fileName, str22)==0) {
    /* wenn Folder FEED, dann gehe wieder durch den Ordner */

    folder21 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/FEED");
    if(folder21 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder21)) )
    {//while folder21 folder FEED
      files++;
      char fileName22[255];
      strncpy(fileName22, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName22[254] = '\0';

      if (strcmp(fileName22, str1) == 0){

      }
      else if (strcmp(fileName22,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_FEED[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_FEED[sizeof format_FEED+100];
      sprintf(filename_FEED,format_FEED,fileName,fileName22);
      printf("%s\n", filename_FEED );

      //destination dfd in writer_results.c stored in a variable
      char format_FEED_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_FEED_dfd[sizeof format_FEED_dfd+100];
      sprintf(filename_FEED_dfd,format_FEED_dfd,fileName,fileName22);
      printf("%s\n", filename_FEED_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_FEED, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_FEED_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder21
  closedir(folder21);
  }//elseif str22 FEED fileName22

  else if (strcmp(fileName, str23)==0) {
    /* wenn Folder DATA_DESCRIPTION, dann gehe wieder durch den Ordner */

    folder22 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/DATA_DESCRIPTION");
    if(folder22 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder22)) )
    {//while folder22 folder DATA_DESCRIPTION
      files++;
      char fileName23[255];
      strncpy(fileName23, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName23[254] = '\0';

      if (strcmp(fileName23, str1) == 0){

      }
      else if (strcmp(fileName23,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_DATA_DESCRIPTION[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_DATA_DESCRIPTION[sizeof format_DATA_DESCRIPTION+100];
      sprintf(filename_DATA_DESCRIPTION,format_DATA_DESCRIPTION,fileName,fileName23);
      printf("%s\n", filename_DATA_DESCRIPTION );

      //destination dfd in writer_results.c stored in a variable
      char format_DATA_DESCRIPTION_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_DATA_DESCRIPTION_dfd[sizeof format_DATA_DESCRIPTION_dfd+100];
      sprintf(filename_DATA_DESCRIPTION_dfd,format_DATA_DESCRIPTION_dfd,fileName,fileName23);
      printf("%s\n", filename_DATA_DESCRIPTION_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_DATA_DESCRIPTION, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_DATA_DESCRIPTION_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder22
  closedir(folder22);
}//elseif str23 DATA_DESCRIPTION fileName23

  else if (strcmp(fileName, str24)==0) {
    /* wenn Folder PROCESSOR, dann gehe wieder durch den Ordner */

    folder23 = opendir("/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/PROCESSOR");
    if(folder23 == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }
    while( (entry=readdir(folder23)) )
    {//while folder23 folder PROCESSOR
      files++;
      char fileName24[255];
      strncpy(fileName24, entry->d_name, 254); //strncpy(dest,src,number char)
      fileName24[254] = '\0';

      if (strcmp(fileName24, str1) == 0){

      }
      else if (strcmp(fileName24,  str2) == 0) {
        /* tue nichts, durchlaufe while weiter und hole neuen fileName */
      }
      else{

      //source sfd in writer_results.c in a variable stored
      char format_PROCESSOR[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_PROCESSOR[sizeof format_PROCESSOR+100];
      sprintf(filename_PROCESSOR,format_PROCESSOR,fileName,fileName24);
      printf("%s\n", filename_PROCESSOR );

      //destination dfd in writer_results.c stored in a variable
      char format_PROCESSOR_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s/%s";
      char filename_PROCESSOR_dfd[sizeof format_PROCESSOR_dfd+100];
      sprintf(filename_PROCESSOR_dfd,format_PROCESSOR_dfd,fileName,fileName24);
      printf("%s\n", filename_PROCESSOR_dfd );

      //from writer_results
      /* SOURCE */
      // variable here in open
      sfd = open(filename_PROCESSOR, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;

      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;

      /* DESTINATION */
      // variable here in open
      dfd = open(filename_PROCESSOR_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;

      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);


    }

  }//while folder23
  closedir(folder23);
  }//elseif str24 PROCESSOR fileName24

//insert


        else{//anfang des Ordners

      //source sfd in writer_results.c in a variable stored
      char format[] = "/data/testdata/schaaf/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s";
      char filename[sizeof format+100];
      sprintf(filename,format,fileName);
      printf("%s\n", filename );

      //destination dfd in writer_results.c stored in a variable
      char format_dfd[] = "/lfs/Antennae_Band7_CalibratedData/Antennae_North.cal.ms/%s";
      char filename_dfd[sizeof format_dfd+100];
      sprintf(filename_dfd,format_dfd,fileName);
      printf("%s\n", filename_dfd );

      /* SOURCE */
      // variable here in open
      sfd = open(filename, O_RDONLY);

        if (sfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the fd = % d\n", sfd);

      filesize1 = lseek(sfd, 0, SEEK_END); //oder 0
      lseek(sfd, 0, SEEK_SET);
      char *cpsrc, *cpdest;
      src = mmap(NULL, filesize1, PROT_READ, MAP_SHARED, sfd, 0);
      cpsrc = src;
      /* DESTINATION */
      // variable here in open
      dfd = open(filename_dfd, O_RDWR | O_CREAT | O_SYNC, 0777);

        if (dfd < 0)
      {
          perror("c1");
          exit(1);
      }
      printf("opened the dfd = % d\n", dfd);

      ftruncate(dfd, filesize1);

      dest = mmap(NULL, filesize1, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
      cpdest = dest;
      if (dest == MAP_FAILED) {
        close(dfd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
      }
      /* COPY */
      {
      #define DEF_SIZE 64;
            size_t chunk_size = DEF_SIZE;
            char *odest = dest;
            char *osrc = src;
            for (i = 0; i < filesize1; i+= chunk_size)
            {
              if ((filesize1 - i) < chunk_size) { chunk_size = filesize1 - i; }
              //cflush((uint32_t *)src, chunk_size);
              memcpy(dest, src, chunk_size);
              cflush((uint32_t *)dest, chunk_size);
        dest += chunk_size;
        src += chunk_size;

            }
          }

      /* HELPER FUNCTION TO WRITE ALL STDOUT TO FILE*/

      //int out = open("/data/testdata/from_mem.txt", O_RDWR|O_CREAT|O_APPEND, 0600);
        //if (-1 == out) { perror("opening from_mem.txt"); return 255; }
      int err = open("/tmp/cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
        if (-1 == err) { perror("opening cerr.log"); return 255; }

      //int save_out = dup(fileno(stdout));
      int save_err = dup(fileno(stderr));

      //if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
      if (-1 == dup2(err, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

      fflush(stderr); close(err);

      //dup2(save_out, fileno(stdout));
      dup2(save_err, fileno(stderr));

      //close(save_out);
      close(save_err);

      munmap(cpsrc, filesize1);
      munmap(cpdest, filesize1);

      close(sfd);
      printf("closed the sfd = % d\n", sfd);
      close(dfd);
      printf("closed the dfd = % d\n", dfd);

    }
    }

    closedir(folder);
    //closedir(folder2);
  /*  closedir(folder3);
    closedir(folder4);
    closedir(folder5);

    closedir(folder6);
    closedir(folder7);
    closedir(folder8);
    closedir(folder9);
    closedir(folder10);

    closedir(folder11);
    closedir(folder12);
    closedir(folder13);
    closedir(folder14);
    closedir(folder15);

    closedir(folder16);
    closedir(folder17);
    closedir(folder18);
    closedir(folder19);
    closedir(folder20);

    closedir(folder21);
    closedir(folder22);
    closedir(folder23);*/

return 0;
}
