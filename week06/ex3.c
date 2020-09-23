#include <stdio.h>
#include <stdlib.h>

void compute_wait_time(int n, int wt[], int burst_times[], int quantum, int ct[], int arrival_times[]){

    int rt[n];            // list of remaining times

    /* Copy the burst time into rt */
    for (int i = 0; i < n; i++){
        rt[i] = burst_times[i];
    }

    int time = 0;
    int arrival = 0;

    int done = 0;         // works instead of boolean

    while(done == 0){
        int finish = 0;   // works instead of boolean

        for (int i = 0; i < n; i++){
            if (rt[i] > 0){
                finish = 1;
                if (rt[i] > quantum && arrival_times[i] <= arrival){
                    time += quantum;
                    rt[i] -= quantum;
                    arrival++;
                }
                else {
                    if (arrival_times[i] <= arrival){
                        arrival++;
                        time += rt[i];
                        rt[i] = 0;
                        ct[i] = time;
                    }
                }
            }
        }

        if (finish == 0){
            done = 1;
        }
    }
}

void compute_turn_time(int n, int wt[], int burst_times[], int tat[], int ct[], int arrival_times[]){
    for (int i = 0; i < n; i++){
        tat[i] = ct[i] - arrival_times[i];
        wt[i] = tat[i] - burst_times[i];
    }
}

void compute_times(int n, int burst_times[], int arrival_times[]){

    int quantum = 2;
    float a_Tt = 0;                   // average turnaround time
    float a_Wt = 0;                   // average waiting time
    int wt[n], tat[n], ct[n];       // ct - completion, tat - turnaround, wt - wait time

    compute_wait_time(n, wt, burst_times, quantum, ct, arrival_times);

    compute_turn_time(n, wt, burst_times, tat, ct, arrival_times);


    printf("#P  AT  BT  WT  TAT CT\n");

    for (int i = 0; i < n; i++){
        printf("P%d  %d   %d   %d   %d   %d\n", i, arrival_times[i], burst_times[i], wt[i], tat[i], ct[i]);
        a_Tt += tat[i];
        a_Wt += wt[i];
    }
    a_Tt = a_Tt/n;
    a_Wt = a_Wt/n;

    printf("Average Turnaround time %f\n", a_Tt);
    printf("Average waiting time %f\n", a_Wt);
}

int main(){

    int Number;
    printf("Enter the number of processes: \n");
    scanf("%d", &Number);
    printf("Enter burst time and arrival time for each process\n");

    int arrival_times[Number];
    int burst_times[Number];

    for (int i = 0; i < Number; i++){
        printf("Arrival time of process %d: ",i+1);
        scanf("%d",&arrival_times[i]);
        printf("Burst time of process %d: ",i+1);
        scanf("%d",&burst_times[i]);
    }

    compute_times(Number, burst_times, arrival_times);

    return 0;
}
