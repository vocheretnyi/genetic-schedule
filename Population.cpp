//
// Created by vocheretnyi on 10.04.20.
//

#include <ctime>
#include <utility>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include "Population.h"
#include "Schedule.h"

using namespace std;

Population::Population(const DataStorage& data, double mutationRate, size_t populationSize)
        : data_(data), mutationRate_(mutationRate), answerReady(false) {

    population_.resize(populationSize);
    for (DNA& dna : population_) {
        dna.schedule = Schedule::GenerateRandomSchedule(data_);
    }

    calcFitness();
}

void Population::calcFitness() {
    double sum = 0.0f;

    for (DNA& dna : population_) {
        double fitness = dna.calcFitness();
        if (fitness == -1) {
            answerReady = true;
            answer = dna;
            return;
        }
        sum += fitness;
    }

    for (DNA& dna : population_) {
        dna.fitness = dna.fitness / sum;
    }
}

void Population::evolve() {
    vector<DNA> new_population;

    for (int i = 0; i < population_.size(); ++i) {
        const DNA& dna1 = GetDNAWithProbability(RandomProbability());
        const DNA& dna2 = GetDNAWithProbability(RandomProbability());
        new_population.push_back(mutation(crossover(dna1, dna2)));
    }

    population_ = move(new_population);
    calcFitness();
}

DNA Population::mutation(DNA dna) const {
    auto& schedule = dna.schedule.schedule;
    for (auto&[group, schedulePerGroup] : schedule) {
        for (auto&[day, listOfClasses] : schedulePerGroup) {
            for (Class& class_ : listOfClasses) {
                if (RandomProbability() < mutationRate_) {
                    class_.room = Schedule::GetRandomRoom(data_.rooms, group.size);
                }
                if (RandomProbability() < mutationRate_) {
                    class_.teacher = GetRandom(class_.subject.teachers);
                }
                if (RandomProbability() < mutationRate_) {
                    class_.subject = GetRandom(group.subjects);
                    class_.teacher = GetRandom(class_.subject.teachers);
                }
            }
        }
    }
    return dna;
}

Class Population::crossover(const Class& class1, const Class& class2) const {
    Class res;
    res.time = class1.time;
    res.group = class2.group;
    if (RandomBool()) {
        res.room = class1.room;
    } else {
        res.room = class2.room;
    }

    if (RandomBool()) {
        res.teacher = class1.teacher;
    } else {
        res.teacher = class2.teacher;
    }

    if (RandomBool()) {
        res.subject = class1.subject;
        res.teacher = class1.teacher;
    } else {
        res.subject = class2.subject;
        res.teacher = class2.teacher;
    }

    return res;
}

vector<Class> Population::crossover(const vector<Class>& classes1,
                                    const vector<Class>& classes2) const {
    vector<Class> classes;
    uniform_int_distribution<int> int_distribution(0, classes1.size());
    int border = int_distribution(random_engine());
    for (int i = 0; i < classes1.size(); ++i) {
        if (i < border) {
            classes.push_back(crossover(classes1[i], classes2[i]));
        } else {
            classes.push_back(crossover(classes2[i], classes1[i]));
        }
    }
    return classes;
}

Schedule::Schedule_Per_Group Population::crossover(const Schedule::Schedule_Per_Group& schedulePerGroup1,
                                                   const Schedule::Schedule_Per_Group& schedulePerGroup2) const {
    Schedule::Schedule_Per_Group res;
    for (const auto&[day, listOfClasses] : schedulePerGroup1) {
        if (RandomBool()) {
            res[day] = crossover(schedulePerGroup1.at(day), schedulePerGroup2.at(day));
        } else {
            res[day] = crossover(schedulePerGroup2.at(day), schedulePerGroup1.at(day));
        }
    }
    return res;
}

DNA Population::crossover(const DNA& dna1, const DNA& dna2) const {
    const auto& schedule1 = dna1.schedule.schedule;
    const auto& schedule2 = dna2.schedule.schedule;
    DNA dna;
    for (const auto&[group, schedulePerGroup] : schedule1) {
        if (RandomBool()) {
            dna.schedule.schedule[group] = crossover(schedule1.at(group), schedule2.at(group));
        } else {
            dna.schedule.schedule[group] = crossover(schedule2.at(group), schedule1.at(group));
        }
    }
    return dna;
}

const DNA& Population::GetDNAWithProbability(double probability) const {
    double sum = 0.0f;
    for (const DNA& dna : population_) {
        sum += dna.fitness;
        if (probability < sum) {
            return dna;
        }
    }
    assert(false);
    return DNA();
}

bool Population::AnswerReady() const {
    return answerReady;
}

const DNA& Population::GetAnswer() const {
    return answer;
}