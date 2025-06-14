#ifndef SRT_H_INCLUDED
#define SRT_H_INCLUDED

// Shortest Remaining Time First (Preemptive SJF)
void shortestRemainingTime()
{
    using Process = pair<int, int>; // {remainingTime, processIndex}
    priority_queue<Process, vector<Process>, greater<>> readyQueue;

    vector<int> remainingTime(process_count);
    vector<bool> isCompleted(process_count, false);

    for (int i = 0; i < process_count; ++i)
        remainingTime[i] = getServiceTime(processes[i]);

    int time = 0, nextArrival = 0;

    while (time < last_instant)
    {
        // Push newly arrived processes into the queue
        while (nextArrival < process_count && getArrivalTime(processes[nextArrival]) == time)
        {
            readyQueue.push({remainingTime[nextArrival], nextArrival});
            ++nextArrival;
        }

        if (!readyQueue.empty())
        {
            auto [rem, pid] = readyQueue.top();
            readyQueue.pop();

            // Execute one unit of time
            timeline[time][pid] = '*';
            remainingTime[pid]--;

            if (remainingTime[pid] == 0)
            {
                int arrival = getArrivalTime(processes[pid]);
                int total = getServiceTime(processes[pid]);
                finishTime[pid] = time + 1;
                turnAroundTime[pid] = finishTime[pid] - arrival;
                normTurn[pid] = static_cast<float>(turnAroundTime[pid]) / total;
                isCompleted[pid] = true;
            }
            else
            {
                // Re-push with updated remaining time
                readyQueue.push({remainingTime[pid], pid});
            }
        }

        ++time;
    }

    if (operation == "stats")
        fillInWaitTime();
}

#endif // SRT_H_INCLUDED
