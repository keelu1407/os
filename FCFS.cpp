#include <iostream>
#include <algorithm> 
#include <iomanip> 
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
bool compareArrival(process p1, process p2) 
{ 
 return p1.arrival_time < p2.arrival_time;
}
22
bool compareID(process p1, process p2) 
{ 
 return p1.pid < p2.pid;
}
int main() 
{
 int n;
 struct process p[100];
 float avg_turnaround_time;
 float avg_waiting_time;
 float total_turnaround_time = 0;
 float total_waiting_time = 0;
 cout << setprecision(2) << fixed;
 cout<<" Enter the number of processes: ";
 cin>>n;
 for(int i = 0; i < n; i++) 
{
 cout<<" Enter arrival time of process "<<i+1<<": ";
23
 cin>>p[i].arrival_time;
 cout<<" Enter burst time of process "<<i+1<<": ";
 cin>>p[i].burst_time;
 p[i].pid = i+1;
 cout<<endl;
 }
 sort(p,p+n,compareArrival);
 for(int i = 0; i < n; i++) {
 p[i].start_time = (i == 0)?p[i].arrival_time:max(p[i1].completion_time,p[i].arrival_time);
 p[i].completion_time = p[i].start_time + p[i].burst_time;
 p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
 p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
 total_turnaround_time += p[i].turnaround_time;
 total_waiting_time += p[i].waiting_time;
 }
 avg_turnaround_time = (float) total_turnaround_time / n;
 avg_waiting_time = (float) total_waiting_time / n;
24
 sort(p,p+n,compareID);
 cout<<endl;
 cout<<" 
PID\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;
 for(int i = 0; i < n; i++) 
{
 cout<<" 
"<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_tim
e<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_
time<<"\t"<<"\n"<<endl;
 }
 cout<<"\n Average Turnaround Time = "<<avg_turnaround_time<<endl;
 cout<<" Average Waiting Time = "<<avg_waiting_time<<endl;;
}

