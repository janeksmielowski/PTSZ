#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>

#include "settings.h"

using namespace std;

struct Task {
    int number;
    int processingTime;
    int readinessTime;
    int deadlineTime;
    int weight;
};

class TimeWeight {
public:
    int time;
    int weight;
    
    bool operator< (TimeWeight right) {
        return this->weight < right.weight;
    }
};

class TimeGuard {
    clock_t timeMemory;
public:
    TimeGuard() {
        this->timeMemory = clock();
    }

    double stop() {
        return double(clock() - this->timeMemory);
    }
};

TimeWeight getTimeWeight(int time, Task task) {
    if (time < task.readinessTime) {
        time = task.readinessTime;
    }
    time += task.processingTime;
    int weight = time > task.deadlineTime ? task.weight : 0;
    return {time, weight};
}

TimeWeight getTimeWeights(int time, Task left, Task right) {
    TimeWeight leftTW = getTimeWeight(time, left);
    TimeWeight rightTW = getTimeWeight(leftTW.time, right);
    return {rightTW.time, leftTW.weight + rightTW.weight};
}

int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "Please provide required args: input path" << endl;
        return EXIT_FAILURE;
    }

    string inputPath = argv[1];
    string outputPath = inputPath;

    int pathnameLastIndex = inputPath.find_last_of("/\\");
    outputPath.replace(pathnameLastIndex + 1, 2, "out");

    // reading

    vector<Task> instance;

    ifstream infile(inputPath);
    int size;

    infile >> size;

    for (int j = 0; j < size; ++j) {
        Task task;
        task.number = j + 1;
        infile >> task.processingTime >> task.readinessTime >> task.deadlineTime >> task.weight;
        instance.push_back(task);
    }

    infile.close();

    // algorithm

    TimeGuard guard = TimeGuard();

    int globalTime = 0, globalCriterion = 0;

    for (int j = 0; j < size; ++j) {
        int time = globalTime, criterion = globalCriterion;

        for (int k = j + 1; k < size; ++k) {
            Task left = instance[j], right = instance[k];

            TimeWeight beforeSwap = getTimeWeights(time, left, right);
            TimeWeight afterSwap = getTimeWeights(time, right, left);

            if (afterSwap < beforeSwap) {
                swap(instance[j], instance[k]);
            }
        }

        Task firstTask = instance[j];
        TimeWeight globals = getTimeWeight(globalTime, firstTask);

        globalTime = globals.time;
        globalCriterion += globals.weight;
    }

    ofstream outfile(outputPath);

    outfile << globalCriterion << endl;

    for (int j = 0; j < size - 1; ++j) {
        outfile << instance[j].number << " ";
    }

    outfile << instance[size - 1].number << endl;

    outfile.close();

    int millis = guard.stop();
    cout << size << ": scheduleTime= " << globalTime << ", criterion= " << globalCriterion << ", processingTime= " << millis << "ms" << endl;

    return EXIT_SUCCESS;
}