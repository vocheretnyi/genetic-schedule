#pragma once

#include <string>
#include <utility>

using namespace std;

struct Room {
    int number;
    size_t capacity;

    explicit Room(int roomNumber, size_t roomCapacity) :
            number(roomNumber), capacity(roomCapacity) {}
};

struct Teacher {
    string name;

    explicit Teacher(string teacherName) : name(move(teacherName)) {}
};

struct Subject {
    string name;
    vector<Teacher> teachers;

    explicit Subject(string subjectName, vector<Teacher> subjectTeachers) :
            name(move(subjectName)), teachers(move(subjectTeachers)) {}
};

struct Group {
    string name;
    vector<Subject> subjects;
    size_t size;

    explicit Group(string groupName, vector<Subject> groupSubjects, size_t groupSize) :
            name(move(groupName)), subjects(move(groupSubjects)), size(groupSize) {}
};

using Day = string;

struct Time {
    Day day;
    size_t number;
};

struct Class {
    Group group;
    Subject subject;
    Room room;
    Teacher teacher;
    Time time;
};