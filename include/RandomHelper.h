#pragma once

#include <random>
#include <algorithm>

static std::mt19937& random_engine() {
    static std::random_device random_device;
    static std::mt19937 smt(random_device());
    return smt;
}

template<typename T>
static const T& GetRandom(const vector<T>& vec) {
    uniform_int_distribution<int> distribution(0, vec.size() - 1);
    size_t randomPos = distribution(random_engine());
    return vec[randomPos];
}

template<typename T>
static vector<T> GetRandomSubset(vector<T> vec, size_t len) {
    shuffle(vec.begin(), vec.end(), mt19937(random_device()()));
    return {vec.begin(), vec.begin() + len};
}

static bool RandomBool() {
    uniform_int_distribution<int> bool_distribution(0, 1);
    return bool_distribution(random_engine());
}

static double RandomProbability() {
    uniform_real_distribution<double> distribution(0.0f, 1.0f);
    return distribution(random_engine());
}
