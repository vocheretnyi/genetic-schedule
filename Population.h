//
// Created by vocheretnyi on 10.04.20.
//

#pragma once

#include <vector>
#include <random>

#include "Data.h"
#include "DNA.h"

class Population {
public:
    Population(const Data& data, double mutationRate, size_t populationSize);

    void evolve();

    bool AnswerReady() const;

    const DNA& GetAnswer() const;

private:
    DNA mutation(DNA dna) const;

    DNA crossover(const DNA& dna1, const DNA& dna2) const;

    const DNA& GetDNAWithProbability(double probability) const;

    static std::mt19937& random_engine();

    void calcFitness();

    const Data& data_;
    std::vector<DNA> population_;
    double mutationRate_;

    bool answerReady;
    DNA answer;
};

