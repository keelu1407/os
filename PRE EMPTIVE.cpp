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
 int priority;
 float start_time;
 float completion_time;
 float turnaround_time;
 float waiting_time;
};
int main() 
46
{
 int n;
 struct process p[100];
 float avg_turnaround_time;
 float avg_waiting_time;
 float total_turnaround_time = 0;
 float total_waiting_time = 0;
 int burst_remaining[100];
 int is_completed[100];
 memset(is_completed,0,sizeof(is_completed));
 cout << setprecision(2) << fixed;
 cout<<" Enter the number of processes: ";
 cin>>n;
 for(int i = 0; i < n; i++) 
{
 cout<<" Enter arrival time of process "<<i+1<<": ";
 cin>>p[i].arrival_time;
 cout<<"Enter burst time of process "<<i+1<<": ";
47
 cin>>p[i].burst_time;
 cout<<" Enter priority of the process "<<i+1<<": ";
 cin>>p[i].priority;
 p[i].pid = i+1;
 burst_remaining[i] = p[i].burst_time;
 cout<<endl;
 }
 float current_time = 0;
 int completed = 0;
 int prev = 0;
 while(completed != n) 
{
 int idx = -1;
 int mx = -1;
 for(int i = 0; i < n; i++) 
{
 if(p[i].arrival_time <= current_time && is_completed[i] == 0) 
{
 if(p[i].priority > mx) 
{
48
 mx = p[i].priority;
 idx = i;
 }
 if(p[i].priority == mx) 
{
 if(p[i].arrival_time < p[idx].arrival_time) 
{
 mx = p[i].priority;
 idx = i;
 }
 }
 }
 }
 if(idx != -1) 
{
 if(burst_remaining[idx] == p[idx].burst_time) 
{
 p[idx].start_time = current_time;
 }
 burst_remaining[idx] -= 1;
 current_time++;
49
 prev = current_time;
 if(burst_remaining[idx] == 0) 
{
 p[idx].completion_time = current_time;
 p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
 p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
 total_turnaround_time += p[idx].turnaround_time;
 total_waiting_time += p[idx].waiting_time;
 is_completed[idx] = 1;
 completed++;
 }
 }
 else 
 {
 current_time++;
 } 
 }
 float min_arrival_time = 10000000;
 float max_completion_time = -1;
50
 for(int i = 0; i < n; i++) 
 {
 min_arrival_time = min(min_arrival_time,p[i].arrival_time);
 max_completion_time = max(max_completion_time,p[i].completion_time);
 }
 avg_turnaround_time = (float) total_turnaround_time / n;
 avg_waiting_time = (float) total_waiting_time / n;
 cout<<endl<<endl;
 cout<<" 
PID\t"<<"AT\t"<<"BT\t"<<"PRI\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<en
dl;
 for(int i = 0; i < n; i++) 
{
 cout<<" 
"<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].priority<<
"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<
<"\t"<<p[i].waiting_time<<"\t"<<"\n"<<endl;
 }
 cout<<"\n Average Turnaround Time = "<<avg_turnaround_time<<endl;
51
 cout<<" Average Waiting Time = "<<avg_waiting_time<<endl;
}
