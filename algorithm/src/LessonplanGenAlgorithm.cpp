#include "LessonplanGenAlgorithm.hpp"

namespace lessonplans {

    void LessonplanGenAlgorithm::setAlgorithmData(std::vector<int> lessons, std::vector<int> rooms,
                                                  std::vector<int> subjects, std::vector<int> teachers,
                                                  std::vector<int> classes) {
        this->lessons = lessons;
        this->rooms = rooms;
        this->subjects = subjects;
        this->teachers = teachers;
        this->classes = classes;
    }

    std::vector<std::vector<int>> LessonplanGenAlgorithm::getLessonplan() {

    }

}
