//Non preemptive
//assumed that higher the priority number, higher is the priority
#include <iostream>
#include <iomanip>
#include <string.h> 
using namespace std;
struct process 
{
 int pid; //process id/process number
 int priority;
 float arrival_time;
 float burst_time;
 float start_time;
 float completion_time;
 float turnaround_time;
 float waiting_time;
};
int main() 
40
{
 int n;
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
 cout<<" Enter priority of the process "<<i+1<<": ";
 cin>>p[i].priority;
 p[i].pid = i+1;
 cout<<endl;
 }
41
 float current_time = 0;
 int completed = 0; 
 while(completed != n) 
{
//finding process with maximum priority
 int idx = -1;
 int maxp = 0; //variable taken to find the maximum 
priority
 for(int i = 0; i < n; i++) 
{
 if(p[i].arrival_time <= current_time && is_completed[i] == 0) 
//checking all the processes in the ready queue
{
 if(p[i].priority > maxp) 
{
 maxp = p[i].priority;
 idx = i;
 }
 else
 {
 if(p[i].priority == maxp) 
{
42
 if(p[i].arrival_time < p[idx].arrival_time) 
{
 maxp = p[i].priority;
 idx = i;
 }
 }
}
 }
 }
 
 if(idx != -1) 
{ //that if it is true that means some process is found in 
ready queue and then we find the different values of that process
 p[idx].start_time = current_time;
 p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
 p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
 p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
 
 total_turnaround_time += p[idx].turnaround_time;
 total_waiting_time += p[idx].waiting_time;
 is_completed[idx] = 1; //marks that the process is 
completed
43
 completed++; //icrements the no. of completed 
processes
 current_time = p[idx].completion_time;
 }
 else 
{
 current_time++;
 }
 
 }
 
 avg_turnaround_time = (float) total_turnaround_time / n;
 avg_waiting_time = (float) total_waiting_time / n;
 cout<<endl<<endl;
 cout<<" 
PID\t"<<"AT\t"<<"BT\t"<<"PRI\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"
<<endl;
 for(int i = 0; i < n; i++) 
{
 cout<<" 
"<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].priority<
44
<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<
<"\t"<<p[i].waiting_time<<"\t"<<"\n"<<endl;
 }
 cout<<"\n Average Turnaround Time = "<<avg_turnaround_time<<endl;
 cout<<" Average Waiting Time = "<<avg_waiting_time<<endl;
}

