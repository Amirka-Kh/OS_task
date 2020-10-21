//
// This code works on linux terminal
//

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

    struct dirent * a[10];              // array of pointers to the next directory entry
    int index = 0;                      // index in ino_s array


    while ((entry=readdir(directory))){

        stat(entry->d_name,&en_info);
        printf("links -> %s %lu\n",entry->d_name, en_info.st_nlink);

        if (en_info.st_nlink >= 2) {
            a[index] = entry;
            index++;
        }
    }

    for (int i = 0; i < index; i++){
        printf("%s %lu\n",a[i]->d_name, a[i]->d_ino);
    }

    closedir(directory);

    return 0;
}

