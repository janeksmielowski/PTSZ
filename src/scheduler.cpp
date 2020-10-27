#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "settings.h"

using namespace std;

struct Task {
    int number;
    int processingTime;
    int readinessTime;
    int deadlineTime;
    int weight;
};

int getWeights(int time, Task left, Task right) {
    if (time < left.readinessTime) {
        time = left.readinessTime;
    }
    time += left.processingTime;
    int t1Weight = time > left.deadlineTime ? left.weight : 0;
    if (time < right.readinessTime) {
        time = right.readinessTime;
    }
    time += right.processingTime;
    int t2Weight = time > right.deadlineTime ? right.weight : 0;
    return t1Weight + t2Weight;
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

        string filename = "in_" + index + "_" + to_string(INSTANCE_SIZES[i]) + ".txt";
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

    for (int i = 0; i < INSTANCES; ++i) {
        int globalTime = 0, globalCriterion = 0;

        for (int j = 0; j < INSTANCE_SIZES[i]; ++j) {
            int time = globalTime, criterion = globalCriterion;

            for (int k = j + 1; k < INSTANCE_SIZES[i]; ++k) {
                Task left = instances[i][j], right = instances[i][k];

                int beforeSwapWeight = getWeights(time, left, right);
                int afterSwapWeight = getWeights(time, right, left);

                if (afterSwapWeight < beforeSwapWeight) {
                    swap(instances[i][j], instances[i][k]);
                }
            }

            globalTime = (globalTime < instances[i][j].readinessTime ? instances[i][j].readinessTime : time) + instances[i][j].processingTime;
            globalCriterion += time > instances[i][j].deadlineTime ? instances[i][j].weight : 0;
        }

        cout << INSTANCE_SIZES[i] << ": t=" << globalTime << ", c=" << globalCriterion << endl;

        string filename = "out_" + index + "_" + to_string(INSTANCE_SIZES[i]) + ".txt";
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