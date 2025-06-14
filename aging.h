#ifndef AGING_H_INCLUDED
#define AGING_H_INCLUDED

// Aging Scheduling Algorithm
// Processes are assigned priorities and promoted gradually to prevent starvation
void aging(int originalQuantum)
{
    vector<tuple<int, int, int>> readyQueue; // (priority, index, waitingTime)
    int j = 0, currentProcess = -1;

    for (int time = 0; time < last_instant; time++)
    {
        // Add all processes that have arrived by current time
        while (j < process_count && getArrivalTime(processes[j]) <= time)
        {
            readyQueue.push_back(make_tuple(getPriorityLevel(processes[j]), j, 0));
            j++;
        }

        // Update priorities and waiting time
        for (auto &entry : readyQueue)
        {
            int idx = get<1>(entry);
            if (idx == currentProcess)
            {
                get<2>(entry) = 0;                                // Reset waiting time
                get<0>(entry) = getPriorityLevel(processes[idx]); // Restore original priority
            }
            else
            {
                get<2>(entry)++; // Increment waiting time
                get<0>(entry)++; // Improve priority (lower number is higher priority)
            }
        }

        // Sort by effective priority (lowest value first)
        sort(readyQueue.begin(), readyQueue.end(), byPriorityLevel);

        // Select process with highest effective priority
        currentProcess = get<1>(readyQueue[0]);
        int quantum = originalQuantum;

        // Run selected process for the time slice or until end
        while (quantum-- && time < last_instant)
        {
            timeline[time][currentProcess] = '*';
            time++;
        }
        time--; // Adjust outer loop increment
    }
    // There is no particular end time, so we can set to the last_instant
    for (int i = 0; i < process_count; i++)
    {
        finishTime[i] = last_instant;
    }
}

#endif // AGING_H_INCLUDED
