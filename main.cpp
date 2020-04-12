#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

#include "Classes.h"
#include "Data.h"
#include "Population.h"

using namespace std;

const double mutationRate = 0.01;
const size_t populationSize = 50;

const int TEACHERS_PER_SUBJECT = 4;
const int SUBJECTS_PER_GROUP = 7;
const int LESSONS_PER_DAY = 4;

static vector<Teacher> GetRandomSubsetOfTeachers(vector<Teacher> teachers) {
    shuffle(teachers.begin(), teachers.end(), mt19937(random_device()()));
    return {teachers.begin(), teachers.begin() + TEACHERS_PER_SUBJECT};
}

static vector<Subject> GetRandomSubsetOfSubjects(vector<Subject> subjects) {
    shuffle(subjects.begin(), subjects.end(), mt19937(random_device()()));
    return {subjects.begin(), subjects.begin() + SUBJECTS_PER_GROUP};
}

int main() {
    vector<Day> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"}; // 5
    vector<Teacher> teachers = {Teacher("Merk"), Teacher("Margo"), Teacher("Fish"), Teacher("Roma"),
                                Teacher("Pokemon")}; // 5
    vector<Room> rooms = {
            Room(215, 30),
            Room(505, 35),
            Room(1, 27),
            Room(39, 100),
            Room(303, 25)
    }; // 5
    vector<Subject> subjects = {
            Subject("Algebra", GetRandomSubsetOfTeachers(teachers)),
            Subject("Geometry", GetRandomSubsetOfTeachers(teachers)),
            Subject("Programming", GetRandomSubsetOfTeachers(teachers)),
            Subject("Discrete Math", GetRandomSubsetOfTeachers(teachers)),
            Subject("Data science", GetRandomSubsetOfTeachers(teachers)),
            Subject("Data structures", GetRandomSubsetOfTeachers(teachers)),
            Subject("Math Anal.", GetRandomSubsetOfTeachers(teachers)),
            Subject("Prob. Th.", GetRandomSubsetOfTeachers(teachers)),
            Subject("Algorithms", GetRandomSubsetOfTeachers(teachers)),
    }; // 9
    vector<Group> groups = {
            Group("TTP-42", GetRandomSubsetOfSubjects(subjects), 20), // 5 rooms
            Group("TTP-41", GetRandomSubsetOfSubjects(subjects), 30), // 3 rooms
            Group("TK-4", GetRandomSubsetOfSubjects(subjects), 27), // 4 rooms
            Group("MI-4", GetRandomSubsetOfSubjects(subjects), 26), // 4 rooms
    };

    Data data(groups, subjects, rooms, teachers, days, LESSONS_PER_DAY);

    Population population(data, mutationRate, populationSize);

    int iterations = 0;

    while (!population.AnswerReady() && iterations < 50000) {
        ++iterations;
        population.evolve();
        if (iterations % 100 == 0) {
            cout << iterations << "\n";
        }
    }

    cout << "population size = " << populationSize << "\n";
    cout << "mutation rate = " << mutationRate << "\n";
    cout << "iterations = " << iterations << "\n";
    cout << "answer is ready = " << population.AnswerReady() << "\n";

    auto ans = population.GetAnswer();

//    for (int i = 0; i < ans.size(); ++i) {
//        cout << ans[i] << "*" << coeffs[i];
//        if (i + 1 != ans.size()) {
//            cout << " + ";
//        }
//    }
//    cout << " = " << result << "\n";

    return 0;
}
