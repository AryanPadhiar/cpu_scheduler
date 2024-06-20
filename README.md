# cpu_scheduler
 
CPU Scheduler: Implementation of Various Scheduling Algorithms

## Project Overview
This project is designed to implement and compare the performance of several CPU scheduling algorithms. These algorithms include First-Come-First-Serve (FCFS), Shortest Job First (SJF), Round Robin (RR), Shortest Remaining Time First (SRTF), and an Innovative algorithm. The comparison is based on key performance metrics such as average waiting time, average turnaround time, and CPU idleness.

## How to Run the Project
### Dependencies
To run this project, you will need:
- A C++ compiler supporting C++11 or later.
- A terminal or command line interface.

### Steps to Run
1. **Clone the Repository:**
   ```bash
   git clone [https://github.com/love-mishra/CPU-Scheduler.git](https://github.com/AryanPadhiar/cpu_scheduler.git)
   cd cpu-scheduler
   ```

2. **Compile the Code:**
   ```bash
   g++ -std=c++11 -o cpu cpu.cpp
   ```

3. **Run the Executable:**
   ```bash
   ./acm
   ```

4. **Follow On-Screen Instructions:**
   - Input the processes' details as prompted.
   - Choose the scheduling algorithm to simulate.
   - View the results and performance metrics.

## Internal Working of the Project
### Theory
CPU scheduling is a fundamental aspect of operating system design, ensuring efficient execution of processes. The algorithms implemented are:
1. **First-Come-First-Serve (FCFS):**
   - Executes processes in the order they arrive.
   - Simple but can lead to high waiting times due to the Convoy effect.

2. **Shortest Job First (SJF):**
   - Executes processes with the shortest burst time first.
   - Optimal for average waiting time but can cause starvation for longer processes.

3. **Round Robin (RR):**
   - Assigns a fixed time quantum to each process.
   - Ensures fair CPU time distribution but may incur high context switching overhead.

4. **Shortest Remaining Time First (SRTF):**
   - Preemptive version of SJF, selecting the process with the shortest remaining burst time.
   - Efficient but complex and can lead to starvation.

5. **Innovative Algorithm:**
   - A custom algorithm designed to balance performance.
   - Uses the median burst time as a time quantum.
   - Aims to achieve a balanced performance across all metrics.

### Implementation Details
- **Input Handling:** Supports both offline and online queries for process details.
- **Sorting and Scheduling:** Processes are sorted based on arrival times, and scheduling algorithms are applied to determine the order of execution.
- **Performance Metrics:** Calculates average waiting time, average turnaround time, and CPU idleness for each algorithm.
- **Visualization:** Displays the start and finish times of processes, along with their states during execution.

## Learning Takeaways
- Gained a thorough understanding of various CPU scheduling algorithms and their trade-offs.
- Enhanced C++ programming skills, especially using STL and designing algorithms.
- Learned about process synchronization and scheduling techniques.
- Developed the ability to analyze and optimize algorithm performance.

## Resources and References
- GeeksforGeeks: [CPU Scheduling Algorithms](https://www.geeksforgeeks.org/cpu-scheduling-in-operating-systems/).
- Stack Overflow for troubleshooting and coding tips.
- [YouTube Playlist on CPU Scheduling](https://www.youtube.com/playlist?list=PLBlnK6fEyqRitWSE_AyyySWfhRgyA-rHk)

 
