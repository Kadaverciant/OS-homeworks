#include <stdio.h>

int main() {
    int n;
    printf("Enter number of precesses: ");
    scanf("%d",&n);

    int p[n][2];//2d array to store arrival and burst time
    for (int i=0; i<n; i++) {
        printf("Enter arrival time of precess[%d]: ",i+1);
        scanf("%d",&p[i][0]);
        printf("Enter burst time of precess[%d]: ",i+1);
        scanf("%d",&p[i][1]);
    }

    for (int i=0; i<n-1; i++) {//sort by arrival time
        for (int j=i+1; j<n; j++) {
            if (p[i][0]>p[j][0]) {
                int t1=p[i][0];
                int t2=p[i][1];
                p[i][0]=p[j][0];
                p[i][1]=p[j][1];
                p[j][0]=t1;
                p[j][1]=t2;
            }
        }
    }

    int pr[n][5];
    //work with first process with the earliest arrival time
    pr[0][0]=p[0][0];//at
    pr[0][1]=p[0][1];//bt
    pr[0][2]=p[0][0]+p[0][1];//ct
    pr[0][3]=p[0][1];//tat
    pr[0][4]=0;//wt

    for (int i=1; i<n; i++) {
        pr[i][0]=p[i][0];//at
        pr[i][1]=p[i][1];//bt
        if (pr[i][0]>pr[i-1][2]) {//at>ct(prev)
            pr[i][2]= pr[i][0]+pr[i][1];//ct
            pr[i][3]= pr[i][2]-pr[i][0];//tat=ct-at
            pr[i][4]=0;//wt
        } else {
            pr[i][2]= pr[i-1][2]+pr[i][1];//ct
            pr[i][3]= pr[i][2]-pr[i][0];//tat=ct-at
            pr[i][4]= pr[i][3]-pr[i][1];//wt=tat-bt
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
