#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <queue> 
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
bool compare1(process p1, process p2) 
{ 
 return p1.arrival_time < p2.arrival_time;
27
}
bool compare2(process p1, process p2) 
{ 
 return p1.pid < p2.pid;
}
int main() 
{
 int n;
 int tq;
 struct process p[100];
 float avg_turnaround_time;
 float avg_waiting_time;
 float total_turnaround_time = 0;
 float total_waiting_time = 0;
 int burst_remaining[100];
 int idx;
 cout << setprecision(2) << fixed;
 cout<<" Enter the number of processes: ";
28
 cin>>n;
 cout<<" Enter time quantum: ";
 cin>>tq;
 for(int i = 0; i < n; i++) 
{
 cout<<" Enter arrival time of process "<<i+1<<": ";
 cin>>p[i].arrival_time;
 cout<<" Enter burst time of process "<<i+1<<": ";
 cin>>p[i].burst_time;
 burst_remaining[i] = p[i].burst_time;
 p[i].pid = i+1;
 cout<<endl;
 }
 sort(p,p+n,compare1);
 queue<int> q;
 float current_time = 0;
 q.push(0);
 int completed = 0;
 int mark[100];
 //memset(mark,0,sizeof(mark));
29
 mark[0] = 1;
 while(completed != n) 
{
 idx = q.front();
 q.pop();
 if(burst_remaining[idx] == p[idx].burst_time) 
{
 p[idx].start_time = max(current_time,p[idx].arrival_time);
 current_time = p[idx].start_time;
 }
 if(burst_remaining[idx]-tq > 0) 
{
 burst_remaining[idx] -= tq;
 current_time += tq;
 }
 else 
{
 current_time += burst_remaining[idx];
 burst_remaining[idx] = 0;
 completed++;
30
 p[idx].completion_time = current_time;
 p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
 p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
 total_turnaround_time += p[idx].turnaround_time;
 total_waiting_time += p[idx].waiting_time;
 }
 for(int i = 1; i < n; i++) 
{
 if(burst_remaining[i] > 0 && p[i].arrival_time <= current_time && 
mark[i] == 0) 
{
 q.push(i);
 mark[i] = 1;
 }
 }
 if(burst_remaining[idx] > 0) 
{
 q.push(idx);
 }
 if(q.empty()) 
31
{
 for(int i = 1; i < n; i++) 
{
 if(burst_remaining[i] > 0) 
{
 q.push(i);
 mark[i] = 1;
 break;
 }
 }
 }
 }
 avg_turnaround_time = (float) total_turnaround_time / n;
 avg_waiting_time = (float) total_waiting_time / n;
 sort(p,p+n,compare2);
 cout<<endl;
 cout<<" 
PID\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;
 for(int i = 0; i < n; i++) 
32
{
 cout<<" 
"<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_tim
e<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_
time<<"\n"<<endl;
 }
 cout<<"\n Average Turnaround Time = "<<avg_turnaround_time<<endl;
 cout<<" Average Waiting Time = "<<avg_waiting_time<<endl;
}
