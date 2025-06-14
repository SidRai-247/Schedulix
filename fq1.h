#ifndef FQ1_H_INCLUDED
#define FQ1_H_INCLUDED

// Feedback Queue Scheduling (Single Queue Approximation)
// Lower priority number indicates higher priority
void feedbackQ1()
{
    // Min-heap based on priority level (priority, process index)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    // Tracks remaining service time for each process
    unordered_map<int, int> remainingServiceTime;

    int j = 0;

    // Push the first process if it arrives at time 0
    while (j < process_count && getArrivalTime(processes[j]) == 0)
    {
        pq.emplace(0, j);
        remainingServiceTime[j] = getServiceTime(processes[j]);
        j++;
    }

    for (int time = 0; time < last_instant; ++time)
    {
        if (!pq.empty())
        {
            auto [priorityLevel, processIndex] = pq.top();
            pq.pop();

            int arrival = getArrivalTime(processes[processIndex]);
            int service = getServiceTime(processes[processIndex]);

            // Check if new processes arrive at current time + 1
            while (j < process_count && getArrivalTime(processes[j]) == time + 1)
            {
                pq.emplace(0, j);
                remainingServiceTime[j] = getServiceTime(processes[j]);
                j++;
            }

            // Execute current process for one unit of time
            remainingServiceTime[processIndex]--;
            if (time < last_instant)
                timeline[time][processIndex] = '*';

            if (remainingServiceTime[processIndex] == 0)
            {
                finishTime[processIndex] = time + 1;
                turnAroundTime[processIndex] = finishTime[processIndex] - arrival;
                normTurn[processIndex] = turnAroundTime[processIndex] * 1.0 / service;
            }
            else
            {
                // Re-insert the process with updated priority
                if (pq.size() >= 1)
                    pq.emplace(priorityLevel + 1, processIndex);
                else
                    pq.emplace(priorityLevel, processIndex);
            }
        }

        // Add any arriving processes that came exactly at time+1 (missed earlier)
        while (j < process_count && getArrivalTime(processes[j]) == time + 1)
        {
            pq.emplace(0, j);
            remainingServiceTime[j] = getServiceTime(processes[j]);
            j++;
        }
    }

    // fillInWaitTime(); // Leave this commented if handled externally
}

#endif // FQ1_H_INCLUDED
