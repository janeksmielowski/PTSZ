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

vector<Machine> makeMachines(vector<float> machineFactors) {
    vector<Machine> machines;

    for (int m = 0; m < MACHINES; ++m) {
        Machine machine;
        machine.number = m;
        machine.factor = machineFactors[m];
        machine.time = 0;
        machine.sumScheduleTime = 0;
        machines.push_back(machine);
    }

    return machines;
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

void updateReadyTasks(vector<Task> &readyTasks, vector<Task> instance, int &lastReadyTask, float time) {
    for (int i = lastReadyTask + 1; i < instance.size() && instance[i].readiness <= time; ++i) {
        readyTasks.push_back(instance[i]);
        ++lastReadyTask;
    };
}

bool machineNotReady(Machine machine, float time) {
    return machine.time > time + 1;
}

void updateMachine(Machine &machine, Task readyTask) {
    machine.schedule.push_back(readyTask.number);
    if (machine.time < readyTask.readiness) {
        machine.time = readyTask.readiness;
    }
    machine.time += readyTask.duration * machine.factor;
    machine.sumScheduleTime += (machine.time - readyTask.readiness);
}

float evaluateCriterion(vector<Machine> machines, int instanceSize) {
    float criterion = 0;
    for (int m = 0; m < MACHINES; ++m) {
        criterion += machines[m].sumScheduleTime;
    }
    return (float) criterion / (float) instanceSize;
}

void writeMachines(ofstream &outfile, vector<Machine> machines) {
    for (int m = 0; m < MACHINES; ++m) {
        for (int i = 0; i < machines[m].schedule.size() - 1; ++i) {
            outfile << machines[m].schedule[i] << " ";
        }
        outfile << machines[m].schedule[machines[m].schedule.size() - 1] << endl;
    }
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

    vector<Machine> machines = makeMachines(machineFactors);

    sort(machines.begin(), machines.end(), machineFactorCompareFn);
    sort(instance.begin(), instance.end(), instanceCompareFn);

    int lastReadyTask = -1;
    bool shouldSchedule = true;
    float time = 0;
    vector<Task> readyTasks;

    while (shouldSchedule) {
        updateReadyTasks(readyTasks, instance, lastReadyTask, time);

        for (int m = 0; m < MACHINES; ++m) {
            if (machineNotReady(machines[m], time) || readyTasks.size() == 0) {
                continue;
            }

            updateMachine(machines[m], readyTasks[0]);
            readyTasks.erase(readyTasks.begin());
        }

        shouldSchedule = lastReadyTask < instanceSize - 1 || readyTasks.size() > 0;
        ++time;
    }

    float criterion = evaluateCriterion(machines, instanceSize);
    sort(machines.begin(), machines.end(), machineNumberCompareFn);

    ofstream outfile(outfilePath);
    outfile << fixed << setprecision(2) << criterion << endl;
    writeMachines(outfile, machines);
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