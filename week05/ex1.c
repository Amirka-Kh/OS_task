#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <syscall.h>

/* in problem 1 each thread should output a message
 * I decided let each thread outputs its own 'id'
 */

struct s_threadM {
    // mutex to allow main thread to wait
    // for the new thread to set its tid
    pthread_mutex_t mtx;

    // to hold new thread's tid
    pid_t id;

    // to indicate when 'id' is valid
    int ready;
};

void *foo(void *arg)
{
    struct s_threadM *thM = arg;

    // lock mutex
    pthread_mutex_lock(&thM->mtx);

    // get and save tid and ready flag
    thM->id = syscall(SYS_gettid);
    thM->ready = 1;

    // unlock resources
    pthread_mutex_unlock(&thM->mtx);

    return NULL;
}

void CreateThreads(unsigned int n)
{
    pthread_t thread;

    // struct to pass back tid
    struct s_threadM threadM;
    pthread_mutex_init(&threadM.mtx, NULL);

    for (int i = 0; i < n; i++) {
        /* I lock mutex 'before' creating the thread, to make the new thread
           wait until we're ready */
        pthread_mutex_lock(&threadM.mtx);

        // clear ready flag before creating each thread
        threadM.ready = 0;

        // create threads and pass address of struct as argument
        if (pthread_create(&thread, NULL, foo, &threadM)) {
            printf("pthread error!\n");
        } else {
            // Now we have the tid
            printf("%d thread was created\n", i+1);
            printf("its 'id' %d\n", threadM.id);
        }

        // unlock the mutex when done
        pthread_mutex_unlock(&threadM.mtx);

        pthread_join(thread, NULL);
    }

    /* When we're completely done with the struct we need to clean up the
       mutex variable */
    pthread_mutex_destroy(&threadM.mtx);

}

int main(){
    int n;
    scanf("%d", &n);
    CreateThreads(n);
    return 0;
}