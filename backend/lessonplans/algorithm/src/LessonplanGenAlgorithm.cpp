#include "LessonplanGenAlgorithm.hpp"

#include <utility>
#include <climits>
#include <algorithm>

namespace lessonplans {

    void LessonplanGenAlgorithm::setAlgorithmData(LessonplanData* lessonplanData) {
        this->lessonplanData = lessonplanData;
    }

    vector<unsigned short> LessonplanGenAlgorithm::getRandomTakingSequence(unsigned short sequenceSize) {
        // TODO: ... https://stackoverflow.com/questions/20734774/random-array-generation-with-no-duplicates

        return vector<unsigned short>();
    }

    void LessonplanGenAlgorithm::initPopulation() {

        this->population = *new vector<LessonplanIndividual*>(
                this->populationCount
        );

        for (int i = 0; i < this->populationCount; i++) {
            auto* lessonplanIndividual = new LessonplanIndividual();

            lessonplanIndividual->initLessonplan(this->lessonplanData);

            this->population[i] = lessonplanIndividual;
        }
    }

    void LessonplanGenAlgorithm::crossover() {

    }

    void LessonplanGenAlgorithm::mutate() {

    }

    void LessonplanGenAlgorithm::evaluate() {

    }

    void LessonplanGenAlgorithm::select() {

    }

//    unsigned long long LessonplanGenAlgorithm::encodeIndividualLesson(unsigned short room, unsigned short subject,
//                                             unsigned short teacher, unsigned short classItem) {
//        unsigned long long individualLesson = (
//                ((unsigned long long) classItem << 48u) // Set fourth byte as class
//                | ((unsigned long long) teacher << 32u) // Set third byte as teacher
//                | ((unsigned long long) subject << 16u) // Set second byte as subject
//                | (unsigned long long) room // Set first byte as room
//        );
//
//        return individualLesson;
//    }
//
//    vector<unsigned short> LessonplanGenAlgorithm::decodeIndividualLesson(unsigned long long individual) {
//        vector<unsigned short> individualLessonData = *new vector<unsigned short>(
//                4 // Four different data encoded -> room, subject, teacher, class
//        );
//
//        individualLessonData[0] = (individual & 0xFFu); // Extract first byte as room
//        individualLessonData[1] = ((individual >> 16u) & 0xFFu); // Extract second byte as subject
//        individualLessonData[2] = ((individual >> 32u) & 0xFFu); // Extract third byte as teacher
//        individualLessonData[3] = ((individual >> 48u) & 0xFFu); // Extract fourth byte as class
//
//        return individualLessonData;
//    }

    vector<vector<unsigned short>> LessonplanGenAlgorithm::getLessonplanFromBestIndividual() {
        return this->population[0]->getIndividual();
    }

    vector<vector<vector<unsigned short>>> LessonplanGenAlgorithm::getLessonplansFromAllIndividuals() {
        vector<vector<vector<unsigned short>>> lessonplans = *new vector<vector<vector<unsigned short>>>(
                this->populationCount
        );

        std::transform(
                this->population.begin(),
                this->population.end(),
                lessonplans.begin(),
                [](LessonplanIndividual* lessonplanIndividual) {
                    return lessonplanIndividual->getIndividual();
                }
        );

        return lessonplans;
    }

}
