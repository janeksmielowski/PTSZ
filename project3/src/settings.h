#ifndef SETTINGS_H
#define SETTINGS_H

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

// const int INDEXES = 14;
// const std::string INDEX_ARR[] = {"136774", "136785", "136812", "136815", "132336", "136803", "132639", "136814", "136807", "136798", "132337", "132321", "136808", "136691"};

const int INDEXES = 1;
const std::string INDEX_ARR[] = {"136815"};

const int INSTANCES = 10;
const int INSTANCE_SIZES[] = { 50, 100, 150, 200, 250, 300, 350, 400, 450, 500 };
const int MACHINES = 3;

const std::string INDEX_INPATH = "\\in_136815";
const std::string INDEX_OUTPATH = "\\out_136815";
const std::string INSTANCES_PATH = ".\\instances";

const int GEN_TASK_MAX_DURATION = 10;
const int GEN_TASK_MAX_TOLERANCE = 10;
const int GEN_TASK_MAX_WEIGHT = 10;

struct Machine {
    int time = 0;
};

struct Task {
    int number;
    int duration[3];
    int deadline;
    int weight;
};

#endif