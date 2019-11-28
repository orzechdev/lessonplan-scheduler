#ifndef ALGORITHM_LESSONPLANINDIVIDUAL_HPP
#define ALGORITHM_LESSONPLANINDIVIDUAL_HPP

#include <vector>

#include "../algorithm/SchedulingProblemProperties.hpp"
#include "LessonplanIndividualDescriptor.hpp"

using std::vector;

namespace lessonplans {
    class LessonplanIndividual {
    public:
        unsigned int getMaxDataCount() const;
        void setMaxDataCount(unsigned int maxDataCount);

        vector<vector<unsigned short>> getLessonplan();

        void setLessonplan(vector<vector<unsigned short>> lessonplan);

        void setLessonplanDataItem(unsigned short dataIdx, unsigned short weekDayId, unsigned short lessonId,
                                   unsigned short classId, unsigned short subjectId, unsigned short teacherId,
                                   unsigned short roomId);

        void setLessonplanDataItemWeekDay(unsigned short dataIdx, unsigned short weekDayId);

        void setLessonplanDataItemLesson(unsigned short dataIdx, unsigned short lessonId);

        void setLessonplanDataItemTeacher(unsigned short dataIdx, unsigned short teacherId);

        void setLessonplanDataItemRoom(unsigned short dataIdx, unsigned short roomId);

        static const short dataTypes = 6;

        LessonplanIndividualDescriptor *getLessonplanIndividualDescriptor() const;

        void setLessonplanIndividualDescriptor(LessonplanIndividualDescriptor *lessonplanIndividualDescriptor);

    private:
        unsigned int maxDataCount;
        vector<vector<unsigned short>> lessonplan;
        LessonplanIndividualDescriptor* lessonplanIndividualDescriptor;
    };
}

#endif //ALGORITHM_LESSONPLANINDIVIDUAL_HPP
