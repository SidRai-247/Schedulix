#ifndef HRNN_H_INCLUDED
#define HRNN_H_INCLUDED

// Highest Response Ratio Next (HRRN) Scheduling Algorithm
// Non-preemptive: selects the process with the highest response ratio
void highestResponseRatioNext()
{
    vector<tuple<string, double, int>> readyQueue; // (processName, responseRatio, executedTime)
    int j = 0;

    for (int time = 0; time < last_instant;)
    {
        // Add processes that have arrived by 'time'
        while (j < process_count && getArrivalTime(processes[j]) <= time)
        {
            readyQueue.emplace_back(getProcessName(processes[j]), 1.0, 0);
            ++j;
        }

        if (readyQueue.empty())
        {
            // CPU is idle
            ++time;
            continue;
        }

        // Update response ratios for all processes in the ready queue
        for (auto &proc : readyQueue)
        {
            const string &name = get<0>(proc);
            int idx = processToIndex[name];
            int arrival = getArrivalTime(processes[idx]);
            int service = getServiceTime(processes[idx]);
            int waitingTime = time - arrival;
            get<1>(proc) = calculate_response_ratio(waitingTime, service);
        }

        // Select process with highest response ratio
        sort(readyQueue.begin(), readyQueue.end(), descendingly_by_response_ratio);

        const string &selectedName = get<0>(readyQueue[0]);
        int selectedIdx = processToIndex[selectedName];
        int serviceTime = getServiceTime(processes[selectedIdx]);

        // Execute selected process non-preemptively
        for (int exec = 0; exec < serviceTime && time < last_instant; ++exec, ++time)
        {
            timeline[time][selectedIdx] = '*';
        }

        finishTime[selectedIdx] = time;
        turnAroundTime[selectedIdx] = finishTime[selectedIdx] - getArrivalTime(processes[selectedIdx]);
        normTurn[selectedIdx] = turnAroundTime[selectedIdx] * 1.0f / serviceTime;

        // Remove from ready queue
        readyQueue.erase(readyQueue.begin());
    }

    // fillInWaitTime(); // Optional: call externally if needed
}

#endif // HRNN_H_INCLUDED
