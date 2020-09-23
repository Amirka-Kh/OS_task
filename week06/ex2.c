#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct process {
    int arrival;    // arrival time
    int burst;      // burst time
    int id;         // process id
} process;


/* This function computes waiting time
 * We create set of remaining times
 * That will help us to compute time
 * Which process need to execute
 */
void compute_wait_time(process list[], int size, int wt[]){

    int rt[size];            // list of remaining times

    /* Copy the burst time into rt */
    for (int i = 0; i < size; i++){
        rt[i] = list[i].burst;
    }

    /* Here I denote time, we will increment it to find
     * Which process at this time can be executed*/
    int finish = 0, time = 0;

    /* I initialised min with INT_MAX in order to
     * Compare process burst time, otherwise we can get
     * Wrong result, because time can be equal to INT_MAX - 1
     */
    int min = INT_MAX;
    int shortest = 0;
    int finish_time = 0;
    int complete = 0;

    /* We will use check to determine
     * Whatever do we have for the current time
     * the process to execute
     */
    int check = 0;           // 0 stands for false

    while(complete != size){

        /* We find a process with minimum
         * Remaining time among the processes
         * That arrives till the current time
         */
        for (int j = 0; j < size; j++){
            if ((list[j].arrival <= time) && (rt[j] < min) && (rt[j]>0)){
                min = rt[j];
                shortest = j;
                check = 1;   // 1 stands for true
            }
        }

        /* No process arrive or all processes executed for current time
         * Therefore, we increment time */
        if (check == 0){
            time++;
            continue;
        }


        rt[shortest]--;

        /* We check have the process executed */
        min = rt[shortest];
        if (min == 0)
            min = INT_MAX;

        if (rt[shortest] == 0){
            complete++;         // increment the number of completed processes
            check = 0;

            finish_time = time + 1;

            wt[shortest] = finish_time - list[shortest].burst -
                    list[shortest].arrival;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        time++;
    }
}

void compute_turn_time(process list[], int size, int wt[], int tat[]){
    for (int i = 0; i < size; i++){
        tat[i] = wt[i] + list[i].burst;
    }
}

void compute_completion_time(process list[], int size, int ct[], int tat[]){
    for (int i = 0; i < size; i++){
        ct[i] = tat[i] + list[i].arrival;
    }
}

void compute_time(process list[], int n){

    int a_Tt = 0;           // average turnaround time
    int a_Wt = 0;           // average waiting time

    int wt[n], tat[n], ct[n];

    compute_wait_time(list, n, wt);

    compute_turn_time(list, n, wt, tat);

    compute_completion_time(list, n, ct, tat);

    printf("#P  AT  BT  WT  TAT CT\n");

    for (int i = 0; i < n; i++){
        printf("P%d  %d   %d   %d   %d   %d\n", i, list[i].arrival, list[i].burst, wt[i], tat[i], ct[i]);
        a_Tt += tat[i];
        a_Wt += wt[i];
    }
    a_Tt = a_Tt/n;
    a_Wt = a_Wt/n;

    printf("Average Turnaround time %d\n", a_Tt);
    printf("Average waiting time %d\n", a_Wt);

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
        p.id = i;
        list[i] = p;
    }

    compute_time(list, Number);

    return 0;
}