#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>

#include "settings.h"

using namespace std;

int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "Please provide required args: index" << endl;
        return EXIT_FAILURE;
    }

    string index = argv[1];

    string path = ".\\out";
    CreateDirectoryA(path.c_str(), NULL);

    // TODO: implement me
    for (int i = 0; i < INSTANCES; ++i) {
        string filename = ".\\out\\out_" + index + "_" + to_string(INSTANCE_SIZES[i]) + ".txt";
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