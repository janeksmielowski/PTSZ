#include <iostream>
#include <fstream>
#include <cstdlib>

#include "settings.h"

using namespace std;

int main(int argc, char** argv) {

    // TODO: implement me
    for (int i = 0; i < INSTANCES; ++i) {
        string filename = "out_136815_" + to_string(INSTANCE_SIZES[i]) + ".txt";
        ofstream outfile(filename);

        outfile << 0 << endl;

        for (int j = 1; j < INSTANCE_SIZES[i]; ++j) {
            outfile << j << " ";
        }

        outfile << INSTANCE_SIZES[i] << endl;

        outfile.close();
    }

    return EXIT_SUCCESS;
}