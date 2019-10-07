#include "LessonplanGenAlgorithm.hpp"

#include <utility>
#include <climits>

namespace lessonplans {

    void LessonplanGenAlgorithm::setAlgorithmData(
        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> lessonsRestrictionsForIndividuals,
        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> weekDaysRestrictionsForIndividuals,
        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> roomsRestrictionsForIndividuals,
        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> teachersRestrictionsForIndividuals,
        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> classesRestrictionsForIndividuals,
        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> subjectsRestrictionsForIndividuals
    ) {
        this->classesRestrictionsForIndividuals = std::move(classesRestrictionsForIndividuals);
//        this->subjectsRestrictionsForIndividuals = std::move(subjectsRestrictionsForIndividuals);
//        this->roomsRestrictionsForIndividuals = std::move(roomsRestrictionsForIndividuals);
//        this->teachersRestrictionsForIndividuals = std::move(teachersRestrictionsForIndividuals);
//        this->lessonsRestrictionsForIndividuals = std::move(lessonsRestrictionsForIndividuals);
//        this->weekDaysRestrictionsForIndividuals = std::move(weekDaysRestrictionsForIndividuals);

        /*
         * TODO: HERE IS SOMETHONG WRONG WITH .size() !!!!!!!! and anywhere .size() may not be properly assigned to int!!!
         */

        this->dataCounts[0] = (int) this->classesRestrictionsForIndividuals.size();
//        this->dataCounts[1] = this->subjectsRestrictionsForIndividuals.size();
//        this->dataCounts[2] = this->roomsRestrictionsForIndividuals.size();
//        this->dataCounts[3] = this->teachersRestrictionsForIndividuals.size();
//        this->dataCounts[4] = this->lessonsRestrictionsForIndividuals.size();
//        this->dataCounts[5] = this->weekDaysRestrictionsForIndividuals.size();

    }

    std::vector<unsigned short> LessonplanGenAlgorithm::getRandomTakingSequence(unsigned short sequenceSize) {
        // TODO: ... https://stackoverflow.com/questions/20734774/random-array-generation-with-no-duplicates

        return std::vector<unsigned short>();
    }

    void LessonplanGenAlgorithm::initPopulation() {
        this->population = *new std::vector<std::vector<std::vector<unsigned short>>>(
                this->populationCount, std::vector<std::vector<unsigned short>>(
                        USHRT_MAX, std::vector<unsigned short>(
                                (int) this->dataCounts.size()
                        )
                )
        );
        this->populationPartnersCount = *new std::vector<std::vector<std::vector<unsigned short>>>(
                this->populationCount, std::vector<std::vector<unsigned short>>(
                        (int) this->dataCounts.size(), std::vector<unsigned short>(
                                USHRT_MAX
                        )
                )
        );

//        for (unsigned int i = 0; i < this->populationCount; i++) {
            for (unsigned int j = 0; j < USHRT_MAX; j++) {
                for (int k = 0; k < (int) this->dataCounts.size(); k++) {
                    this->population[0][j][k] = 1;
                }
            }
//        }
        return;

        for (unsigned int i = 0; i < this->populationCount; i++) {
            this->population[i] = this->iterateThroughTypedDataList(this->lessonsRestrictionsForIndividuals, 0, i);
//            this->iterateThroughTypedDataList(this->weekDaysRestrictionsForIndividuals, this->dataCounts[1], i);
//            this->iterateThroughTypedDataList(this->roomsRestrictionsForIndividuals, this->dataCounts[2], i);
//            this->iterateThroughTypedDataList(this->teachersRestrictionsForIndividuals, this->dataCounts[3], i);
//            this->iterateThroughTypedDataList(this->classesRestrictionsForIndividuals, this->dataCounts[4], i);
//            this->iterateThroughTypedDataList(this->subjectsRestrictionsForIndividuals, this->dataCounts[5], i);
        }



    }

    std::vector<std::vector<unsigned short>> LessonplanGenAlgorithm::iterateThroughTypedDataList(
            std::vector<std::vector<std::vector<std::vector<unsigned short>>>> dataTypedList,
            unsigned short dataType,
            unsigned short populationIndividual
    ) {

        std::vector<std::vector<unsigned short>> individual = this->population[populationIndividual];
        unsigned short dataTypedListSize = this->dataCounts[dataType];

        // Iterate through the whole list of currently selected data type
        for (unsigned short i = 0; i < dataTypedListSize; i++) {
            std::vector<std::vector<std::vector<unsigned short>>> dataTypedRestrictionForIndividuals = dataTypedList[i];

            individual[i] = this->iterateThroughRelatedTypedDataList(dataTypedRestrictionForIndividuals, dataType, 0, populationIndividual);
        }

        return individual;
    }

    std::vector<unsigned short> LessonplanGenAlgorithm::iterateThroughRelatedTypedDataList(
            std::vector<std::vector<std::vector<unsigned short>>> dataTypedRestrictionForIndividuals,
            unsigned short dataType,
            unsigned short relatedDataTypeIndex,
            unsigned short populationIndividual
    ) {
        unsigned short differentDataTypes = dataTypedRestrictionForIndividuals.size();
        std::vector<std::vector<unsigned short>> typedRestrictionList = dataTypedRestrictionForIndividuals[relatedDataTypeIndex];
        unsigned short currentRelatedDataType = relatedDataTypeIndex >= dataType ? relatedDataTypeIndex + 1 : relatedDataTypeIndex; // Skip most outer loop data type
        unsigned short currentRelatedDataCount = this->dataCounts[currentRelatedDataType];

        // Iterate through the whole list of currently selected related data type
        for (unsigned short k = 0; k < currentRelatedDataCount; k++) {
            std::vector<unsigned short> typedRestriction = typedRestrictionList[k];
            unsigned short maxPartners = typedRestriction[0];
            unsigned short minPartners = typedRestriction[1];
            unsigned short willingToRelate = typedRestriction[2];

            if (!willingToRelate) {
                continue;
            }

            if (this->populationPartnersCount[populationIndividual][currentRelatedDataType][k] >= maxPartners) {
                continue;
            }

            // TODO: backward tracking ??? !!!
            this->populationPartnersCount[populationIndividual][currentRelatedDataType][k]++;

            if (currentRelatedDataType >= differentDataTypes) {
                std::vector<unsigned short> preparedCell = std::vector<unsigned short>(
                        this->dataCounts.size()
                );
                preparedCell[currentRelatedDataType] = k;
                return preparedCell;
            }

            std::vector<unsigned short> preparedCell = this->iterateThroughRelatedTypedDataList(dataTypedRestrictionForIndividuals, dataType, relatedDataTypeIndex + 1, populationIndividual);
            preparedCell[currentRelatedDataCount] = k;
            return preparedCell;
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

    std::vector<unsigned short> LessonplanGenAlgorithm::initLessons(unsigned short classIndex, unsigned int lessonIndex, std::vector<unsigned short> alreadySelectedRooms) {
//        unsigned short classesCount = this->classes.size();
//
//        for (unsigned short i = 0; i < classesCount; i++) {
//            unsigned short selectedClass = this->classes[i]; // TO USE
//            std::vector<std::vector<unsigned short>> classSubjectsWithHours = this->classesSubjectsWithHours[i];
//            unsigned short classSubjectsCount = classSubjectsWithHours.size();
//
//            for (unsigned short j = 0; j < classSubjectsCount; j++) {
//                unsigned short selectedSubject = classSubjectsWithHours[j][0]; // TO USE
//                unsigned short classSubjectHours = classSubjectsWithHours[j][1];
//
//                // find room
//
//                // find teacher
//
//                for (unsigned short k = 0; k < classSubjectHours; k++) {
//
//                }
//            }
//        }
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
//    std::vector<unsigned short> LessonplanGenAlgorithm::decodeIndividualLesson(unsigned long long individual) {
//        std::vector<unsigned short> individualLessonData = *new std::vector<unsigned short>(
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

    std::vector<std::vector<unsigned short>> LessonplanGenAlgorithm::getBestIndividual() {
        return this->population[0];
    }

    std::vector<std::vector<unsigned short>> LessonplanGenAlgorithm::getLessonplanFromBestIndividual() {
//        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> lessonplan = *new std::vector<std::vector<std::vector<std::vector<unsigned short>>>>(
//                this->classCount, std::vector<std::vector<std::vector<unsigned short>>>(
//                        this->dayCount, std::vector<std::vector<unsigned short>>(
//                                this->lessonCount, std::vector<unsigned short>(
//                                        4 // Four different data encoded -> room, subject, teacher, class
//                                )
//                        )
//                )
//        );
//
//        std::vector<std::vector<std::vector<unsigned long long>>> bestIndividual = this->getBestIndividual();
//        unsigned short bestIndividualClassCount = bestIndividual.size();
//        unsigned short bestIndividualDayCount = bestIndividual[0].size();
//        unsigned short bestIndividualLessonCount = bestIndividual[0][0].size();
//
//        for (unsigned short i = 0; i < bestIndividualClassCount; i++) {
//            std::vector<std::vector<unsigned long long>> bestIndividualClass = bestIndividual[i];
//            for (unsigned short j = 0; j < bestIndividualDayCount; j++) {
//                std::vector<unsigned long long> bestIndividualDay = bestIndividualClass[j];
//                for (unsigned short k = 0; k < bestIndividualLessonCount; k++) {
//                    lessonplan[i][j][k] = lessonplans::LessonplanGenAlgorithm::decodeIndividualLesson(bestIndividualDay[k]);
//                }
//            }
//        }
//
//        return lessonplan;
        return this->getBestIndividual();
    }

}
