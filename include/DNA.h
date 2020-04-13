//
// Created by vocheretnyi on 10.04.20.
//

#pragma once

#include <vector>

#include "DataStorage.h"
#include "Schedule.h"

struct DNA {
    Schedule schedule;
    double fitness;

    DNA() {
        fitness = 0.0f;
    }

    double calcFitness() {
        int numOfConflicts = 0;

        for (auto&[group1, schedulePerGroup] : schedule.schedule) {
            for (auto&[group2, schedulePerGroup] : schedule.schedule) {
                if (group1 == group2 || group1 < group2) {
                    continue;
                }

                for (auto&[day, listOfClasses] : schedulePerGroup) {
                    for (int i = 0; i < listOfClasses.size(); ++i) {
                        if (schedule.schedule[group1][day][i].room == schedule.schedule[group2][day][i].room) {
                            numOfConflicts++;
                        }
                        if (schedule.schedule[group1][day][i].teacher == schedule.schedule[group2][day][i].teacher) {
                            numOfConflicts++;
                        }
                    }
                }
            }
        }

        if (numOfConflicts == 0) {
            fitness = -1.0;
        } else {
            fitness = 1.0 / numOfConflicts;
        }
        return fitness;
    }
};

