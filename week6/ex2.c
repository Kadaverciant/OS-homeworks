#include <stdio.h>

int existUnvisited(int n, int pr[][6]) {
    int exist=0;
    for (int i=0; i<n; i++) {
        if (pr[i][5]==0) {
            exist=1;
            break;
        }
    }
    return exist;
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

    int p[n][2];
    for (int i=0; i<n; i++) {
        printf("Enter arrival time of precess[%d]: ",i+1);
        scanf("%d",&p[i][0]);
        printf("Enter burst time of precess[%d]: ",i+1);
        scanf("%d",&p[i][1]);
    }

    //sort firstly by burst time
    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<n; j++) {
            if (p[i][1]>p[j][1]) {
                swap(p,i,j);
            }
        }
    }

    //secondly sort by arrival time with respect to burst time
    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<n; j++) {
            if (p[i][0]>p[j][0]) {
                for (int k=j; k>i; k--) {
                    swap(p,k,k-1);
                }
            }
        }
    }
    /*
     * After that we will receive that on first position there would be process with
     * the earliest arrival time and the lowest burst.
     * Also in output it would be more convenient to see and check processes.
     * However, it won't influence on results of the program.
     */

    int pr[n][6];
    pr[0][0]=p[0][0];//at
    pr[0][1]=p[0][1];//bt
    pr[0][2]=p[0][0]+p[0][1];//ct
    pr[0][3]=p[0][1];//tat
    pr[0][4]=0;//wt
    pr[0][5]=1;//flag-visited or not

    int lastCT=pr[0][2];
    for (int i=1; i<n; i++) {
        pr[i][0]=p[i][0];//at
        pr[i][1]=p[i][1];//bt
        pr[i][5]=0;
    }

    while (existUnvisited(n,pr)) {
        int nextId=-1;
        int nextBT=9999;
        for (int i=0; i<n; i++) {//looking for the unvisited process which arrival time is less or
                                 // equal to end time of last executed process and has the lowest burst time.
            if (pr[i][5]==0 && pr[i][0]<=lastCT &&  pr[i][1]<nextBT) {
                nextBT=pr[i][1];
                nextId=i;
            }
        }
        if (nextId!=-1) {
            pr[nextId][2]= lastCT+pr[nextId][1];//ct
            pr[nextId][3]= pr[nextId][2]-pr[nextId][0];//tat=ct-at
            pr[nextId][4]= pr[nextId][3]-pr[nextId][1];//wt=tat-bt
            pr[nextId][5]=1;
            lastCT=pr[nextId][2];
        } else {//if there is no such process, we are looking for the  unvisited process which arrival time
                //is minimum among the unvisited processes and has the lowest burst time.
            int nextAT=9999;
            for (int i = 0; i < n; i++) {
                if (pr[i][5]==0 && pr[i][0]<nextAT && pr[i][1]<nextBT) {
                    nextAT=pr[i][0];
                    nextBT=pr[i][1];
                    nextId=i;
                }
            }
            pr[nextId][2]= pr[nextId][0]+pr[nextId][1];//ct
            pr[nextId][3]= pr[nextId][2]-pr[nextId][0];//tat=ct-at
            pr[nextId][4]=0;//wt
            pr[nextId][5]=1;
            lastCT=pr[nextId][2];
        }
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


