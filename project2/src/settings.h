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

const int INDEXES = 9;
const std::string INDEX_ARR[] = {"136812", "136815", "132639", "136814", "136807", "136798", "132321", "136808", "136691"};
// const std::string INDEX_ARR[] = {"136808"};

const int INSTANCES = 10;
const int INSTANCE_SIZES[] = { 50, 100, 150, 200, 250, 300, 350, 400, 450, 500 };
const int MACHINES = 5;

const std::string INSTANCES_PATH = ".\\instances";

const int GEN_MACHINE_PRECISION = 2;
const int GEN_MACHINE_FACTOR_RANGE = 5;
const int GEN_TASK_MAX_DURATION = 10;

struct Machine {
    int number;
    float factor;
    float time;
    float sumScheduleTime;
    std::vector<int> schedule;
};

struct Task {
    int number;
    int duration;
    int readiness;
};

#endif