#pragma once

#include <vector>
#include <map>

#include "Classes.h"
#include "DataStorage.h"
#include "RandomHelper.h"

using namespace std;

struct Schedule {
    using Schedule_Per_Group = map<Day, vector<Class>>;
    map<Group, Schedule_Per_Group> schedule;

    static Schedule GenerateRandomSchedule(const DataStorage& data) {
        Schedule scheduleObj;
        map<Group, Schedule_Per_Group>& schedule = scheduleObj.schedule;

        for (const Group& group : data.groups) {
            for (const Day& day : data.days) {
                for (int lessonNum = 0; lessonNum < data.LESSONS_PER_DAY; ++lessonNum) {
                    const Subject& subject = GetRandom(group.subjects);
                    const Teacher& teacher = GetRandom(subject.teachers);
                    const Room& room = GetRandomRoom(data.rooms, group.size);
                    schedule[group][day].push_back(Class(group, subject, room, teacher, Time(day, lessonNum)));
                }
            }
        }

        return scheduleObj;
    }

    static const Room& GetRandomRoom(const vector<Room>& rooms, size_t group_size) {
        vector<Room> filteredRooms;
        copy_if(rooms.begin(), rooms.end(), back_inserter(filteredRooms), [group_size](const Room& room) {
            return room.capacity >= group_size;
        });
        return GetRandom(rooms);
    }
};