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

void schedule(int instanceSize, string inpath, string outpath) {
    string infilePath = inpath + "_" + to_string(instanceSize) + ".txt";
    string outfilePath = outpath + "_" + to_string(instanceSize) + ".txt";

    ifstream infile(infilePath);

    int size;
    infile >> size;

    int taskAssignment = size / MACHINES;
    vector<Task> instance = readInstance(infile, size);

    infile.close();

    ofstream outfile(outfilePath);
    outfile << 0 << endl;
    for (int i = 1; i < size; ++i) {
        outfile << i << " ";
    }
    outfile << size << endl;

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