#include "settings.h"

using namespace std;

vector<Task> readInstance(ifstream &infile, int instanceSize) {
    vector<Task> instance;

    for (int i = 0; i < instanceSize; ++i) {
        Task task;
        task.number = i + 1;
        infile >> task.duration[0] >> task.duration[1] >> task.duration[2] >> task.deadline >> task.weight;
        instance.push_back(task);
    }

    return instance;
}

bool sortFn(Task left, Task right) {
    int leftWeight = left.weight == 0 ? 1 : left.weight;
    int rightWeight = right.weight == 0 ? 1 : right.weight;
    return (float)left.deadline / (float)leftWeight < (float)right.deadline / (float)rightWeight;
}

float evalCriterion(vector<Task> instance, vector<Task> schedule) {
    float criterion = 0, weightSum = 0;
    vector<Machine> machines(MACHINES);

    for (int i = 0; i < schedule.size(); ++i) {
        int taskNumber = schedule[i].number - 1;
        
        for (int m = 0; m < MACHINES; ++m) {
            if (m > 0) {
                machines[m].time = max(machines[m].time, machines[m - 1].time);
            }
            machines[m].time += instance[taskNumber].duration[m];
        }

        criterion += instance[taskNumber].weight * max(0, machines[MACHINES - 1].time - instance[i].deadline);
        weightSum += instance[taskNumber].weight;
    }

    return (float) criterion / (float) weightSum;
};

void schedule(string infilePath, string outfilePath) {
    ifstream infile(infilePath);

    int size;
    infile >> size;

    int taskAssignment = size / MACHINES;
    vector<Task> instance = readInstance(infile, size);
    vector<Task> schedule = instance;

    infile.close();

    sort(schedule.begin(), schedule.end(), sortFn);
    float criterion = evalCriterion(instance, schedule);

    ofstream outfile(outfilePath);
    outfile << fixed << setprecision(2) << criterion << endl;
    for (int i = 0; i < size - 1; ++i) {
        outfile << schedule[i].number << " ";
    }
    outfile << schedule[size - 1].number << endl;

    outfile.close();
}

int main(int argc, char** argv) {
    srand(time(NULL));
    rand();

    if (argc != 2) {
        cout << "Please provide required args: path to input file" << endl;
        return EXIT_FAILURE;
    }

    string inputPath = argv[1];
    string outputPath = inputPath;

    int pathnameLastIndex = inputPath.find_last_of("/\\");
    outputPath.replace(pathnameLastIndex + 1, 2, "out");

    schedule(inputPath, outputPath);

    return EXIT_SUCCESS;
}