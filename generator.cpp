#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const unsigned int INSTANCES = 2;
const unsigned int INSTANCE_SIZES[] = {4, 10};

const string SPACE = " ";

int main(int argc, char** argv) {

    if (argc != 5) {
        cout << "Please provide required args: max processing time, max readiness time, max deadline time, max weight" << endl;
        return EXIT_FAILURE;
    }

    unsigned int maxProcessingTime = stoi(argv[1]);
    unsigned int maxReadinessTime = stoi(argv[2]);
    unsigned int maxDeadlineTime = stoi(argv[3]);
    unsigned int maxWeight = stoi(argv[4]);

    if (maxProcessingTime > 0 && maxReadinessTime > 0 && maxDeadlineTime > 0 && maxWeight > 0
        && maxReadinessTime + maxProcessingTime > maxDeadlineTime
    ) {
        cout << "Invalid args: all values must be positive and tasks must be accomplishable before max deadline time" << endl;
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    rand();

    for (int i = 0; i < INSTANCES; ++i) {
        string filename = "in_136815_" + to_string(INSTANCE_SIZES[i]) + ".txt";
        ofstream outfile(filename);

        outfile << INSTANCE_SIZES[i] << endl;

        for (int j = 0; j < INSTANCE_SIZES[i]; ++j) {
            unsigned int processingTime = rand() % maxProcessingTime + 1;
            unsigned int readinessTime = rand() % maxReadinessTime + 1;
            unsigned int deadlineTime = rand() % (maxDeadlineTime - readinessTime) + readinessTime + 1;
            unsigned int weight = rand() % maxWeight + 1;

            outfile << processingTime << SPACE << readinessTime << SPACE << deadlineTime << SPACE << weight << endl;
        }

        outfile.close();
    }

    return EXIT_SUCCESS;
}