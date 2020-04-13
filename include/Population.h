//
// Created by vocheretnyi on 10.04.20.
//

#pragma once

#include <vector>
#include <random>

#include "DataStorage.h"
#include "DNA.h"

class Population {
public:
    Population(const DataStorage& data, double mutationRate, size_t populationSize);

    void evolve();

    bool AnswerReady() const;

    const DNA& GetAnswer() const;

private:
    DNA mutation(DNA dna) const;

    DNA crossover(const DNA& dna1, const DNA& dna2) const;

    Schedule::Schedule_Per_Group crossover(const Schedule::Schedule_Per_Group& schedulePerGroup1,
                                           const Schedule::Schedule_Per_Group& schedulePerGroup2) const;

    vector<Class> crossover(const vector<Class>& classes1,
                            const vector<Class>& classes2) const;

    Class crossover(const Class& class1, const Class& class2) const;

    const DNA& GetDNAWithProbability(double probability) const;

    void calcFitness();

    const DataStorage& data_;
    std::vector<DNA> population_;
    double mutationRate_;

    bool answerReady;
    DNA answer;
};

