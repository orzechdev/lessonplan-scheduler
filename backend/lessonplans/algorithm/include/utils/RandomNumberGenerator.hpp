#ifndef ALGORITHM_RANDOMNUMBERGENERATOR_HPP
#define ALGORITHM_RANDOMNUMBERGENERATOR_HPP

#include <vector>

using std::vector;

namespace lessonplans {
    class RandomNumberGenerator {
    public:
        static unsigned short getRandomNumber(unsigned short minimumNumber, unsigned short maximumNumber);
        static vector<unsigned short> getRandomIdxsSequence(unsigned short sequenceSize);
        static vector<unsigned short> getRandomIdsSequence(unsigned short sequenceSize);
        static vector<unsigned short> getRandomNumbersSequence(unsigned short sequenceSize, unsigned short lowestNumber);
    };
}


#endif //ALGORITHM_RANDOMNUMBERGENERATOR_HPP
