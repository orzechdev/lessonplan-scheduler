#ifndef ALGORITHM_LESSONPLANGENALGORITHM_HPP
#define ALGORITHM_LESSONPLANGENALGORITHM_HPP

#include <vector>

#include "GenAlgorithm.hpp"

namespace lessonplans {
    class LessonplanGenAlgorithm : public GenAlgorithm {
        public:
            LessonplanGenAlgorithm(
                    int populationCount,
                    int generationNumber,
                    float crossoverProb,
                    float mutationProb
            ) :
                    GenAlgorithm(populationCount, generationNumber, crossoverProb, mutationProb)
            {}
            void setAlgorithmData(
                    unsigned short weekDaysCount,
                    unsigned short lessonsCount,
                    unsigned short classesCount,
                    unsigned short subjectsCount,
                    unsigned short teachersCount,
                    unsigned short roomsCount,
                    std::vector<unsigned short> classesSubjectsRestrictionStatus,
                    std::vector<std::vector<unsigned short>> classesSubjects,
                    std::vector<unsigned short> teachersSubjectsRestrictionStatus,
                    std::vector<std::vector<unsigned short>> teachersSubjects,
                    std::vector<unsigned short> roomsSubjectsRestrictionStatus,
                    std::vector<std::vector<unsigned short>> roomsSubjects
            );
            std::vector<std::vector<unsigned short>> getLessonplanFromBestIndividual();

        private:
            /*
             * Pre initialized data
             */
            // Algorithm data
            std::vector<std::vector<std::vector<std::vector<unsigned short>>>> lessonsRestrictionsForIndividuals, weekDaysRestrictionsForIndividuals,
                roomsRestrictionsForIndividuals, teachersRestrictionsForIndividuals, classesRestrictionsForIndividuals, subjectsRestrictionsForIndividuals;
//            unsigned short lessonCount, weekDayCount, roomCount, teacherCount, classCount, subjectCount;
            std::vector<int> dataCounts;
//            std::vector<unsigned short> rooms, subjects, teachers;
            // Algorithm constraints
//            std::vector<bool> roomsExclusiveAssignments;
//            std::vector<std::vector<unsigned short>> subjectsRooms, teachersSubjects;
//            std::vector<std::vector<std::vector<unsigned short>>> classesSubjectsIdsWithClassesSubjectsHours;

            /*
             * Generated data
             */
            // Population
            // 255.255.255.255 -> 11111111.11111111.11111111.11111111 -> room.subject.teacher.class
            // 65535.65535.65535.65535 -> 1111111111111111.1111111111111111.1111111111111111.1111111111111111 -> room.subject.teacher.class
//            std::vector<std::vector<std::vector<std::vector<unsigned long long>>>> population;
            std::vector<std::vector<std::vector<unsigned short>>> population;
            std::vector<std::vector<std::vector<std::vector<unsigned short>>>> populationAssignedLessonAndDaysToClasses;
            std::vector<std::vector<std::vector<std::vector<unsigned short>>>> populationAssignedLessonAndDaysToTeachers;
            std::vector<std::vector<std::vector<std::vector<unsigned short>>>> populationAssignedLessonAndDaysToRooms;
            std::vector<std::vector<std::vector<unsigned short>>> populationPartnersCount;
            unsigned short weekDaysCount;
            unsigned short lessonsCount;
            unsigned short classesCount;
            unsigned short subjectsCount;
            unsigned short teachersCount;
            unsigned short roomsCount;
            // Population constraints
            std::vector<unsigned short> classesSubjectsRestrictionStatus;
            std::vector<std::vector<unsigned short>> classesSubjects;
            std::vector<unsigned short> teachersSubjectsRestrictionStatus;
            std::vector<std::vector<unsigned short>> teachersSubjects;
            std::vector<unsigned short> roomsSubjectsRestrictionStatus;
            std::vector<std::vector<unsigned short>> roomsSubjects;

            /*
             * Other
             */
            void initPopulation() override;
            void crossover() override;
            void mutate() override;
            void evaluate() override;
            void select() override;
            std::vector<std::vector<unsigned short>> initIndividual(unsigned short individualIndex);
            std::vector<unsigned short> initIndividualSetWeekDayAndLesson(unsigned short individualIndex, unsigned short classIdx, unsigned short teacherIdx, unsigned short roomIdx);
            static unsigned long long encodeIndividualLesson(unsigned short room, unsigned short subject, unsigned short teacher, unsigned short classItem);
            static std::vector<unsigned short> decodeIndividualLesson(unsigned long long individualLesson);
            std::vector<unsigned short> getRandomTakingSequence(unsigned short sequenceSize);
            std::vector<std::vector<unsigned short>> getBestIndividual();
            std::vector<unsigned short> initLessons(unsigned short classIndex, unsigned int lessonIndex, std::vector<unsigned short> alreadySelectedRooms);
            std::vector<std::vector<unsigned short>> iterateThroughTypedDataList(std::vector<std::vector<std::vector<std::vector<unsigned short>>>> dataTypedList, unsigned short dataType, unsigned short populationIndividual);
            std::vector<unsigned short> iterateThroughRelatedTypedDataList(
                    std::vector<std::vector<std::vector<unsigned short>>> dataTypedRestrictionForIndividuals,
                    unsigned short dataType,
                    unsigned short relatedDataTypeIndex,
                    unsigned short populationIndividual
            );
    };
}

#endif //ALGORITHM_LESSONPLANGENALGORITHM_HPP
