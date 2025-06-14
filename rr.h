#ifndef RR_H_INCLUDED
#define RR_H_INCLUDED

// Round Robin Scheduling Implementation
void roundRobin(int quantum)
{
    queue<pair<int, int>> q; // (processIndex, remainingTime)
    vector<int> remainingTime(process_count);
    int j = 0, time = 0;

    // Initialize first arriving processes
    while (j < process_count && getArrivalTime(processes[j]) <= time)
    {
        remainingTime[j] = getServiceTime(processes[j]);
        q.push({j, remainingTime[j]});
        ++j;
    }

    while (time < last_instant)
    {
        if (!q.empty())
        {
            auto [index, rem] = q.front();
            q.pop();

            int arrival = getArrivalTime(processes[index]);
            int service = getServiceTime(processes[index]);

            int executed = 0;
            while (executed < quantum && remainingTime[index] > 0 && time < last_instant)
            {
                timeline[time][index] = '*';
                --remainingTime[index];
                ++executed;
                ++time;

                // Add newly arrived processes during this quantum
                while (j < process_count && getArrivalTime(processes[j]) <= time)
                {
                    remainingTime[j] = getServiceTime(processes[j]);
                    q.push({j, remainingTime[j]});
                    ++j;
                }
            }

            if (remainingTime[index] > 0)
                q.push({index, remainingTime[index]});
            else
            {
                finishTime[index] = time;
                turnAroundTime[index] = finishTime[index] - arrival;
                normTurn[index] = turnAroundTime[index] * 1.0f / service;
            }
        }
        else
        {
            // CPU idle
            ++time;

            // Add newly arrived processes during idle time
            while (j < process_count && getArrivalTime(processes[j]) <= time)
            {
                remainingTime[j] = getServiceTime(processes[j]);
                q.push({j, remainingTime[j]});
                ++j;
            }
        }
    }

    // fillInWaitTime(); // Optional: call externally if needed
}

#endif // RR_H_INCLUDED
