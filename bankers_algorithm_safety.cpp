#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cout << "Enter number of processes: "; cin >> n;  //total no of processes 
    cout << "Enter number of resources: "; cin >> m; //total no of resources

    vector<vector<int>> alloc(n, vector<int>(m)); //already allocated resources
    vector<vector<int>> max_need(n, vector<int>(m)); //maximum need of resources of a particular process 
    vector<int> avail(m); //currently available resources

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> alloc[i][j];

    cout << "Enter Max Need Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> max_need[i][j];

    cout << "Enter Available Resources: ";
    for (int i = 0; i < m; i++) cin >> avail[i];

    vector<vector<int>> need(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max_need[i][j] - alloc[i][j]; //current need of any process (max - alloc)

    vector<bool> finish(n, false);
    vector<int> safe_seq;
    vector<int> work = avail;
//check if we have enough no of resources to complete any process
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool possible = true; 
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
//if we have enough no of resources then possible will always equal to true and if possible = true then allocate that resources to the particular process complete it and push it in the safe sequence
                if (possible) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j]; //once executed take resoiurces back (resource reclaimation)
                    safe_seq.push_back(i);
                    finish[i] = true;
                }
            }
        }
    }
//Now check if all processes executed or not , if any process is remaining to execute(not enough resources) then safe will become false and system is not in safe state
    bool safe = true;
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            safe = false;
            break;
        }
    }

    if (safe) {
        cout << "\nSystem is in SAFE State.\nSafe Sequence: ";
        for (int i = 0; i < safe_seq.size(); i++)
            cout << "P" << safe_seq[i] << (i == n - 1 ? "" : " -> ");
        cout << endl;
    } else {
        cout << "\nSystem is in DEADLOCK/UNSAFE State." << endl;
    }

    return 0;
}
