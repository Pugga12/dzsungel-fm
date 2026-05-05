//
// Created by adama on 5/5/26.
//
#include "dsp/noise.h"
#include <random>


extern "C" {
    float gaussianRandom() {
        static std::random_device rd;
        static std::mt19937 generator(rd());
        static std::normal_distribution<float> dist(GAUSSIAN_MEAN, GAUSSIAN_STDDEV);

        return dist(generator);
    }
}
