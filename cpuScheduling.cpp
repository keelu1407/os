#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int priority;
};

class SJF
{
    int n;
    struct process p[100];

    float avg_turnaround_time;
    float avg_waiting_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int is_completed[100];
    

    public:
        SJF()
        {
            memset(is_completed,0,sizeof(is_completed));

            cout << setprecision(2) << fixed;
            cout<<"Enter the number of processes: ";
            cin>>n;

            for(int i = 0; i < n; i++) {
                cout<<"Enter arrival time of process "<<i+1<<": ";
                cin>>p[i].arrival_time;
                cout<<"Enter burst time of process "<<i+1<<": ";
                cin>>p[i].burst_time;
                p[i].pid = i+1;
                cout<<endl;
            }
        }
        void start()
        {
            int current_time = 0;
            int completed = 0;

            while(completed != n) {
                int idx = -1;
                int mn = 10000000;
                for(int i = 0; i < n; i++) {
                    if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                        if(p[i].burst_time < mn) {
                            mn = p[i].burst_time;
                            idx = i;
                        }
                        if(p[i].burst_time == mn) {
                            if(p[i].arrival_time < p[idx].arrival_time) {
                                mn = p[i].burst_time;
                                idx = i;
                            }
                        }
                    }
                }
                if(idx != -1) {
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
                else {
                    current_time++;
                }
                
            }

            avg_turnaround_time = (float) total_turnaround_time / n;
            avg_waiting_time = (float) total_waiting_time / n;      

            cout<<endl<<endl;

            cout<<"#P\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

            for(int i = 0; i < n; i++) {
                cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<"\n"<<endl;
            }
            cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
            cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;

        }
};

class FCFS
{
    private:
        int n;
        struct process p[100];

        float avg_turnaround_time;
        float avg_waiting_time;
        
        
        int total_turnaround_time = 0;
        int total_waiting_time = 0;
        
        int is_completed[100];

        static bool compareArrival(process p1, process p2) 
        { 
            return p1.arrival_time < p2.arrival_time;
        }

        static bool compareID(process p1, process p2) 
        {  
            return p1.pid < p2.pid;
        }
    

    public:
        FCFS()
        {
            memset(is_completed,0,sizeof(is_completed));

            cout << setprecision(2) << fixed;
            cout<<"Enter the number of processes: ";
            cin>>n;

            for(int i = 0; i < n; i++) {
                cout<<"Enter arrival time of process "<<i+1<<": ";
                cin>>p[i].arrival_time;
                cout<<"Enter burst time of process "<<i+1<<": ";
                cin>>p[i].burst_time;
                p[i].pid = i+1;
                cout<<endl;
            }
        }
        void start()
        {
            sort(p,p+n,compareArrival);

            for(int i = 0; i < n; i++) {
                p[i].start_time = (i == 0) ? p[i].arrival_time : max(p[i-1].completion_time,p[i].arrival_time);
                //i = 0 O - arrival time 0 second, burst time 2 second
                //i = 1 A - arrival time 3 sec, burst time 5 second completion time 8 
                //i = 2 B - arrival time 4 sec, burst time 2 second start time
                p[i].completion_time = p[i].start_time + p[i].burst_time;
                p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
                p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

                total_turnaround_time += p[i].turnaround_time;
                total_waiting_time += p[i].waiting_time;
                
            }

            avg_turnaround_time = (float) total_turnaround_time / n;
            avg_waiting_time = (float) total_waiting_time / n;

            sort(p,p+n,compareID);

            cout<<endl;
            cout<<"#P\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

            for(int i = 0; i < n; i++) {
                cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<"\n"<<endl;
            }
            cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
            cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
            

        }
};
//Preemptive
class SRTF
{
    private:
        int n;
        struct process p[100];

        float avg_turnaround_time;
        float avg_waiting_time;
        
        
        int total_turnaround_time = 0;
        int total_waiting_time = 0;
        
        int is_completed[100];
        int burst_remaining[100];

    public:
        SRTF()
        {
            memset(is_completed,0,sizeof(is_completed));

            cout << setprecision(2) << fixed;
            cout<<"Enter the number of processes: ";
            cin>>n;

            for(int i = 0; i < n; i++) {
                cout<<"Enter arrival time of process "<<i+1<<": ";
                cin>>p[i].arrival_time;
                cout<<"Enter burst time of process "<<i+1<<": ";
                cin>>p[i].burst_time;
                p[i].pid = i+1;
                burst_remaining[i] = p[i].burst_time;
                cout<<endl;
            }
        }
        void start()
        {
            int current_time = 0;
            int completed = 0;
            

            while(completed != n) {
                int idx = -1;
                int mn = 10000000;
                for(int i = 0; i < n; i++) {
                    if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                        if(burst_remaining[i] < mn) {
                            mn = burst_remaining[i];
                            idx = i;
                        }
                        if(burst_remaining[i] == mn) {
                            if(p[i].arrival_time < p[idx].arrival_time) {
                                mn = burst_remaining[i];
                                idx = i;
                            }
                        }
                    }
                }

                if(idx != -1) {
                    if(burst_remaining[idx] == p[idx].burst_time) {
                        p[idx].start_time = current_time;
                    }
                    burst_remaining[idx] -= 1;
                    current_time++;
                    
                    if(burst_remaining[idx] == 0) {
                        p[idx].completion_time = current_time;
                        p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                        p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

                        total_turnaround_time += p[idx].turnaround_time;
                        total_waiting_time += p[idx].waiting_time;

                        is_completed[idx] = 1;
                        completed++;
                    }
                }
                else {
                    current_time++;
                }  
            }

            

            avg_turnaround_time = (float) total_turnaround_time / n;
            avg_waiting_time = (float) total_waiting_time / n;
        
    

            cout<<endl<<endl;

            cout<<"#P\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

            for(int i = 0; i < n; i++) {
                cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<"\n"<<endl;
            }
            cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
            cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
            
        }
};

class Non_Premptive_Priority
{
    int n;
    struct process p[100];

    float avg_turnaround_time;
    float avg_waiting_time;
    
    
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    
    int is_completed[100];
    

    public:
        Non_Premptive_Priority()
        {
            memset(is_completed,0,sizeof(is_completed));

            cout << setprecision(2) << fixed;
            cout<<"Enter the number of processes: ";
            cin>>n;

            for(int i = 0; i < n; i++) {
                cout<<"Enter arrival time of process "<<i+1<<": ";
                cin>>p[i].arrival_time;
                cout<<"Enter burst time of process "<<i+1<<": ";
                cin>>p[i].burst_time;
                cout<<"Enter priority of process "<<i+1<<": ";
                cin>>p[i].priority;
                p[i].pid = i+1;
                cout<<endl;
            }
        }
        void start()
        {
            int current_time = 0;
            int completed = 0;
            

            while(completed != n) {
                int idx = -1;
                int mx = -1;
                for(int i = 0; i < n; i++) {
                    if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                        if(p[i].priority > mx) {
                            mx = p[i].priority;
                            idx = i;
                        }
                        if(p[i].priority == mx) {
                            if(p[i].arrival_time < p[idx].arrival_time) {
                                mx = p[i].priority;
                                idx = i;
                            }
                        }
                    }
                }
                if(idx != -1) {
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
                else {
                    current_time++;
                }
                
            }

            

            avg_turnaround_time = (float) total_turnaround_time / n;
            avg_waiting_time = (float) total_waiting_time / n;
        
    

            cout<<endl<<endl;

            cout<<"#P\t"<<"AT\t"<<"BT\t"<<"PRI\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

            for(int i = 0; i < n; i++) {
                cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].priority<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<"\n"<<endl;
            }
            cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
            cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
            
        }
};
class Premptive_Priority
{
    int n;
    struct process p[100];

    float avg_turnaround_time;
    float avg_waiting_time;
    
    
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    
    int is_completed[100];
    int burst_remaining[100];

    public:
        Premptive_Priority()
        {
            memset(is_completed,0,sizeof(is_completed));

            cout << setprecision(2) << fixed;
            cout<<"Enter the number of processes: ";
            cin>>n;

            for(int i = 0; i < n; i++) {
                cout<<"Enter arrival time of process "<<i+1<<": ";
                cin>>p[i].arrival_time;
                cout<<"Enter burst time of process "<<i+1<<": ";
                cin>>p[i].burst_time;
                cout<<"Enter priority of process "<<i+1<<": ";
                cin>>p[i].priority;
                p[i].pid = i+1;
                burst_remaining[i] = p[i].burst_time;
                cout<<endl;
            }
        }
        void start()
        {
            int current_time = 0;
            int completed = 0;
            

            while(completed != n) {
                int idx = -1;
                int mx = -1;
                for(int i = 0; i < n; i++) {
                    if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                        if(p[i].priority > mx) {
                            mx = p[i].priority;
                            idx = i;
                        }
                        if(p[i].priority == mx) {
                            if(p[i].arrival_time < p[idx].arrival_time) {
                                mx = p[i].priority;
                                idx = i;
                            }
                        }
                    }
                }

                if(idx != -1) {
                    if(burst_remaining[idx] == p[idx].burst_time) {
                        p[idx].start_time = current_time;
                    }
                    burst_remaining[idx] -= 1;
                    current_time++;
                    
                    if(burst_remaining[idx] == 0) {
                        p[idx].completion_time = current_time;
                        p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                        p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                        
                        total_turnaround_time += p[idx].turnaround_time;
                        total_waiting_time += p[idx].waiting_time;                        

                        is_completed[idx] = 1;
                        completed++;
                    }
                }
                else {
                    current_time++;
                }  
            }

            

            avg_turnaround_time = (float) total_turnaround_time / n;
            avg_waiting_time = (float) total_waiting_time / n;
        
    

            cout<<endl<<endl;

            cout<<"#P\t"<<"AT\t"<<"BT\t"<<"PRI\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

            for(int i = 0; i < n; i++) {
                cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].priority<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<"\n"<<endl;
            }
            cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
            cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
        }
};

class RoundRobin
{
    int n;
    int tq;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int burst_remaining[100];

    static bool compare1(process p1, process p2) 
    { 
        return p1.arrival_time < p2.arrival_time;
    }

    static bool compare2(process p1, process p2) 
    {  
        return p1.pid < p2.pid;
    }

    public:
        RoundRobin()
        {

            cout << setprecision(2) << fixed;
            cout<<"Enter the number of processes: ";
            cin>>n;
            cout<<"Enter time quantum: ";
            cin>>tq;

            for(int i = 0; i < n; i++) {
                cout<<"Enter arrival time of process "<<i+1<<": ";
                cin>>p[i].arrival_time;
                cout<<"Enter burst time of process "<<i+1<<": ";
                cin>>p[i].burst_time;
                burst_remaining[i] = p[i].burst_time;
                p[i].pid = i+1;
                cout<<endl;
            }
        }
        void start()
        {
            int idx;
            sort(p,p+n,compare1);
            
            queue<int> q;
            int current_time = 0;
            q.push(0);
            int completed = 0;
            int mark[100];
            memset(mark,0,sizeof(mark));
            mark[0] = 1;

            while(completed != n) {
                idx = q.front();
                q.pop();

                if(burst_remaining[idx] == p[idx].burst_time) {
                    p[idx].start_time = max(current_time,p[idx].arrival_time);
                    current_time = p[idx].start_time;
                }

                if(burst_remaining[idx]-tq > 0) {
                    burst_remaining[idx] -= tq;
                    current_time += tq;
                }
                else {
                    current_time += burst_remaining[idx];
                    burst_remaining[idx] = 0;
                    completed++;

                    p[idx].completion_time = current_time;
                    p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                    p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

                    total_turnaround_time += p[idx].turnaround_time;
                    total_waiting_time += p[idx].waiting_time;
                }

                for(int i = 1; i < n; i++) {
                    if(burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
                        q.push(i);
                        mark[i] = 1;
                    }
                }
                if(burst_remaining[idx] > 0) {
                    q.push(idx);
                }

                if(q.empty()) {
                    for(int i = 1; i < n; i++) {
                        if(burst_remaining[i] > 0) {
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
            cout<<"#P\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

            for(int i = 0; i < n; i++) {
                cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].burst_time<<"\t"<<p[i].start_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<"\n"<<endl;
            }
            cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
            cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
        }
};

int main()
{
    while (true)
    {
        cout << "Choose the CPU Scheduling algorithm\n";
        cout << "1. FCFS\n2. SJF\n3. SRTF\n4. Non-preemptive Priority\n5. Preemptive Priority\n6. Round Robin\n";
        int ch;
        cin >> ch;

        switch (ch)
        {
            case 1:
            {
                FCFS algo;
                algo.start();
                break;
            }
            case 2:
            {
                SJF algo;
                algo.start();
                break;
            }
            case 3:
            {
                SRTF algo;
                algo.start();
                break;
            }
            case 4:
            {
                Non_Premptive_Priority algo;
                algo.start();
                break;
            }
            case 5:
            {
                Premptive_Priority algo;
                algo.start();
                break;
            }
            case 6:
            {
                RoundRobin algo;
                algo.start();
                break;
            }
            default:
            {
                cout << "Please provide a valid input\n";
            }
        }

        cout << "Do you want to continue? Y/N: ";
        char c;
        cin >> c;
        if (c == 'y' || c == 'Y') continue;
        else break;
    }

}