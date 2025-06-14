# 🔧 Schedulix – Modular CPU Scheduling Simulator in C++

Schedulix is a modular and extensible C++ simulator for visualizing and analyzing classical CPU scheduling algorithms. This is not just a course project—it’s a full-fledged **Operating Systems + DSA integration** that models real-world schedulers in a testable and traceable way.

---

## 🧠 What is CPU Scheduling?

In a multitasking operating system, **CPU scheduling** determines which process will be assigned to the CPU at any given time. Since the CPU can only execute one process at a time, scheduling policies aim to optimize key performance metrics such as:

- Turnaround time
- Waiting time
- CPU utilization
- Fairness and response time

This simulator implements some of the most important CPU scheduling algorithms, both **preemptive** and **non-preemptive**, and provides trace-level output for understanding each decision made by the scheduler.

---

## 📘 Implemented Algorithms

### 1. First Come First Serve (FCFS)
- Non-preemptive
- Processes are served in the order they arrive.
- Easy to implement but suffers from convoy effect.

### 2. Round Robin (RR)
- Preemptive
- Each process gets a fixed time slice (quantum).
- Good for time-sharing systems and fairness.

### 3. Shortest Process Next (SPN)
- Non-preemptive
- Picks the job with the smallest service time.
- Minimizes average waiting time but can cause starvation.

### 4. Shortest Remaining Time (SRT)
- Preemptive version of SPN.
- At every unit, chooses process with least remaining burst time.
- Highly responsive but complex to implement.

### 5. Highest Response Ratio Next (HRRN)
- Non-preemptive
- Prioritizes based on: `(waiting time + service time) / service time`
- Balances fairness and efficiency, avoids starvation.

### 6. Feedback with fixed quantum (FB-1)
- Preemptive
- Multilevel feedback queue, each queue with q = 1
- Long jobs slowly demoted to lower queues

### 7. Feedback with increasing quantum (FB-2i)
- Preemptive
- Queue `i` has quantum `2^i`, adapting to job length
- Better for balancing short and long jobs

### 8. Aging
- Preemptive
- Priority-based scheduling with aging to avoid starvation
- Each ready process gains priority over time

---

## 🛠️ Project Structure
Schedulix/
│
├── main.cpp # Driver file
├── parser.h # Parses input and builds process structures
├── utils.h # Helper functions and constants
├── print.h # Output formatting for trace/statistics
├── fcfs.h # FCFS algorithm
├── rr.h # Round Robin algorithm
├── spn.h # Shortest Process Next
├── srt.h # Shortest Remaining Time
├── hrrn.h # Highest Response Ratio Next
├── fb1.h # Feedback with q=1
├── fb2i.h # Feedback with q=2^i
├── aging.h # Aging-based scheduler
├── Makefile # Easy build automation
└── testcases/ # Sample input/output test files
├── input1.txt
├── output1.txt

# Schedulix CPU Scheduler: Getting Started

This guide will walk you through cloning, building, and running the Schedulix CPU Scheduler simulator.

---

## 1. Clone the Repository

First, clone the Schedulix repository into a folder named "CPU Scheduler" and navigate into the directory.

```bash
git clone [https://github.com/your-username/Schedulix.git](https://github.com/your-username/Schedulix.git) "CPU Scheduler"
cd "CPU Scheduler"

## 2. Build the Project

Ensure you have g++ (with C++17 support) and make installed on your system. Then, build the project using make.

```bash
make

## 3. Run the Simulator

You can run the simulator with various test cases. Here's an example of running it in trace mode with the first test case and saving the output to a file.

```bash
./schedulix

## 4. Clean Up

When you're finished, you can remove the executable files using make clean.

```bash
make clean

## 📝 Input & Output Format

This simulator accepts input through standard input or from an input file. The input describes the simulation mode, algorithms to apply, time constraints, and process details. Below is a structured breakdown of the expected format:

### 📥 Input Format

The input must follow **exactly this structure**, in **multiple lines**:

1. **Line 1:**  
   A keyword that specifies the output mode:  
   - `"trace"` → Show timeline simulation of process execution.  
   - `"stats"` → Show statistics such as turnaround and waiting times.

2. **Line 2:**  
   A comma-separated list of scheduling policies you want to simulate.  
   Each policy is represented by a number, optionally followed by a parameter (like time quantum `q`), separated by a hyphen.

   **Supported Algorithms:**

   | Number | Algorithm                                  | Notes                                 |
   |--------|--------------------------------------------|----------------------------------------|
   | 1      | FCFS (First Come First Serve)              | Non-preemptive                         |
   | 2-q    | RR (Round Robin with quantum q)            | Preemptive                             |
   | 3      | SPN (Shortest Process Next)                | Non-preemptive                         |
   | 4      | SRT (Shortest Remaining Time)              | Preemptive                             |
   | 5      | HRRN (Highest Response Ratio Next)         | Non-preemptive                         |
   | 6      | FB-1 (Feedback with fixed q = 1)           | Multi-level, preemptive                |
   | 7      | FB-2i (Feedback with exponentially increasing q) | Multi-level, preemptive         |
   | 8-q    | Aging (priority aging with interval q)     | Non-preemptive                         |

   Example:  
   1,2-4,5,8-1

This means simulate FCFS, Round Robin (q = 4), HRRN, and Aging (q = 1).

3. **Line 3:**  
An integer representing the total simulation time (timeline’s end point).

4. **Line 4:**  
An integer specifying the number of processes.

5. **Lines 5 and onward:**  
Each line contains process data in a comma-separated format.

- For algorithms 1–7 (non-aging algorithms):
  ```
  <ProcessName>,<ArrivalTime>,<ServiceTime>
  ```

- For algorithm 8 (Aging):
  ```
  <ProcessName>,<ArrivalTime>,<Priority>
  ```

Example (for FCFS):
trace
1
20
3
P1,0,5
P2,2,3
P3,4,4

stats
8-1
25
2
P1,0,3
P2,5,5


**Note:**  
Processes should be listed in ascending order of arrival time. If two processes arrive at the same time, the one with lower priority (in case of Aging) or as they appear in the list (for others) is assumed to arrive first. If not the input will be sorted in increasing order of arrival time and in case of a tie, the one with lower index will be plced before(assuming higgher priority)

### 📤 Output Format

The output varies based on the mode selected:

- In `"trace"` mode:  
A visual representation (timeline) of how each process is scheduled over time, per algorithm.

- In `"stats"` mode:  
Detailed statistics per algorithm including:
- Turnaround time
- Waiting time
- Normalized turnaround time
- Average metrics for all processes

> For reference, sample input/output files are available in the `testcases/` directory. You can use them directly or create your own following the same structure.

