#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <memory.h>

int main() {
    for (int i=0; i<10; i++) {//i allocate 10 times 10MB
        memset(calloc(10 * 1024*1024, 1), 0, 10 * 1024*1024);
        sleep(1);
    }
    return 0;
}

/*
 For ex2:
 procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 1  0 1329948 5205124  21916 611700  112  153   270   185  276  488  5  1 93  1  0
 1  0 1329944 5197060  21916 611700    4    0     4     0  566 1147  0  1 99  0  0
 0  0 1329940 5186980  21916 611704    0    0     0     0  509 1082  1  0 99  0  0
 1  0 1329940 5176648  21916 611700    0    0     0     0 1108 2032  1  1 98  0  0
 0  0 1329940 5167072  21916 611700    0    0     0     0  533 1158  1  0 99  0  0
 0  0 1329940 5157244  21916 611700    0    0     0     0 1085 2220  1  1 98  0  0
 1  0 1329940 5146912  21924 611692    0    0     0    48 1544 2825  3  2 96  0  0
 0  0 1329928 5136328  21924 611708   28    0    28     8 1891 3446  6  2 92  0  0
 0  0 1329928 5126248  21924 611708    0    0     0     0 1279 2355  3  1 96  0  0
 1  0 1329928 5115916  21924 611708    0    0     0     0  904 1692  1  1 98  0  0
 2  0 1329928 5102156  21924 611708    0    0     0     0  997 1700  2  1 97  0  0
 0  0 1329928 5207148  21924 611708    0    0     0     0 1058 1906  2  1 97  0  0
 0  0 1329928 5207148  21932 611700    0    0     0   128 1203 2136  2  1 97  0  0
 0  0 1329928 5207148  21932 611708    0    0     0     0  544 1151  1  0 99  0  0
 0  0 1329924 5207148  21932 611708    0    0     0     0  453 1057  0  0 99  0  0
 0  0 1329924 5207148  21932 611708    0    0     0     0  682 1438  1  0 98  0  0
 0  0 1329924 5207148  21932 611708    0    0     0     0  552 1178  1  0 99  0  0
 0  0 1329788 5204644  21932 612032  164    0   164   192 1817 3374  3  2 94  1  0
 0  0 1329788 5204628  21932 612040    0    0     0     0  795 1579  1  0 99  0  0
 0  0 1329788 5204628  21932 611724    0    0     0     0  591 1092  1  0 99  0  0
 0  0 1329784 5204628  21932 611824   16    0    16     0 1104 2034  2  1 97  0  0

 As we can see we are swap in and swap out some memory from time to time.

 For ex3:
top - 16:14:19 up  1:30,  1 user,  load average: 0,44, 0,35, 0,39
Tasks: 260 total,   1 running, 256 sleeping,   3 stopped,   0 zombie
%Cpu(s):  0,7 us,  0,5 sy,  0,0 ni, 98,2 id,  0,5 wa,  0,0 hi,  0,2 si,  0,0 st
МиБ Mem :   7958,8 total,   4994,5 free,   2338,1 used,    626,2 buff/cache
МиБ Swap:   2048,0 total,    756,1 free,   1291,9 used.   5349,8 avail Mem

    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
   2250 vsevolod  20   0 3673416 273064  75600 S   2,0   3,4   5:19.97 firefox
   3298 vsevolod  20   0 2496248  96864  69632 S   2,0   1,2   1:36.93 file:// Content
   6732 vsevolod  20   0   20684   4060   3296 R   2,0   0,0   0:00.10 top
   1032 vsevolod   9 -11 2728660   4836   3368 S   1,0   0,1   0:33.85 pulseaudio
   1115 root      20   0  261132    792    212 S   1,0   0,0   0:00.20 upowerd
   1234 vsevolod  20   0  229532      0      0 S   1,0   0,0   0:15.30 VBoxClient
   1298 vsevolod  20   0 4301376 116744  47468 S   1,0   1,4   2:52.23 gnome-shell
   4040 vsevolod  20   0 8622020   1,1g  18540 S   1,0  13,9  16:33.21 java
   6731 vsevolod  20   0   94692  93256   1104 S   1,0   1,1   0:00.08 ex2
      1 root      20   0  168952   6520   3640 S   0,0   0,1   0:01.69 systemd
      2 root      20   0       0      0      0 S   0,0   0,0   0:00.00 kthreadd
      3 root       0 -20       0      0      0 I   0,0   0,0   0:00.00 rcu_gp
      4 root       0 -20       0      0      0 I   0,0   0,0   0:00.00 rcu_par_gp
      6 root       0 -20       0      0      0 I   0,0   0,0   0:00.00 kworker/0:0H-eve+
      9 root       0 -20       0      0      0 I   0,0   0,0   0:00.00 mm_percpu_wq
     10 root      20   0       0      0      0 S   0,0   0,0   0:00.00 rcu_tasks_rude_
[5]   Завершён        ./ex2    0      0      0 S   0,0   0,0   0:00.00 rcu_tasks_trace

 There we can see how many resources of a machine all processes are using & the amount of swapped memory.
 */
