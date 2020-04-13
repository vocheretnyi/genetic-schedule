#pragma once

#include "Classes.h"

struct DataStorage {
    DataStorage(const vector<Group>& groups_,
                const vector<Subject>& subjects_,
                const vector<Room>& rooms_,
                const vector<Teacher>& teachers_,
                const vector<Day>& days_,
                size_t LESSONS_PER_DAY_) :
            groups(groups_),
            subjects(subjects_),
            rooms(rooms_),
            teachers(teachers_),
            days(days_),
            LESSONS_PER_DAY(LESSONS_PER_DAY_) {
    }

    const vector<Group>& groups;
    const vector<Subject>& subjects;
    const vector<Room>& rooms;
    const vector<Teacher>& teachers;
    const vector<Day>& days;
    size_t LESSONS_PER_DAY;
};