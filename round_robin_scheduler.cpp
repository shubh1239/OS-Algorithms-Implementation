#include<iostream>
#include<vector>
#include<queue>
#include<iomanip>

using namespace std;

struct Process {
    int id;    //process id
    int burst_time;
    int remaining_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
};

void calculateTimes(vector<Process>& processes, int quantum) {
    int current_time = 0;  //starting time = 0
    queue<int> ready_queue; 
    int completed = 0;  //how many processes currently completed
    int n = processes.size(); //total no of processes 
    vector<bool> is_in_queue(n, false); //check if the current process is already in ready queue

    // Initial check for processes arriving at time 0
    for(int i = 0; i < n; i++) {
        if(processes[i].arrival_time <= current_time) {  //necessary condition to check if any process AT = 0 or not
            ready_queue.push(i); //if AT of any process is 0 then push in ready queue
            is_in_queue[i] = true; #for the process pushed in queue make is_in_queue = true for that process
        }
    }

    while(completed < n) {
        if(ready_queue.empty()) { //necessary to check whether cpu is in idle condition or not (optimization)
            current_time++; //increment time to reach that time period where any process is available to execute on cpu 
            for(int i = 0; i < n; i++) {
                if(processes[i].arrival_time <= current_time && !is_in_queue[i]) { //check if any process is ready to execute on CPU
                    ready_queue.push(i);
                    is_in_queue[i] = true;
                }
            }
            continue;
        }

        int idx = ready_queue.front();  // idx hold the pid of current process executing on cpu
        ready_queue.pop(); // CPU first pop out the process of queue and then execute it 

        int execute_time = min(processes[idx].remaining_time, quantum); //Core logic of RR algo 
        processes[idx].remaining_time -= execute_time;
        current_time += execute_time;

        // Check for new arrivals during execution
        for(int i = 0; i < n; i++) {
            if(processes[i].arrival_time <= current_time && !is_in_queue[i] && processes[i].remaining_time > 0) { // while executing if any process arrives which is not in ready queue and whose AT is less than current time and having remaining time greater than 0 push it in queue 
                ready_queue.push(i);
                is_in_queue[i] = true;
            }
        }

        if(processes[idx].remaining_time > 0) { 
            ready_queue.push(idx);
        } else {
            completed++;
            processes[idx].turnaround_time = current_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
        }
    }
}

int main() {
    int n, quantum;
    cout << "--- OS Scheduling Simulator: Round Robin ---" << endl;
    cout << "Enter number of processes: "; cin >> n;
    cout << "Enter Time Quantum: "; cin >> quantum;

    vector<Process> processes(n);
    for(int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Arrival Time & Burst Time for P" << i+1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    calculateTimes(processes, quantum);

    cout << "\nPID\tArrival\tBurst\tWaiting\tTurnaround\n";
    for(auto p : processes) {
        cout << p.id << "\t" << p.arrival_time << "\t" << p.burst_time << "\t" 
             << p.waiting_time << "\t" << p.turnaround_time << endl;
    }
    return 0;
}
