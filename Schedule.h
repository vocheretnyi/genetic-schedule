#pragma once

#include <vector>

#include "Classes.h"
#include "Data.h"

using namespace std;

struct Schedule {
    using Schedule_Per_Day = vector<Class>;
    vector<Schedule_Per_Day> schedulePerDay;

    static Schedule GenerateRandomSchedule(const Data& data) {
        // TODO
    }

//    bool operator == (const Schedule& other) {
//        return schedulePerDay == other.schedulePerDay;
//    }
};