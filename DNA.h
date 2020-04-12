//
// Created by vocheretnyi on 10.04.20.
//

#pragma once

#include <vector>

#include "Data.h"
#include "Schedule.h"

struct DNA {
    Schedule schedule;
    double fitness;
//    double likelihood;

    DNA() {
        fitness = 0.0f;
//        likelihood = 0.0;
    }

//    bool operator==(const DNA& other) {
//        return schedule == other.schedule;
//    }

    int calcFitness() const {
        // TODO:
    }
};

