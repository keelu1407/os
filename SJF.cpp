#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <string.h> 
using namespace std;
struct process 
{
 int pid;
 float arrival_time;
 float burst_time;
 float start_time;
 float completion_time;
 float turnaround_time;
 float waiting_time;
};
int main() 
{
 int n;
34
 struct process p[100];
 float avg_turnaround_time;
 float avg_waiting_time;
 float total_turnaround_time = 0;
 float total_waiting_time = 0;
 float total_idle_time = 0;
 
 cout<<" Enter the number of processes: ";
 cin>>n;
 int is_completed[n]={0};
 for(int i = 0; i < n; i++) 
{
 cout<<"\n Enter arrival time of process "<<i+1<<": ";
 cin>>p[i].arrival_time;
 cout<<" Enter burst time of process "<<i+1<<": ";
 cin>>p[i].burst_time;
 p[i].pid = i+1;
 cout<<endl;
 }
 float current_time = 0;
 int completed = 0;
35
 while(completed != n) 
{
 int idx = -1; //variable storing the process with least burst
 int minb = 10000000; //varibale storing the least burst
 for(int i = 0; i < n; i++) 
{
 if(p[i].arrival_time <= current_time && is_completed[i] == 0) 
{
 if(p[i].burst_time < minb) 
{
 minb = p[i].burst_time;
 idx = i;
 }
 else
 {
 if(p[i].burst_time == minb) 
{
 if(p[i].arrival_time < p[idx].arrival_time) 
{
 minb = p[i].burst_time;
 idx = i;
 }
 }
36
}
 }
 }
 if(idx != -1) 
{
 p[idx].start_time = current_time;
 p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
 p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
 p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
 
 total_turnaround_time += p[idx].turnaround_time;
 total_waiting_time += p[idx].waiting_time;
 is_completed[idx] = 1;
 completed++;
 current_time = p[idx].completion_time;
 }
 else 
{
 current_time++;
 }
 
 }
37
 avg_turnaround_time = (float) total_turnaround_time / n;
 avg_waiting_time = (float) total_waiting_time / n;
 cout<<endl<<endl;
 cout<<" 
PID\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;
 for(int i = 0; i < n; i++) 
{
 cout<<" 
"<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_tim
e<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_
time<<"\t"<<"\t"<<"\n"<<endl;
 }
 cout<<"\n Average Turnaround Time = "<<avg_turnaround_time<<endl;
 cout<<" Average Waiting Time = "<<avg_waiting_time<<endl;
}

