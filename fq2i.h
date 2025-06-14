#ifndef FQ2I_H
#define FQ2I_H

void feedbackQ2i()
{
    // Min-heap priority queue: (priority level, process index)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    unordered_map<int, int> remainingTime;

    int j = 0;
    // Add initial processes (arrival time 0)
    while (j < process_count && getArrivalTime(processes[j]) == 0)
    {
        pq.emplace(0, j);
        remainingTime[j] = getServiceTime(processes[j]);
        ++j;
    }

    for (int time = 0; time < last_instant; ++time)
    {
        if (!pq.empty())
        {
            auto [priority, index] = pq.top();
            pq.pop();

            int arrival = getArrivalTime(processes[index]);
            int service = getServiceTime(processes[index]);

            // Add new arrivals before processing
            while (j < process_count && getArrivalTime(processes[j]) <= time + 1)
            {
                pq.emplace(0, j);
                remainingTime[j] = getServiceTime(processes[j]);
                ++j;
            }

            int quantum = pow(2, priority);
            int current = time;

            // Execute process for up to 2^priority units or until completion
            while (quantum-- && remainingTime[index])
            {
                if(current < last_instant) timeline[current++][index] = '*';
                --remainingTime[index];
            }

            if (remainingTime[index] == 0)
            {
                finishTime[index] = current;
                turnAroundTime[index] = finishTime[index] - arrival;
                normTurn[index] = turnAroundTime[index] * 1.0 / service;
            }
            else
            {
                // Increase priority level if others are waiting
                if (!pq.empty())
                    pq.emplace(priority + 1, index);
                else
                    pq.emplace(priority, index); // no starvation if it's the only process
            }

            time = current - 1; // adjust for outer loop increment
        }

        // Add any remaining processes arriving at this time
        while (j < process_count && getArrivalTime(processes[j]) <= time + 1)
        {
            pq.emplace(0, j);
            remainingTime[j] = getServiceTime(processes[j]);
            ++j;
        }
    }

    fillInWaitTime();
}

#endif // FQ2I_H
