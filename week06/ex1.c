#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int arrival;    // arrival time
    int burst;      // burst time
    int wait;       // waiting time
    int turn;       // turn around time
    int comp;       // completion time
} process;

/* This function searches for the smallest arrival time
 * If there 2 or more similar arrival times
 * It sends the index of first entry
 */
int find_min(process list[], int size){

    int min = list[0].arrival;
    int min_index = 0;

    for (int i = 0; i < size; i++){
        if (min > list[i].arrival){
            min = list[i].arrival;
            min_index = i;
        }
    }
    return min_index;
}

/* This function computes different times
 * If we found a completion time of first process
 * The waiting time for the second process will be
 * Completion time for first minus arrival time for the second one
 */
void compute_things(process list[], int size, int min_index){

    int exe_time;   // shows the time when the process starts executing
    process p = list[min_index];

    if (p.wait == 0)
        exe_time = p.arrival + p.burst;
    else
        exe_time = p.burst + p.wait;

    p.turn = p.wait + p.burst;      // as I wrote in description of the function
    p.comp = p.arrival + p.turn;    // we will need these variables to compute times

    for (int i = 0; i < size; i++){

        if (i != min_index){        // overwriting will bring wrong answers

            if (list[i].arrival < exe_time)
                list[i].wait = p.comp - list[i].arrival;
        }
    }

    list[min_index] = p;
}

/* This function helps me to remove
 * An element from the array (add it to the end)
 * In 'main' FCFS loop we do not consider the last element (deleted element)
 */
void delete(process list[], int size, int index){
    process p;
    for (int i = index; i < size-1; i++){
        p = list[i+1];
        list[i+1] = list[i];
        list[i] = p;
    }
}

int main(){

    int Number;
    printf("Enter the number of processes: \n");
    scanf("%d", &Number);
    printf("Enter burst time and arrival time for each process\n");

    process list[Number];

    for (int i = 0; i < Number; i++){
        process p;
        printf("Arrival time of process %d: ",i+1);
        scanf("%d",&p.arrival);
        printf("Burst time of process %d: ",i+1);
        scanf("%d",&p.burst);
        p.comp = 0;
        p.turn = 0;
        p.wait = 0;
        list[i] = p;
    }

    /* ----------------------FCFS--------------------------*/
    int a_Tt = 0;           // average turnaround time
    int a_Wt = 0;           // average waiting time

    /* I had made a function of FCFS scheduling, but then
     * I thought that it can be done in 'main'
     * I used n as Number, therefore:
     */
    int n = Number;

    int list_size = n;
    for (int i = 0; i < n; i++){

        int min_index = find_min(list, list_size);

        compute_things(list, list_size, min_index);

        delete(list, list_size, min_index);

        list_size -= 1;
    }

    printf("#P  AT  BT  WT  TAT CT\n");

    int i;
    for (int j = 1; j <= n; j++){
        i = n - j;
        printf("P%d  %d   %d   %d   %d   %d\n", i, list[i].arrival, list[i].burst, list[i].wait, list[i].turn, list[i].comp);
        a_Tt += list[i].turn;
        a_Wt += list[i].wait;
    }
    a_Tt = a_Tt/n;
    a_Wt = a_Wt/n;

    printf("Average Turnaround time %d\n", a_Tt);
    printf("Average waiting time %d\n", a_Wt);

    return 0;
}