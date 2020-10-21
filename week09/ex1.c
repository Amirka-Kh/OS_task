#include <stdio.h>
#include <stdlib.h>
//
// Created by amira on 14.10.2020.
//

typedef struct Page{
    int R;          // reference bit
    int No;         // page number
}Page;


int main(){

    int hit = 0, miss = 0, nframes; // nframes stands for amount of page frames in memory

    printf("Number of frames: ");
    scanf("%d", &nframes);

    FILE *file;
    file = fopen("INPUT.txt", "r");

    /* I create create an empty memory with n frames */
    Page * memory = malloc(nframes * sizeof(Page));
    for (int i = 0; i < nframes; i++){
        (memory + i)->R = 0;
        (memory + i)->No = -1;  // By that I mean that that place is free
                                // I though to assign it to zero, but then
                                // I understood new page number can be zero
    }

    int new_page;   // is a new page number that we receive
    // I save number of new_page every 'clock tick'
    while (fscanf(file, "%d", &new_page) != EOF){
        // for a new 'clock tick' we refresh reference bit for all pages
        for(int i = 0; i < nframes; i++){
            (memory + i)->R >>= 1;
        }

        int q_set = -1;    // this means: "does a new_page set"
                           // when we will find a place where to put it
                           // we will assign q-set to index of that place

        for (int i = 0; i < nframes; i++){
            if((memory + i)->No == new_page)
                q_set = i; // we have already that page in memory
        }

        if (q_set != -1)
            hit++;
        else{
            q_set = 0; // now I will a candidate to remove
                       // I look to all pages presented in the memory
                       // therefore I set 0 to q_set
            for (int i = 1; i < nframes; i++){
                if ((memory+i)->R < (memory+q_set))
                    q_set = i;
                if ((memory+i)->R == (memory+q_set)->R &&
                        (memory+i)->No < (memory+q_set)->No)
                    q_set = i;
            }
            (memory+q_set)->No = new_page;
            miss++;
        }
        (memory+q_set)->R |= (1<<7);
    }
    float ratio = hit/miss;
    printf("Number of hits: %d\nNumber of misses: %d\nRatio: %lf\n", hit, miss, ratio);


}