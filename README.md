# 🔧 Schedulix – Modular CPU Scheduling Simulator in C++

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![License](https://img.shields.io/badge/license-MIT-green.svg)]()

Schedulix is a modular and extensible C++ simulator for visualizing and analyzing classical CPU scheduling algorithms. This is not just a course project—it's a full-fledged **Operating Systems + DSA integration** that models real-world schedulers in a testable and traceable way.

---

## 🧠 What is CPU Scheduling?

In a multitasking operating system, **CPU scheduling** determines which process will be assigned to the CPU at any given time. Since the CPU can only execute one process at a time, scheduling policies aim to optimize key performance metrics such as:

- **Turnaround time** - Total time from arrival to completion
- **Waiting time** - Time spent waiting in ready queue
- **CPU utilization** - Percentage of time CPU is busy
- **Fairness and response time** - Equal treatment and quick responsiveness

This simulator implements some of the most important CPU scheduling algorithms, both **preemptive** and **non-preemptive**, and provides trace-level output for understanding each decision made by the scheduler.

---

## 📘 Implemented Algorithms

### 1. First Come First Serve (FCFS)
- **Type:** Non-preemptive
- **Description:** Processes are served in the order they arrive
- **Pros:** Simple to implement
- **Cons:** Suffers from convoy effect

### 2. Round Robin (RR)
- **Type:** Preemptive
- **Description:** Each process gets a fixed time slice (quantum)
- **Pros:** Good for time-sharing systems and fairness
- **Cons:** Performance depends on quantum size

### 3. Shortest Process Next (SPN)
- **Type:** Non-preemptive
- **Description:** Picks the job with the smallest service time
- **Pros:** Minimizes average waiting time
- **Cons:** Can cause starvation of long processes

### 4. Shortest Remaining Time (SRT)
- **Type:** Preemptive (preemptive version of SPN)
- **Description:** At every unit, chooses process with least remaining burst time
- **Pros:** Highly responsive
- **Cons:** Complex to implement, high overhead

### 5. Highest Response Ratio Next (HRRN)
- **Type:** Non-preemptive
- **Description:** Prioritizes based on: `(waiting time + service time) / service time`
- **Pros:** Balances fairness and efficiency, avoids starvation
- **Cons:** Requires calculation of response ratios

### 6. Feedback with Fixed Quantum (FB-1)
- **Type:** Preemptive
- **Description:** Multilevel feedback queue, each queue with quantum = 1
- **Pros:** Adaptive to job characteristics
- **Cons:** Long jobs slowly demoted to lower queues

### 7. Feedback with Increasing Quantum (FB-2i)
- **Type:** Preemptive
- **Description:** Queue `i` has quantum `2^i`, adapting to job length
- **Pros:** Better for balancing short and long jobs
- **Cons:** Complex queue management

### 8. Aging
- **Type:** Preemptive
- **Description:** Priority-based scheduling with aging to avoid starvation
- **Pros:** Each ready process gains priority over time
- **Cons:** Overhead of priority updates

---

## 🛠️ Project Structure

```
Schedulix/
│
├── main.cpp          # Driver file
├── parser.h          # Parses input and builds process structures
├── utils.h           # Helper functions and constants
├── print.h           # Output formatting for trace/statistics
├── fcfs.h            # FCFS algorithm
├── rr.h              # Round Robin algorithm
├── spn.h             # Shortest Process Next
├── srt.h             # Shortest Remaining Time
├── hrrn.h            # Highest Response Ratio Next
├── fb1.h             # Feedback with q=1
├── fb2i.h            # Feedback with q=2^i
├── aging.h           # Aging-based scheduler
├── Makefile          # Easy build automation
└── testcases/        # Sample input/output test files
    ├── input1.txt
    └── output1.txt
```

---

## 🚀 Getting Started

### Prerequisites

- **C++ Compiler:** g++ with C++17 support
- **Build System:** make
- **Operating System:** Linux, macOS, or Windows (with WSL/MinGW)

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/Schedulix.git "CPU Scheduler"
cd "CPU Scheduler"
```

### 2. Build the Project

```bash
make
```

### 3. Run the Simulator

```bash
./schedulix
```

The program will wait for input from stdin. You can also redirect input from a file:

```bash
./schedulix < testcases/input1.txt
```

Or save output to a file:

```bash
./schedulix < testcases/input1.txt > output.txt
```

### 4. Clean Up

```bash
make clean
```

---

## 📝 Input & Output Format

### 📥 Input Format

The input must follow this **exact structure** with **multiple lines**:

#### Line 1: Output Mode
A keyword that specifies the output mode:
- `trace` → Show timeline simulation of process execution
- `stats` → Show statistics such as turnaround and waiting times

#### Line 2: Scheduling Algorithms
A comma-separated list of scheduling policies to simulate. Each policy is represented by a number, optionally followed by a parameter (like time quantum `q`), separated by a hyphen.

| Number | Algorithm | Type | Parameter |
|--------|-----------|------|-----------|
| `1` | FCFS (First Come First Serve) | Non-preemptive | None |
| `2-q` | RR (Round Robin) | Preemptive | `q` = time quantum |
| `3` | SPN (Shortest Process Next) | Non-preemptive | None |
| `4` | SRT (Shortest Remaining Time) | Preemptive | None |
| `5` | HRRN (Highest Response Ratio Next) | Non-preemptive | None |
| `6` | FB-1 (Feedback with fixed q = 1) | Multi-level, preemptive | None |
| `7` | FB-2i (Feedback with exponential q) | Multi-level, preemptive | None |
| `8-q` | Aging (priority aging) | Preemptive | `q` = aging interval |

**Example:** `1,2-4,5,8-1` means simulate FCFS, Round Robin (q=4), HRRN, and Aging (q=1).

#### Line 3: Simulation Time
An integer representing the total simulation time (timeline's end point).

#### Line 4: Number of Processes
An integer specifying the number of processes.

#### Lines 5+: Process Data
Each line contains process data in comma-separated format:

**For algorithms 1-7 (non-aging):**
```
<ProcessName>,<ArrivalTime>,<ServiceTime>
```

**For algorithm 8 (Aging):**
```
<ProcessName>,<ArrivalTime>,<Priority>
```

### 📤 Output Format

**Trace Mode (`trace`):**
- Visual timeline representation of process scheduling
- Shows which process runs at each time unit
- Separate timeline for each algorithm

**Statistics Mode (`stats`):**
- Detailed performance metrics per algorithm:
  - **Turnaround Time:** Completion time - Arrival time
  - **Waiting Time:** Turnaround time - Service time
  - **Normalized Turnaround Time:** Turnaround time / Service time
  - **Average Metrics:** Mean values across all processes

---

## 📋 Example Usage

### Example 1: Trace Mode

**Input:**
```
trace
1,2-3
10
2
P1,0,4
P2,2,3
```

**Output:** Timeline showing FCFS and Round Robin (q=3) execution.

### Example 2: Statistics Mode

**Input:**
```
stats
8-1
25
2
P1,0,3
P2,5,5
```

**Output:** Performance statistics for Aging algorithm with interval 1.

---

## 🧪 Testing

Sample test cases are provided in the `testcases/` directory:

```bash
# Run a specific test case
./schedulix
```

---



## 🙏 Acknowledgments

- Operating Systems course materials and references
- Classical CPU scheduling algorithm implementations
- C++ STL for efficient data structures

---


**Happy Scheduling! 🎯**