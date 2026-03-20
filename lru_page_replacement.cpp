#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, frames_count; //No of pages and frame count
    cout << "Enter number of pages: "; cin >> n;
    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];

    cout << "Enter number of frames: "; cin >> frames_count;

    vector<int> frames;
    int page_faults = 0; //Assume there are 0 page faults at starting

    for (int i = 0; i < n; i++) {
        auto it = find(frames.begin(), frames.end(), pages[i]);

        if (it == frames.end()) { //page not available in RAM it will return end pointer
            page_faults++; //increment page fault
            if (frames.size() < frames_count) { //we have enough frame to add a page
                frames.push_back(pages[i]); //so push page in RAM
            } else { //frames are full
                frames.erase(frames.begin()); //erase starting page because its not used for long time (Core Logic of LRU)
                frames.push_back(pages[i]); //push the page 
            }
        } else { //page already available in Ram (page hit)
            frames.erase(it); //we need to erase it bcoz the current page is recently used (as we got page hit)
            frames.push_back(pages[i]); //push the page
        }
    }

    cout << "\nTotal Page Faults: " << page_faults << endl;
    cout << "Total Page Hits: " << n - page_faults << endl;

    return 0;
}
