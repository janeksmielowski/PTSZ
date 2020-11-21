#include "settings.h"

using namespace std;

float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

vector<Task> generateInstance(int instanceSize) {
    vector<Task> instance;
    
    for (int i = 0; i < instanceSize; ++i) {
        Task task;
        task.duration = rand() % GEN_TASK_MAX_DURATION + 1;
        task.readiness = rand() % instanceSize;
        instance.push_back(task);
    }

    return instance;
}

vector<float> generateMachines() {
    vector<float> machines;

    for (int m = 0; m < MACHINES - 1; ++m) {
        machines.push_back(randomFloat(1, GEN_MACHINE_FACTOR_RANGE));
    }

    machines.push_back(1.f);
    random_shuffle(machines.begin(), machines.end());

    return machines;
}

void generate(int instanceSize, string path) {
    string filePath = path + "_" + to_string(instanceSize) + ".txt";
    ofstream outfile(filePath);

    vector<float> machines = generateMachines();
    vector<Task> instance = generateInstance(instanceSize);

    outfile << instanceSize << endl;

    for (int m = 0; m < MACHINES - 1; ++m) {
        outfile << fixed << setprecision(GEN_MACHINE_PRECISION) << machines[m] << " ";
    }

    outfile << fixed << setprecision(GEN_MACHINE_PRECISION) << machines[MACHINES - 1] << endl;

    for (int i = 0; i < instanceSize; ++i) {
        outfile << instance[i].duration << " " << instance[i].readiness << endl;
    }

    outfile.close();
}

int main() {
    srand(time(NULL));
    rand();

    const string INDEX_INPATH = "\\in_136815";
    const string PATH = INSTANCES_PATH + INDEX_INPATH;

    CreateDirectoryA(INSTANCES_PATH.c_str(), NULL);
    CreateDirectoryA(PATH.c_str(), NULL);

    for (int i = 0; i < INSTANCES; ++i) {
        generate(INSTANCE_SIZES[i], PATH + INDEX_INPATH);
    }

    return EXIT_SUCCESS;
}