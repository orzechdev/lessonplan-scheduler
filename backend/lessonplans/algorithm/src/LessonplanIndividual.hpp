#ifndef ALGORITHM_LESSONPLANINDIVIDUAL_HPP
#define ALGORITHM_LESSONPLANINDIVIDUAL_HPP

#include <vector>

#include "Individual.hpp"
#include "LessonplanData.hpp"

using std::vector;

namespace lessonplans {
    class LessonplanIndividual : public Individual {
    public:
        LessonplanIndividual() : Individual() {}
        vector<vector<unsigned short>> initLessonplan(LessonplanData* lessonplanData);
        vector<vector<unsigned short>> initLessonplan(
                unsigned short weekDaysCount,
                unsigned short lessonsCount,
                unsigned short classesCount,
                unsigned short subjectsCount,
                unsigned short teachersCount,
                unsigned short roomsCount,
                vector<vector<unsigned short>> classesSubjects,
                vector<vector<unsigned short>> teachersSubjects,
                vector<unsigned short> roomsSubjectsRestrictionStatus,
                vector<vector<unsigned short>> roomsSubjects
        );
        vector<vector<unsigned short>> getIndividual();

    private:
        static const short dataTypes = 6;
        unsigned int maxDataCount;
        vector<vector<unsigned short>> individual;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToClasses;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToTeachers;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToRooms;
        unsigned short findPossibleClass(unsigned short classesCount, vector<vector<unsigned short>> classesSubjects, unsigned short (*onNextFound)(unsigned short));
        unsigned short findPossibleSubject(unsigned short subjectsCount, vector<unsigned short> classSubjects, unsigned short (*onNextFound)(unsigned short));
        unsigned short findPossibleTeacher(unsigned short teacherIdx);
        vector<unsigned short> determinePossibleWeekDayAndLesson(
                unsigned short weekDaysCount,
                unsigned short lessonsCount,
                unsigned short classIdx,
                unsigned short teacherIdx,
                unsigned short roomIdx
        );

        unsigned short onNextFound(unsigned short foundIdx, unsigned short (*onNext)(unsigned short));

        unsigned short findPossibleClass(
                unsigned short weekDaysCount, unsigned short lessonsCount, unsigned short classesCount,
                unsigned short subjectsCount, unsigned short teachersCount, unsigned short roomsCount,
                vector<vector<unsigned short>> classesSubjects,
                vector<vector<unsigned short>> teachersSubjects,
                vector<unsigned short> roomsSubjectsRestrictionStatus,
                vector<vector<unsigned short>> roomsSubjects
        );

        bool findPossibleRoom(
                unsigned short individualDataIdx,
                unsigned short classIdx, unsigned short teacherIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId,
                unsigned short weekDaysCount, unsigned short lessonsCount,
                unsigned short classesCount, unsigned short subjectsCount, unsigned short teachersCount,
                unsigned short roomsCount, vector<vector<unsigned short>> classesSubjects,
                vector<vector<unsigned short>> teachersSubjects,
                vector<unsigned short> roomsSubjectsRestrictionStatus,
                vector<vector<unsigned short>> roomsSubjects
        );
    };
}

#endif //ALGORITHM_LESSONPLANINDIVIDUAL_HPP
