#include "settings.h"

using namespace std;

vector<float> readMachineFactors(ifstream &infile) {
    vector<float> machines(MACHINES);

    for (int i = 0; i < 5; ++i) {
        infile >> machines[i];
    }

    return machines;
}

vector<Task> readInstance(ifstream &infile, int instanceSize) {
    vector<Task> instance;

    for (int i = 0; i < instanceSize; ++i) {
        Task task;
        infile >> task.duration >> task.readiness;
        instance.push_back(task);
    }

    return instance;
}

vector<Machine> readMachineSchedules(ifstream &infile) {
    vector<Machine> machines(5);

    for (int m = 0; m < MACHINES; ++m) {
        int taskNumber;
        string line;
        getline(infile, line);
        istringstream lineStream(line);
        while(lineStream >> taskNumber) {
            machines[m].schedule.push_back(taskNumber);
        }
    }

    return machines;
}

void validate(int instanceSize, string inpath, string outpath) {
    string instancePath = inpath + "_" + to_string(instanceSize) + ".txt";
    string schedulePath = outpath + "_" + to_string(instanceSize) + ".txt";

    ifstream instanceFile(instancePath);

    int size;
    instanceFile >> size;

    vector<float> machineFactors = readMachineFactors(instanceFile);
    vector<Task> instance = readInstance(instanceFile, size);

    instanceFile.close();

    ifstream scheduleFile(schedulePath);

    int presumedCriterion;
    string line;

    getline(scheduleFile, line);
    istringstream lineStream(line);
    lineStream >> presumedCriterion;

    vector<Machine> machines = readMachineSchedules(scheduleFile);

    for (int m = 0; m < MACHINES; ++m) {
        machines[m].factor = machineFactors[m];
        machines[m].time = 0;
    }

    scheduleFile.close();

    float criterion = 0;

    for (int m = 0; m < MACHINES; ++m) {
        for (int s = 0; s < machines[m].schedule.size(); ++s) {
            int taskNumber = machines[m].schedule[s];
            Task task = instance[taskNumber - 1];
            if (machines[m].time < task.readiness) {
                machines[m].time = task.readiness;
            }
            machines[m].time += task.duration * machines[m].factor;
            criterion += (machines[m].time - task.readiness);
        }
    }

    criterion = (float) criterion / (float) instanceSize;
    cout << instanceSize << ": " << fixed << setprecision(2) << criterion << " ";
    cout << (criterion == presumedCriterion ? "valid" : "invalid") << endl;
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