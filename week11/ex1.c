#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>

int main (int argc, char *argv[]) {

    int fdin, fdout;
    char *src, *dst;
    struct stat statbuf;
    int mode = 0x0777;

    if (argc != 3)
        err_quit ("usage: a.out <fromfile> <tofile>");

    /* open the input file */
    if ((fdin = open (argv[1], O_RDONLY)) < 0)
    {printf("%s does not open", argv[1]);
        return 0;
    }

    /* open/create the output file */
    if ((fdout = open (argv[2], O_RDWR | O_CREAT | O_TRUNC, mode )) < 0) //edited here
    {printf ("can't create %s for writing", argv[2]);
        return 0;
    }

    /* find size of input file */
    fstat(fdin,&statbuf);

    /* go to the location corresponding to the last byte */
    lseek(fdout, statbuf.st_size - 1, SEEK_SET);

    /* write a dummy byte at the last location */
    write(fdout, "", 1);

    /* mmap the input file */
    src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0);


    /* mmap the output file */
    dst = mmap (0, statbuf.st_size, PROT_READ | PROT_WRITE,
        MAP_SHARED, fdout, 0));

    /* this copies the input file to the output file */
    memcpy (dst, src, statbuf.st_size);
    return 0;
}