#ifndef FCFS_H
#define FCFS_H

void firstComeFirstServe()
{
    int currentTime = getArrivalTime(processes[0]);

    for (int i = 0; i < process_count; ++i)
    {
        int processIndex = i;
        int arrivalTime = getArrivalTime(processes[processIndex]);
        int serviceTime = getServiceTime(processes[processIndex]);

        // Process starts at max of current time or its arrival
        currentTime = std::max(currentTime, arrivalTime);

        finishTime[processIndex] = currentTime + serviceTime;
        turnAroundTime[processIndex] = finishTime[processIndex] - arrivalTime;
        normTurn[processIndex] = turnAroundTime[processIndex] * 1.0f / serviceTime;

        // Fill execution time '*'
        for (int t = currentTime; t < finishTime[processIndex] && t < last_instant; ++t)
            timeline[t][processIndex] = '*';

        // Fill waiting time '.'
        for (int t = arrivalTime; t < currentTime && t < last_instant; ++t)
            timeline[t][processIndex] = '.';

        currentTime += serviceTime;
    }
}

#endif // FCFS_H
