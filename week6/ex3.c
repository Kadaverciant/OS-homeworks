#include <stdio.h>

int existUnfinished(int n, int pr[][6]) {
    int exist=0;
    for (int i=0; i<n; i++) {
        if (pr[i][5]!=0) {
            exist=1;
            break;
        }
    }
    return exist;
}

int skipTime(int n, int pr[][6], int curTime) {
    int needSkip=1;
    for (int i=0; i<n; i++) {
        if (pr[i][5] > 0 && pr[i][0] < curTime) {
            needSkip = 0;
            break;
        }
    }
    return needSkip;
}

void swap(int p[][2], int first, int second) {
    int temp1=p[first][0];
    int temp2=p[first][1];
    p[first][0]=p[second][0];
    p[first][1]=p[second][1];
    p[second][0]=temp1;
    p[second][1]=temp2;
}

int main() {
    int n;
    printf("Enter number of precesses: ");
    scanf("%d",&n);

    int quantum;
    printf("Enter quantum length: ");
    scanf("%d",&quantum);

    int p[n][2];
    for (int i=0; i<n; i++) {
        printf("Enter arrival time of precess[%d]: ",i+1);
        scanf("%d",&p[i][0]);
        printf("Enter burst time of precess[%d]: ",i+1);
        scanf("%d",&p[i][1]);
    }

    /*
     * You may comment sorting part depending on what you want, since order influence on CT, WT, and TAT =>
     * on average TAT and average WT.
     * However, this part doesn't influence on the calculations methods.
     */
//-----------------------Sorting part begin-----------------------------------------------------------------------------
    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<n; j++) {
            if (p[i][1]>p[j][1]) {
                swap(p,i,j);
            }
        }
    }

    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<n; j++) {
            if (p[i][0]>p[j][0]) {
                for (int k=j; k>i; k--) {
                    swap(p,k,k-1);
                }
            }
        }
    }
//-----------------------Sorting part end-------------------------------------------------------------------------------


    int curTime=0;
    int pr[n][6];
    for (int i=0; i<n; i++) {
        pr[i][0]=p[i][0];//at
        pr[i][1]=p[i][1];//bt
        pr[i][2]=0;//ct
        pr[i][3]=0;//tat
        pr[i][4]=0;//wt
        pr[i][5]=p[i][1];//remaining boost
    }

    while (existUnfinished(n,pr)) {
        for (int i=0; i<n; i++) {
            if (pr[i][5]!=0) {
                if (pr[i][0]<=curTime) {
                    if (pr[i][5]<=quantum) {
                        pr[i][2]=curTime+pr[i][5];//ct
                        curTime+=pr[i][5];
                        pr[i][5]=0;
                        pr[i][3]= pr[i][2]-pr[i][0];//tat=ct-at
                        pr[i][4]= pr[i][3]-pr[i][1];//wt=tat-bt
                    } else {
                        pr[i][5]-=quantum;
                        curTime+=quantum;
                    }
                }
            }
        }
        curTime+= skipTime(n,pr,curTime);//if at the current time there is no processes that are ready to run,
                                         //we add 1 sec, 0 otherwise.
    }

    printf("P#\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i=0; i<n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,pr[i][0],pr[i][1],
               pr[i][2],pr[i][3],pr[i][4]);
    }

    float aTAT=0;
    float aWT=0;
    for (int i=0; i<n; i++) {
        aTAT+=pr[i][3];
        aWT+=pr[i][4];
    }
    aTAT/=n;
    aWT/=n;
    printf("Average Turnaround time = %f\n",aTAT);
    printf("Average Waiting time = %f\n",aWT);
}

/*
 * For test
    P#	AT	BT
    P1	0	1
    P2	0	2
    P3	0	4
    P4	0	6
    P5	0	8
    P6	11	1
    P7	11	2
    P8	11	4
    P9	11	6
    P10	11	8

    For the round-robin algorithm for quantum=3:
    Average Turnaround time = 17.900000
    Average Waiting time = 13.700000

    For the round-robin algorithm for quantum=4:
    Average Turnaround time = 16.000000
    Average Waiting time = 11.800000

    For the round-robin algorithm for quantum=8:
    Average Turnaround time = 14.000000
    Average Waiting time = 9.800000

    For the shortest job first algorithm:
    Average Turnaround time = 12.100000
    Average Waiting time = 7.900000

    For the first come, first served (FCFS) algorithm:
    Average Turnaround time = 17.600000
    Average Waiting time = 13.400000

 * For test
    P#	AT	BT
    P1	0	2
    P2	0	3
    P3	1	4

    For the round-robin algorithm for quantum=3:
    Average Turnaround time = 5.000000
    Average Waiting time = 2.000000

    For the shortest job first algorithm:
    Average Turnaround time = 5.000000
    Average Waiting time = 2.000000

    For the first come, first served (FCFS) algorithm:
    Average Turnaround time = 5.333333
    Average Waiting time = 2.333333

    So, for the shortest job algorithm Average Turnaround time and Average Waiting time are lower or equal
    compared to other algorithms. But, some long processes may never be processed by 
    the system and may remain in the queue for very long time.
    
    The round-robin algorithm depends on the quantum. Very large quantum makes it same to the FCFS.
 */

