#ifndef SETTINGS_H
#define SETTINGS_H

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

const int INSTANCES = 10;
const int INSTANCE_SIZES[] = { 50, 100, 150, 200, 250, 300, 350, 400, 450, 500 };
const int MACHINES = 5;

const std::string INSTANCES_PATH = ".\\instances";
const std::string INDEX_INPATH = "\\in_136815";
const std::string INDEX_OUTPATH = "\\out_136815";
const std::string PATH = INSTANCES_PATH + INDEX_INPATH;

const int GEN_MACHINE_PRECISION = 2;
const int GEN_MACHINE_FACTOR_RANGE = 5;
const int GEN_TASK_MAX_DURATION = 100;

struct Machine {
    float factor;
    float time;
    std::vector<int> schedule;
};

struct Task {
    int duration;
    int readiness;
};

#endif