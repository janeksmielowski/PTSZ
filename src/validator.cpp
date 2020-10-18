#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "settings.h"

using namespace std;

struct Task {
    int processingTime;
    int readinessTime;
    int deadlineTime;
    int weight;
};

void testInstances(string index) {
    for (int i = 0; i < INSTANCES; ++i) {

        string filename = "in_" + index + "_" + to_string(INSTANCE_SIZES[i]) + ".txt";
        ifstream infile(filename);
        int size;
        bool valid = true;

        infile >> size;

        for (int j = 0; j < size; ++j) {
            
            int processingTime, readinessTime, deadlineTime, weight;
            infile >> processingTime >> readinessTime >> deadlineTime >> weight;

            if (processingTime < 0 || readinessTime < 0 || deadlineTime < 0 || weight < 0
                || readinessTime > deadlineTime
            ) {
                valid = false;
            }
        }

        infile.close();

        cout << INSTANCE_SIZES[i] << ": " << (valid ? "valid" : "invalid") << endl;
    }
}

void testSchedules(string index) {
    vector<Task> instance;

    for (int i = 0; i < INSTANCES; ++i) {

        string filename = "in_" + index + "_" + to_string(INSTANCE_SIZES[i]) + ".txt";
        ifstream infile(filename);
        int size;

        infile >> size;

        for (int j = 0; j < size; ++j) {
            Task task;
            infile >> task.processingTime >> task.readinessTime >> task.deadlineTime >> task.weight;
            instance.push_back(task);
        }

        infile.close();
    }

    for (int i = 0; i < INSTANCES; ++i) {

        string filename = "out_" + index + "_" + to_string(INSTANCE_SIZES[i]) + ".txt";
        ifstream infile(filename);
        
        int presumedCriterion;
        int currentTime = 0;
        int criterion = 0;

        infile >> presumedCriterion;

        for (int j = 0; j < INSTANCE_SIZES[i]; ++j) {
            int taskNumber;
            infile >> taskNumber;
            Task task = instance[taskNumber - 1];

            if (currentTime < task.readinessTime) {
                currentTime = task.readinessTime;
            }

            currentTime += task.processingTime;
            if (currentTime > task.deadlineTime) {
                criterion += task.weight;
            }
        }

        cout << INSTANCE_SIZES[i] << ": " << criterion << " " << (presumedCriterion == criterion ? "valid" : "invalid") << endl;

        infile.close();
    }
}

int main(int argc, char** argv) {

    if (argc != 3) {
        cout << "Please provide required args: mode ('instance' or 'schedule'), index" << endl;
        return EXIT_FAILURE;
    }

    string mode = argv[1];
    string index = argv[2];

    if (mode == "instance") {
        testInstances(index);
    }
    
    else if (mode == "schedule") {
        testSchedules(index);
    }

    else {
        cout << "Invalid args: modes are 'instance' or 'schedule'" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}