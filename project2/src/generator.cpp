#include "settings.h"

using namespace std;

float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void generate(string path, int instanceSize) {
    string filePath = path + "\\in_136815_" + to_string(instanceSize) + ".txt";
    ofstream outfile(filePath);

    outfile << instanceSize << endl;

    for (int m = 0; m < 5; ++m) {
        float machineSpeedFactor = randomFloat(1, GEN_MACHINE_RANGE);
        outfile << fixed << setprecision(GEN_MACHINE_PRECISION) << machineSpeedFactor;
        if (m < 4) {
            outfile << " ";
        }
    }

    outfile << endl;

    for (int i = 0; i < instanceSize; ++i) {
        int taskDuration = rand() % GEN_TASK_MAX_DURATION + 1;
        int taskReadiness = rand() % instanceSize;
        outfile << taskDuration << " " << taskReadiness << endl;
    }

    outfile.close();
}

int main() {
    srand(time(NULL));
    rand();

    const string INSTANCES_PATH = ".\\instances";
    const string INDEX_PATH = "\\in136815";
    const string PATH = INSTANCES_PATH + INDEX_PATH;
    CreateDirectoryA(INSTANCES_PATH.c_str(), NULL);
    CreateDirectoryA(PATH.c_str(), NULL);

    for (int i = 0; i < INSTANCES; ++i) {
        generate(PATH, INSTANCE_SIZES[i]);
    }

    return EXIT_SUCCESS;
}