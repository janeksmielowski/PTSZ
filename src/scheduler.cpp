#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
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
        cout << "Please provide required args: index" << endl;
        return EXIT_FAILURE;
    }

    string index = argv[1];
    vector<vector<Task>> instances(10);

    for (int i = 0; i < INSTANCES; ++i) {
        vector<Task> instance;

        string filename = ".\\instances\\in_" + index + "\\in_" + index + "_" + to_string(INSTANCE_SIZES[i]) + ".txt";
        ifstream infile(filename);
        int size;

        infile >> size;

        for (int j = 0; j < size; ++j) {
            Task task;
            task.number = j + 1;
            infile >> task.processingTime >> task.readinessTime >> task.deadlineTime >> task.weight;
            instance.push_back(task);
        }

        infile.close();
        instances[i] = instance;
    }

    string path = ".\\out";
    CreateDirectoryA(path.c_str(), NULL);

    for (int i = 0; i < INSTANCES; ++i) {
        int globalTime = 0, globalCriterion = 0;

        for (int j = 0; j < INSTANCE_SIZES[i]; ++j) {
            int time = globalTime, criterion = globalCriterion;

            for (int k = j + 1; k < INSTANCE_SIZES[i]; ++k) {
                Task left = instances[i][j], right = instances[i][k];

                TimeWeight beforeSwap = getTimeWeights(time, left, right);
                TimeWeight afterSwap = getTimeWeights(time, right, left);

                if (afterSwap < beforeSwap) {
                    swap(instances[i][j], instances[i][k]);
                }
            }

            Task firstTask = instances[i][j];
            TimeWeight globals = getTimeWeight(globalTime, firstTask);
            globalTime = globals.time;
            globalCriterion += globals.weight;
        }

        cout << INSTANCE_SIZES[i] << ": t=" << globalTime << ", c=" << globalCriterion << endl;

        string filename = ".\\out\\out_" + index + "_" + to_string(INSTANCE_SIZES[i]) + ".txt";
        ofstream outfile(filename);

        outfile << globalCriterion << endl;

        for (int j = 0; j < INSTANCE_SIZES[i] - 1; ++j) {
            outfile << instances[i][j].number << " ";
        }

        outfile << instances[i][INSTANCE_SIZES[i] - 1].number << endl;

        outfile.close();
    }

    return EXIT_SUCCESS;
}