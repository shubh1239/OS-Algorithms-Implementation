# OS-Algorithms-Implementation
High-accuracy implementation of Operating System algorithms based on GATE theoretical frameworks.


This repository contains robust implementations of core OS concepts. The logic is derived from a deep theoretical study of Operating Systems

## 🚀 Projects Included

### 1. Round Robin Scheduling Simulator (`round_robin_scheduler.cpp`)
A preemptive scheduling algorithm designed for time-sharing systems.

**Key Features:**
* **Idle Time Management:** Specifically handles cases where the CPU is idle due to no process arrivals (Gaps in the Gantt Chart).
* **Dynamic Queue Management:** Implements `is_in_queue` logic to ensure processes are not redundantly pushed into the ready queue.
* **Context Awareness:** Accurately calculates Waiting Time (WT) and Turnaround Time (TAT) by tracking `remaining_time` vs `time_quantum`.

## 🛠️ How to Run
```bash
g++ round_robin_scheduler.cpp -o rr_sched
./rr_sched

**2. Banker's Algorithm (Deadlock Avoidance)**
Implements the Safety Algorithm to determine if a system can allocate resources without entering a deadlock state.

Uses a Work-Finish approach to simulate resource reclamation.

3. FIFO Page Replacement (fifo_page_replacement.cpp)
Implements the First-In-First-Out approach for memory management.
Uses an unordered_set for O(1) page-hit detection and a queue to track page arrival order.
Demonstrates the Cold Start phase (initial frame filling) and the Replacement phase.
