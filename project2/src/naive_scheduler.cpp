#include "settings.h"

using namespace std;

vector<float> readMachines(ifstream &infile) {
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

void schedule(int instanceSize) {
    string infilePath = PATH + INDEX_INPATH + "_" + to_string(instanceSize) + ".txt";
    string outfilePath = PATH + INDEX_OUTPATH + "_" + to_string(instanceSize) + ".txt";

    ifstream infile(infilePath);

    int size;
    infile >> size;

    int taskAssignment = size / MACHINES;
    vector<float> machines = readMachines(infile);
    vector<Task> instance = readInstance(infile, size);

    infile.close();

    ofstream outfile(outfilePath);

    outfile << 0 << endl;

    for (int m = 0; m < MACHINES; ++m) {
        for (int i = 0; i < taskAssignment - 1; ++i) {
            outfile << m * taskAssignment + i + 1 << " ";
        }
        outfile << (m + 1) * taskAssignment << endl;
    }

    outfile.close();
}

int main() {
    srand(time(NULL));
    rand();

    for (int i = 0; i < INSTANCES; ++i) {
        schedule(INSTANCE_SIZES[i]);
    }

    return EXIT_SUCCESS;
}