#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int main(){

    DIR *directory;
    struct dirent *entry;
    struct stat en_info;

    directory = opendir("/mnt/c/Users/amira/CLionProjects/OS_task/week10/tmp");
    if (directory == NULL){
        printf("you did something wrong");
        return 1;
    }

    while ((entry=readdir(directory))){
        /*
        unsigned int m = en_info.st_mode;
        if (S_ISDIR(m)){
            printf("it is dir: %s\n", entry->d_name);
        }
        */
        stat(entry->d_name,&en_info);
        if( S_ISDIR(en_info.st_mode) )
            printf("%4s: %s\n","Dir",entry->d_name);
        else
            printf("%4s: %s\n","File",entry->d_name);

        if (!stat(entry->d_name, &en_info) && en_info.st_nlink >= 2) {
            printf("%lu", en_info.st_ino);
            printf("%lu", en_info.st_nlink);
        }
    }

    closedir(directory);

    return 0;
}

