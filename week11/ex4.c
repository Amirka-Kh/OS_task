#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define MAXCHAR 1000

int main (int argc, char *argv[]) {

    char str[MAXCHAR];
    FILE *fp;
    int in, out;
    char *src, *dst;
    struct stat statbuf;
    int mode = 0x0777;

    // open the input file 
    in = open (argv[1], O_RDONLY);
    fp = fopen(argv[1], "r");
    fgets(str, MAXCHAR, fp);

    // open/create the output file 
    out = open (argv[2], O_RDWR | O_CREAT | O_TRUNC, mode );

    // find size of input file 
    fstat(in, &statbuf);

    // write a dummy byte at the last location
    for (int i = 0; i < statbuf.st_size; i++) {
        write(out, str+i, 1);
    }

    // mmap the input file 
    src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, in, 0);


    // mmap the output file 
    dst = mmap (0, statbuf.st_size, PROT_READ | PROT_WRITE,
        MAP_SHARED, out, 0);

    // this copies the input file to the output file 
    memcpy (dst, src, statbuf.st_size);
    return 0;
}
