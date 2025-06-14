#ifndef SJF_H
#define SJF_H

// Shortest Process Next (SPN) - Non-preemptive Shortest Job First
void shortestProcessNext()
{
    using Job = pair<int, int>; // {serviceTime, processIndex}
    priority_queue<Job, vector<Job>, greater<Job>> readyQueue;

    int time = 0, nextArrivalIdx = 0;

    while (time < last_instant)
    {
        // Add processes that have arrived by current time
        while (nextArrivalIdx < process_count && getArrivalTime(processes[nextArrivalIdx]) <= time)
        {
            int st = getServiceTime(processes[nextArrivalIdx]);
            readyQueue.push({st, nextArrivalIdx});
            ++nextArrivalIdx;
        }

        if (readyQueue.empty())
        {
            // No process ready, CPU is idle
            ++time;
            continue;
        }

        auto [serviceTime, pid] = readyQueue.top();
        readyQueue.pop();
        int arrival = getArrivalTime(processes[pid]);

        // Fill in waiting time with '.'
        for (int t = arrival; t < time && t < last_instant; ++t)
        {
            timeline[t][pid] = '.';
        }

        // Execute for serviceTime units (mark '*')
        for (int t = 0; t < serviceTime && time < last_instant; ++t, ++time)
        {
            timeline[time][pid] = '*';
        }

        finishTime[pid] = time;
        turnAroundTime[pid] = finishTime[pid] - arrival;
        normTurn[pid] = static_cast<float>(turnAroundTime[pid]) / serviceTime;
    }
}

#endif // SJF_H
