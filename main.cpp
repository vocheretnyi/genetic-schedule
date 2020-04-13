#include <iostream>
#include <vector>

#include "Classes.h"
#include "DataStorage.h"
#include "Population.h"
#include "RandomHelper.h"

using namespace std;

const double MUTATION_RATE = 0.02;
const size_t POPULATION_SIZE = 50;
const size_t EVOLUTION_MAX_ITERATIONS = 5000000;

const int TEACHERS_PER_SUBJECT = 7;
const int SUBJECTS_PER_GROUP = 6;
const int LESSONS_PER_DAY = 4;

static vector<Teacher> GetRandomSubsetOfTeachers(const vector<Teacher>& teachers) {
    return GetRandomSubset(teachers, TEACHERS_PER_SUBJECT);
}

static vector<Subject> GetRandomSubsetOfSubjects(const vector<Subject>& subjects) {
    return GetRandomSubset(subjects, SUBJECTS_PER_GROUP);
}

int main() {
    vector<Day> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"}; // 5
    vector<Teacher> teachers = {
            Teacher("Merk"),
            Teacher("Margo"),
            Teacher("Fish"),
            Teacher("Roma"),
            Teacher("Pokemon"),
            Teacher("Biba"),
            Teacher("Nika"),
            Teacher("Vlad"),
    }; // 8
    vector<Room> rooms = {
            Room(215, 30),
            Room(505, 35),
            Room(1, 27),
            Room(39, 100),
            Room(303, 25),
            Room(27, 35),
    }; // 6
    vector<Subject> subjects = {
            Subject("Algebra", GetRandomSubsetOfTeachers(teachers)),
            Subject("Geometry", GetRandomSubsetOfTeachers(teachers)),
            Subject("Programming", GetRandomSubsetOfTeachers(teachers)),
            Subject("Discrete Math", GetRandomSubsetOfTeachers(teachers)),
            Subject("DataStorage science", GetRandomSubsetOfTeachers(teachers)),
            Subject("DataStorage structures", GetRandomSubsetOfTeachers(teachers)),
            Subject("Math Anal.", GetRandomSubsetOfTeachers(teachers)),
            Subject("Prob. Th.", GetRandomSubsetOfTeachers(teachers)),
            Subject("Algorithms", GetRandomSubsetOfTeachers(teachers)),
    }; // 9
    vector<Group> groups = {
            Group("TTP-42", GetRandomSubsetOfSubjects(subjects), 20),
            Group("TTP-41", GetRandomSubsetOfSubjects(subjects), 30),
            Group("MI-4", GetRandomSubsetOfSubjects(subjects), 26),
    };

    DataStorage data(groups, subjects, rooms, teachers, days, LESSONS_PER_DAY);

    Population population(data, MUTATION_RATE, POPULATION_SIZE);

    int iterations = 0;

    while (!population.AnswerReady() && iterations < EVOLUTION_MAX_ITERATIONS) {
        ++iterations;
        population.evolve();
        if (iterations % 100 == 0) {
            cout << iterations << endl;
        }
    }

    cout << "population size = " << POPULATION_SIZE << "\n";
    cout << "mutation rate = " << MUTATION_RATE << "\n";
    cout << "iterations = " << iterations << "\n";
    cout << "answer is ready = " << population.AnswerReady() << "\n\n\n";

    auto schedule = population.GetAnswer().schedule.schedule;

    cout << "=================================\n";

    for (const Day& mainDay : days) {
        cout << "[Day: " << mainDay << "]\n";

        for (auto&[group, schedulePerGroup] : schedule) {
            auto& listOfClasses = schedulePerGroup[mainDay];
            cout << "  Group: " << group.name << "\n";
            for (Class& class_ : listOfClasses) {
                cout << "  " << class_.time.number + 1 << ")\n";
                cout << "  room = " << class_.room.number << "\n";
                cout << "  lesson = " << class_.subject.name << "\n";
                cout << "  teacher = " << class_.teacher.name << "\n";
            }
            cout << "  --------------------\n";
        }
        cout << "=================================\n";
    }

    return 0;
}
