#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void memory_fill(){

    // memory size allocated for 1 second (10 MB)
    size_t mem_size = 10*1024*1024;

    // allocate memory
    void *based = malloc(mem_size);

    // I am gonna fill this chunks of memory with 0
    int stage = sizeof(int);
    int initialized = 0;

    while (initialized < mem_size) {
        memset((char *)based + initialized, 0, stage);
        initialized += stage;
    }
}

int main(void)
{
    for (int second = 0; second < 10; second++){
        memory_fill();
        sleep(1);
    }
    return 0;
}
