#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
int id;
int at;
int bt1;
int bt2;
int total_bt;
int ct;
int tat;
int wt;
} Process;
int main() {
int n, i, j;
srand(time(NULL));
printf("Enter number of processes: ");
if(scanf("%d", &n) != 1) return 0;
Process p[20];
for(i = 0; i < n; i++) {
p[i].id = i + 1;
printf("Process P%d - Arrival Time: ", i + 1);
scanf("%d", &p[i].at);
printf("Process P%d - First CPU Burst: ", i + 1);
scanf("%d", &p[i].bt1);
p[i].bt2 = (rand() % 10) + 1;
p[i].total_bt = p[i].bt1 + p[i].bt2;
printf("Process P%d - Next CPU Burst (random): %d (Total Burst: %d)\n", i + 1, p[i].bt2, p[i].total_bt);
}
for(i = 0; i < n - 1; i++) {
for(j = 0; j < n - i - 1; j++) {
if(p[j].at > p[j + 1].at) {
Process t = p[j];
p[j] = p[j + 1];
p[j + 1] = t;
}
}
}
int current_time = 0;
int gantt_p[100], gantt_t[100], g_cnt = 0;
gantt_t[0] = 0;
for(i = 0; i < n; i++) {
if(current_time < p[i].at) current_time = p[i].at;
current_time += p[i].total_bt;
p[i].ct = current_time;
p[i].tat = p[i].ct - p[i].at;
p[i].wt = p[i].tat - p[i].total_bt;
gantt_p[g_cnt] = p[i].id;
gantt_t[g_cnt + 1] = current_time;
g_cnt++;
}
printf("\nGantt Chart:\n|");
for(i = 0; i < g_cnt; i++) printf(" P%d |", gantt_p[i]);
printf("\n%d", gantt_t[0]);
for(i = 0; i < g_cnt; i++) printf("    %d", gantt_t[i + 1]);
printf("\n\nProcess\tAT\tBT1\tBT2\tTotal BT\tCT\tTAT\tWT\n");
float total_tat = 0, total_wt = 0;
for(i = 0; i < n; i++) {
total_tat += p[i].tat;
total_wt += p[i].wt;
printf("P%d\t%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt1, p[i].bt2, p[i].total_bt, p[i].ct, p[i].tat, p[i].wt);
}
printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
printf("Average Waiting Time = %.2f\n", total_wt / n);
return 0;
}
