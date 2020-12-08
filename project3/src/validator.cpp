#include "settings.h"

using namespace std;

vector<Task> readInstance(ifstream &infile, int instanceSize) {
    vector<Task> instance;

    for (int i = 0; i < instanceSize; ++i) {
        Task task;
        task.number = i;
        infile >> task.duration[0] >> task.duration[1] >> task.duration[2] >> task.deadline >> task.weight;
        instance.push_back(task);
    }

    return instance;
}

vector<int> readSchedule(ifstream &infile, int size) {
    vector<int> schedule;

    for (int i = 0; i < size; ++i) {
        int task;
        infile >> task;
        schedule.push_back(task);
    }

    return schedule;
}

void validate(int instanceSize, string inpath, string outpath) {
    string instancePath = inpath + "_" + to_string(instanceSize) + ".txt";
    string schedulePath = outpath + "_" + to_string(instanceSize) + ".txt";

    ifstream instanceFile(instancePath);
    int size;

    instanceFile >> size;
    vector<Task> instance = readInstance(instanceFile, size);

    instanceFile.close();

    ifstream scheduleFile(schedulePath);
    int presumedCriterion;

    scheduleFile >> presumedCriterion;
    vector<int> schedule = readSchedule(scheduleFile, size);

    scheduleFile.close();

    float criterion = 0, weightSum = 0;
    vector<Machine> machines(MACHINES);

    for (int i = 0; i < size; ++i) {
        int taskNumber = schedule[i] - 1;
        
        for (int m = 0; m < MACHINES; ++m) {
            if (m > 0) {
                machines[m].time = max(machines[m].time, machines[m - 1].time);
            }
            machines[m].time += instance[taskNumber].duration[m];
        }

        criterion += instance[i].weight * max(0, machines[MACHINES - 1].time - instance[i].deadline);
        weightSum += instance[i].weight;
    }

    criterion = (float) criterion / (float) weightSum;
    cout << instanceSize << ": " << fixed << setprecision(2) << criterion << " ";
    cout << (fabs(criterion - presumedCriterion) < 1 ? "valid" : "invalid") << endl;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    rand();

    if (argc != 2) {
        cout << "Please provide required args: index" << endl;
        return EXIT_FAILURE;
    }

    string index = argv[1];
    string INDEX_INPATH = "\\in_" + index;
    string INDEX_OUTPATH = "\\out_" + index;
    string INPATH = INSTANCES_PATH + INDEX_INPATH + INDEX_INPATH;
    string OUTPATH = INSTANCES_PATH + INDEX_INPATH + INDEX_OUTPATH;

    for (int i = 0; i < INSTANCES; ++i) {
        validate(INSTANCE_SIZES[i], INPATH, OUTPATH);
    }

    return EXIT_SUCCESS;
}