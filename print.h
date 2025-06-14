#ifndef PRINT_H_INCLUDED
#define PRINT_H_INCLUDED
using namespace std;

// Function to print algorithm name
void printAlgorithm(int algorithm_index)
{
    cout << "\n";
    int algorithm_id = algorithms[algorithm_index].first - '0';
    if (algorithm_id == 2)
        cout << ALGORITHMS[algorithm_id] << algorithms[algorithm_index].second << endl;
    else
        cout << ALGORITHMS[algorithm_id] << endl;
}

void printProcesses()
{
    cout << "Process    ";
    for (int i = 0; i < process_count; i++)
        cout << "|  " << getProcessName(processes[i]) << "  ";
    cout << "|\n";
}
void printArrivalTime()
{
    cout << "Arrival    ";
    for (int i = 0; i < process_count; i++)
        printf("|%3d  ", getArrivalTime(processes[i]));
    cout << "|\n";
}
void printServiceTime()
{
    cout << "Service    |";
    for (int i = 0; i < process_count; i++)
        printf("%3d  |", getServiceTime(processes[i]));
    cout << " Mean|\n";
}
void printFinishTime()
{
    cout << "Finish     ";
    for (int i = 0; i < process_count; i++)
        printf("|%3d  ", finishTime[i]);
    cout << "|-----|\n";
}
void printTurnAroundTime()
{
    cout << "Turnaround |";
    int sum = 0;
    for (int i = 0; i < process_count; i++)
    {
        printf("%3d  |", turnAroundTime[i]);
        sum += turnAroundTime[i];
    }
    if ((1.0 * sum / turnAroundTime.size()) >= 10)
        printf("%2.2f|\n", (1.0 * sum / turnAroundTime.size()));
    else
        printf(" %2.2f|\n", (1.0 * sum / turnAroundTime.size()));
}

void printNormTurn()
{
    cout << "NormTurn   |";
    float sum = 0;
    for (int i = 0; i < process_count; i++)
    {
        if (normTurn[i] >= 10)
            printf("%2.2f|", normTurn[i]);
        else
            printf(" %2.2f|", normTurn[i]);
        sum += normTurn[i];
    }

    if ((1.0 * sum / normTurn.size()) >= 10)
        printf("%2.2f|\n", (1.0 * sum / normTurn.size()));
    else
        printf(" %2.2f|\n", (1.0 * sum / normTurn.size()));
}
void printStats(int algorithm_index)
{
    // cout << "\n";
    // cout << "\n";
    printAlgorithm(algorithm_index);
    printProcesses();
    printArrivalTime();
    printServiceTime();
    printFinishTime();
    printTurnAroundTime();
    printNormTurn();
}

void printTimeline(int algorithm_index)
{
    // cout << "\n";
    for (int i = 0; i <= last_instant; i++)
        cout << i % 10 << " ";
    cout << "\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < process_count; i++)
    {
        cout << getProcessName(processes[i]) << "     |";
        for (int j = 0; j < last_instant; j++)
        {
            cout << timeline[j][i] << "|";
        }
        cout << " \n";
    }
    cout << "------------------------------------------------\n";
}

#endif // PRINT_H_INCLUDED
