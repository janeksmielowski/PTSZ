#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#include "settings.h"

using namespace std;

int main(int argc, char** argv) {

    srand(time(NULL));
    rand();

    string path = ".\\instances\\in_136815";
    CreateDirectoryA(path.c_str(), NULL);

    for (int i = 0; i < INSTANCES; ++i) {
        string filename = path + "\\in_136815_" + to_string(INSTANCE_SIZES[i]) + ".txt";
        ofstream outfile(filename);

        outfile << INSTANCE_SIZES[i] << endl;

        for (int j = 0; j < INSTANCE_SIZES[i]; ++j) {
            unsigned int processingTime = rand() % MAX_PROCESSING_TIME + 1;
            unsigned int readinessTime = rand() % INSTANCE_SIZES[i] + 1;
            unsigned int deadlineTime = rand() % (MAX_OVERDUE_TIME) + processingTime + readinessTime + 1;
            unsigned int weight = rand() % MAX_WEIGHT + 1;

            outfile << processingTime << " " << readinessTime << " " << deadlineTime << " " << weight << endl;
        }

        outfile.close();
    }

    return EXIT_SUCCESS;
}