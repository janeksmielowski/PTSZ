#include "settings.h"

using namespace std;

vector<Task> generateInstance(int instanceSize) {
    vector<Task> instance;
    
    for (int i = 0; i < instanceSize; ++i) {
        Task task;
        int sumDuration = 0;
        for (int m = 0; m < MACHINES; ++m) {
            task.duration[m] = rand() % GEN_TASK_MAX_DURATION + 1;
            sumDuration += task.duration[m];
        }
        task.number = i + 1;
        task.deadline = sumDuration + rand() % GEN_TASK_MAX_TOLERANCE;
        task.weight = rand() % GEN_TASK_MAX_WEIGHT;
        instance.push_back(task);
    }

    return instance;
}

void generate(int instanceSize, string path) {
    string filePath = path + "_" + to_string(instanceSize) + ".txt";
    ofstream outfile(filePath);

    vector<Task> instance = generateInstance(instanceSize);

    outfile << instanceSize << endl;

    for (int i = 0; i < instanceSize; ++i) {
        for (int m = 0; m < MACHINES; ++m) {
            outfile << instance[i].duration[m] << " ";
        }
        outfile << instance[i].deadline << " " << instance[i].weight << endl;
    }

    outfile.close();
}

int main() {
    srand(time(NULL));
    rand();

    const string PATH = INSTANCES_PATH + INDEX_INPATH;

    CreateDirectoryA(INSTANCES_PATH.c_str(), NULL);
    CreateDirectoryA(PATH.c_str(), NULL);

    for (int i = 0; i < INSTANCES; ++i) {
        generate(INSTANCE_SIZES[i], PATH + INDEX_INPATH);
    }

    return EXIT_SUCCESS;
}