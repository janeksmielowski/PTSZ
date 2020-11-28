#include "settings.h"

using namespace std;

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

void validate(string index) {
    vector<int> times;

    cout << index << endl;
    for (int i = 0; i < INSTANCES; ++i) {
        int instanceSize = INSTANCE_SIZES[i];
        string instancePath = ".\\instances\\in_136815\\out_136815_" + to_string(instanceSize) + ".txt";
        string inputCmd = ".\\al_" + index + ".exe .\\\\instances\\\\in_136815\\\\in_136815_" + to_string(INSTANCE_SIZES[i]) + ".txt";

        remove(instancePath.c_str());

        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        TimeGuard guard = TimeGuard();

        CreateProcess(NULL, (LPSTR) inputCmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        WaitForSingleObject(pi.hProcess, INFINITE);

        times.push_back(guard.stop());
    }

    for (int i = 0; i < INSTANCES; ++i) {
        int instanceSize = INSTANCE_SIZES[i];
        string instancePath = ".\\instances\\in_136815\\in_136815_" + to_string(instanceSize) + ".txt";
        string schedulePath = ".\\instances\\in_136815\\out_136815_" + to_string(instanceSize) + ".txt";

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
        cout << fixed << setprecision(2) << criterion << " ";
        cout << times[i] << " ";
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    rand();

    for (int idx = 0; idx < INDEXES; ++idx) {
        validate(INDEX_ARR[idx]);
    }

    return EXIT_SUCCESS;
}