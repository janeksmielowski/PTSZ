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
        task.number = i + 1;
        infile >> task.duration >> task.readiness;
        instance.push_back(task);
    }

    return instance;
}

bool instanceCompareFn(Task left, Task right) {
    return left.readiness == right.readiness
        ? left.duration < right.duration
        : left.readiness < right.readiness;
}

bool machineFactorCompareFn(Machine left, Machine right) {
    return left.factor < right.factor;
}

bool machineNumberCompareFn(Machine left, Machine right) {
    return left.number < right.number;
}

void schedule(int instanceSize, string inpath, string outpath) {
    string infilePath = inpath + "_" + to_string(instanceSize) + ".txt";
    string outfilePath = outpath + "_" + to_string(instanceSize) + ".txt";

    ifstream infile(infilePath);

    int size;
    infile >> size;

    int taskAssignment = size / MACHINES;
    vector<float> machineFactors = readMachineFactors(infile);
    vector<Task> instance = readInstance(infile, size);

    infile.close();

    vector<Machine> machines;

    for (int m = 0; m < MACHINES; ++m) {
        Machine machine;
        machine.number = m;
        machine.factor = machineFactors[m];
        machine.time = 0;
        machines.push_back(machine);
    }

    sort(machines.begin(), machines.end(), machineFactorCompareFn);
    sort(instance.begin(), instance.end(), instanceCompareFn);

    int lastReadyTask = -1;
    float time = 0;
    vector<Task> readyTasks;

    while (lastReadyTask < instanceSize - 1 || readyTasks.size() > 0) {

        for (int i = lastReadyTask + 1; i < instance.size() && instance[i].readiness <= time; ++i) {
            readyTasks.push_back(instance[i]);
            ++lastReadyTask;
        }

        int min = -1;
        // szereguj
        for (int m = 0; m < MACHINES; ++m) {
            if (machines[m].time > time + 1) {
                continue;
            }

            if (readyTasks.size() == 0) {
                continue;
            }

            int taskPickIndex = 0;
            machines[m].schedule.push_back(readyTasks[taskPickIndex].number);

            if (machines[m].time < readyTasks[taskPickIndex].readiness) {
                machines[m].time = readyTasks[taskPickIndex].readiness;
            }

            machines[m].time += readyTasks[taskPickIndex].duration * machines[m].factor;
            machines[m].sumScheduleTime += (machines[m].time - readyTasks[taskPickIndex].readiness);

            readyTasks.erase(readyTasks.begin() + taskPickIndex);

            if (m == 0) {
                min = machines[m].time;
            } else {
                if (machines[m].time < min) {
                    min = machines[m].time;
                }
            }
        }

        if (min == -1) {
            time = floor(time + 1);
        } else {
            time = min;
        }
    }

    sort(machines.begin(), machines.end(), machineNumberCompareFn);

    float criterion = 0;
    for (int m = 0; m < MACHINES; ++m) {
        criterion += machines[m].sumScheduleTime;
    }

    ofstream outfile(outfilePath);

    criterion /= (float) instanceSize;
    outfile << fixed << setprecision(2) << criterion << endl;

    for (int m = 0; m < MACHINES; ++m) {
        for (int i = 0; i < machines[m].schedule.size() - 1; ++i) {
            outfile << machines[m].schedule[i] << " ";
        }
        outfile << machines[m].schedule[machines[m].schedule.size() - 1] << endl;
    }

    outfile.close();
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
        schedule(INSTANCE_SIZES[i], INPATH, OUTPATH);
    }

    return EXIT_SUCCESS;
}