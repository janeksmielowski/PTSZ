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

void schedule(string infilePath, string outfilePath) {
    cout << infilePath << " " << outfilePath << endl;
    ifstream infile(infilePath);

    int size;
    infile >> size;

    int taskAssignment = size / MACHINES;
    vector<Task> instance = readInstance(infile, size);

    infile.close();

    sort(instance.begin(), instance.end(), sortFn);

    ofstream outfile(outfilePath);
    outfile << 0 << endl;
    for (int i = 0; i < size - 1; ++i) {
        outfile << instance[i].number << " ";
    }
    outfile << instance[size - 1].number << endl;

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