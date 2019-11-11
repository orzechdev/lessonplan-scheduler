#include <numeric>
#include <chrono>
#include <random>
#include <algorithm>

#include "RandomNumberGenerator.hpp"

namespace lessonplans {

    unsigned short RandomNumberGenerator::getRandomNumber(unsigned short minimumNumber, unsigned short maximumNumber) {
        // Init random engine with unusual seed
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 randomEngine(seed);

        // Get random int distribution
        std::uniform_int_distribution<unsigned int> intDistribution(minimumNumber, maximumNumber); // uniform, unbiased

        // Get random unsigned short from int distribution
        int number = static_cast<unsigned short>(intDistribution(randomEngine));

        return number;
    }

    vector<unsigned short> RandomNumberGenerator::getRandomIdxsSequence(unsigned short sequenceSize) {
        return RandomNumberGenerator::getRandomNumbersSequence(sequenceSize, 0);
    }

    vector<unsigned short> RandomNumberGenerator::getRandomIdsSequence(unsigned short sequenceSize) {
        return RandomNumberGenerator::getRandomNumbersSequence(sequenceSize, 1);
    }

    vector<unsigned short> RandomNumberGenerator::getRandomNumbersSequence(unsigned short sequenceSize,
                                                                                         unsigned short lowestNumber) {
        // Init vector with required size
        vector<unsigned short> sequence = *new vector<unsigned short>(
                sequenceSize
        );

        // Populate vector with increasing numbers
        std::iota(std::begin(sequence), std::end(sequence), lowestNumber);

        // Init random engine with unusual seed
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 randomEngine(seed);

        // Shuffle numbers in vector with random engine to obtain theirs random distribution
        std::shuffle(std::begin(sequence), std::end(sequence), randomEngine);

        return sequence;
    }

}
