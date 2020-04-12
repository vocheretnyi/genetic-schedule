//
// Created by vocheretnyi on 10.04.20.
//

#include <ctime>
#include <utility>
#include <algorithm>
#include <cassert>
#include <iostream>
#include "Population.h"

using namespace std;

Population::Population(const Data& data, double mutationRate, size_t populationSize)
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
    uniform_real_distribution<double> real_distribution(0.0, 1.0);

    for (int i = 0; i < population_.size(); ++i) {
        const DNA& dna1 = GetDNAWithProbability(real_distribution(random_engine()));
        const DNA& dna2 = GetDNAWithProbability(real_distribution(random_engine()));
        DNA newDNA = mutation(crossover(dna1, dna2));
        double fitness = newDNA.calcFitness();
        new_population.push_back(newDNA);
    }

    population_ = move(new_population);
}

DNA Population::mutation(DNA dna) const {
//    uniform_real_distribution<double> real_distribution(0.0, 1.0);
//    uniform_int_distribution<int> int_distribution(0, diophantine_.result);
//    for (int& gen : dna.genes) {
//        if (real_distribution(random_engine()) < mutationRate_) {
//            gen = int_distribution(random_engine());
//        }
//    }
//    return dna;
}

DNA Population::crossover(const DNA& dna1, const DNA& dna2) const {
//    uniform_int_distribution<int> int_distribution(0, diophantine_.coeffs.size());
//    DNA dna(dna1.genes.size());
//    int border = int_distribution(random_engine());
//    for (int i = 0; i < dna1.genes.size(); ++i) {
//        if (i < border) {
//            dna.genes[i] = dna1.genes[i];
//        } else {
//            dna.genes[i] = dna2.genes[i];
//        }
//    }
//    return dna;
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

std::mt19937& Population::random_engine() {
    static std::random_device random_device;
    static std::mt19937 smt(random_device());
    return smt;
}
