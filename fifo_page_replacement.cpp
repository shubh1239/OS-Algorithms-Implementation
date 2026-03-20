#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

int main() {
    int n, frames_count; //No of pages and frame count
    cout << "Enter number of pages: "; cin >> n;
    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];

    cout << "Enter number of frames: "; cin >> frames_count;

    unordered_set<int> s; //to check if page is already in RAM or not
    queue<int> indexes;  

    int page_faults = 0;  //assume at strting therev are no page faults
    for (int i = 0; i < n; i++) {
        if (s.size() < frames_count) { // to check if we have space remaining in RAM or not
            if (s.find(pages[i]) == s.end()) { // to check if the page is available in RAM or not , if not available it will return the end pointer
                s.insert(pages[i]); // if page not available insert it 
                page_faults++; //increase page fault by 1 
                indexes.push(pages[i]); //push that page
            }
        } else { //If we don’t have enough space in ram or frames are full
            if (s.find(pages[i]) == s.end()) {  //page not available in ram (page fault)
                int val = indexes.front(); //core logic of FIFO , val will store front pointer
                indexes.pop(); // pop the val 
                s.erase(val); //erase the value in val
                s.insert(pages[i]); //insert that page 
                indexes.push(pages[i]); //push that page 
                page_faults++; //increment page fault
            }
        }
    }

    cout << "\nTotal Page Faults: " << page_faults << endl;
    cout << "Total Page Hits: " << n - page_faults << endl;

    return 0;
}
