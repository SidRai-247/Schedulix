// Author: Siddharth Rai
// CP Template
#include <bits/stdc++.h>
#define ll long long
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define ff first
#define ss second
#define rep(i, n) for (ll i = 0; i < (n); ++i)
#define yes cout << "YES\n"
#define no cout << "NO\n"
using namespace std;

/** Global Constants **/
const string TRACE = "trace";
const string SHOW_STATISTICS = "stats";
const string ALGORITHMS[9] = {"", "FCFS", "RR-", "SPN", "SRT", "HRRN", "FB-1", "FB-2i", "AGING"};

// Main Helper Headers
#include "parser.h" // Handles User Input and Data Structures
#include "utils.h"  // Handles custom sorting comaprators and other useful functions
#include "print.h"  // Handles Printing functionalities

// Scheduling Algorithm Headers
#include "fcfs.h"
#include "rr.h"
#include "sjf.h"
#include "srt.h"
#include "hrrn.h"
#include "fq1.h"
#include "fq2i.h"
#include "aging.h"

// Mapping Algorithm ID to respective Functions.
void execute_algorithm(char algorithm_id, int quantum, string operation)
{
    switch (algorithm_id)
    {
    case '1':
        if (operation == TRACE)
            cout << "FCFS  ";
        firstComeFirstServe();
        break;
    case '2':
        if (operation == TRACE)
            cout << "RR-" << quantum << "  ";
        roundRobin(quantum);
        break;
    case '3':
        if (operation == TRACE)
            cout << "SPN   ";
        shortestProcessNext();
        break;
    case '4':
        if (operation == TRACE)
            cout << "SRT   ";
        shortestRemainingTime();
        break;
    case '5':
        if (operation == TRACE)
            cout << "HRRN  ";
        highestResponseRatioNext();
        break;
    case '6':
        if (operation == TRACE)
            cout << "FB-1  ";
        feedbackQ1();
        break;
    case '7':
        if (operation == TRACE)
            cout << "FB-2i ";
        feedbackQ2i();
        break;
    case '8':
        if (operation == TRACE)
            cout << "Aging ";
        aging(quantum);
        break;
    default:
        break;
    }
}

int main()
{
    // Take the User Input
    parse();

    // //Pre-Processing the Input: Sorting in increasing oredr of arrival time, index
    vector<pair<int, int>> arrivalWithIndex;
    for (int i = 0; i < processes.size(); ++i)
    {
        arrivalWithIndex.push_back({get<1>(processes[i]), i}); // {arrivalTime, originalIndex}
    }

    // // Sort: first by arrival time, then by smaller index
    sort(arrivalWithIndex.begin(), arrivalWithIndex.end());
    vector<tuple<string, int, int>> sortedProcesses;
    for (auto &p : arrivalWithIndex) sortedProcesses.push_back(processes[p.second]);
    processes = sortedProcesses;

    // Main task:
    // Run for each Algorithm
    for (int idx = 0; idx < (int)algorithms.size(); idx++)
    {
        // Clear the Timeline for next Algorithm
        clear_timeline();
        execute_algorithm(algorithms[idx].first, algorithms[idx].second, operation);
        // cout << last_instant << " " << process_count << "\n";
        if (operation == TRACE)
        {
            // Mark the Waiting times for the Processes
            fillInWaitTime();
            printTimeline(idx);
        }
        else if (operation == SHOW_STATISTICS)
            printStats(idx);
        cout << "\n";
    }
    return 0;
}