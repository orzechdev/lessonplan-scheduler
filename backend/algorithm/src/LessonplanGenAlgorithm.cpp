#include "LessonplanGenAlgorithm.hpp"

namespace lessonplans {

    void LessonplanGenAlgorithm::setAlgorithmData(unsigned short dayCount, unsigned short lessonCount,
                                                  std::vector<unsigned short> rooms, std::vector<unsigned short> subjects,
                                                  std::vector<unsigned short> teachers, std::vector<unsigned short> classes) {
        this->dayCount = dayCount;
        this->lessonCount = lessonCount;
        this->rooms = rooms;
        this->subjects = subjects;
        this->teachers = teachers;
        this->classes = classes;
    }

    void LessonplanGenAlgorithm::initPopulation() {
        this->population = *new std::vector<std::vector<std::vector<unsigned long int>>>(
                this->populationCount, std::vector<std::vector<unsigned long int>>(
                        this->dayCount, std::vector<unsigned long int>(
                                this->lessonCount
                        )
                )
        );
    }

    void LessonplanGenAlgorithm::crossover() {

    }

    void LessonplanGenAlgorithm::mutate() {

    }

    void LessonplanGenAlgorithm::evaluate() {

    }

    void LessonplanGenAlgorithm::select() {

    }

    std::vector<std::vector<std::vector<unsigned short>>> LessonplanGenAlgorithm::getLessonplan() {
        std::vector<std::vector<std::vector<unsigned short>>> lessonplan(this->dayCount, std::vector<std::vector<unsigned short>>(this->lessonCount, std::vector<unsigned short>(4)));
        for (long unsigned int i = 0; i < this->population[0].size(); i++) {
            for (long unsigned int j = 0; j < this->population[0][i].size(); j++) {
                unsigned long int popValue = 4026597120+i+j;
                this->population[0][i][j] = popValue;
                lessonplan[i][j][0] = (popValue&0xFFu); //extract first byte as room
                lessonplan[i][j][1] = ((popValue>>8u)&0xFFu); //extract second byte as subject
                lessonplan[i][j][2] = ((popValue>>16u)&0xFFu); //extract third byte as teacher
                lessonplan[i][j][3] = ((popValue>>24u)&0xFFu); //extract fourth byte as class
            }
        }

        return lessonplan;
    }

}
