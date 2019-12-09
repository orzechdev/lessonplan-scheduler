#ifndef ALGORITHM_SCHEDULINGGREEDYALGORITHM_HPP
#define ALGORITHM_SCHEDULINGGREEDYALGORITHM_HPP

#include "../SchedulingProblem.hpp"
#include "../SchedulingProblemProperties.hpp"
#include "../../lessonplan/LessonplanIndividual.hpp"
#include "../SchedulingSolution.hpp"
#include "../../lessonplan/LessonplanScoreList.hpp"

namespace lessonplans {
    class SchedulingGreedyAlgorithm {
    public:
        SchedulingGreedyAlgorithm(int iterationsCount);

        SchedulingSolution *findBestLessonplan(SchedulingProblem *schedulingProblem);

    private:
        int calculationsTimeLimitInSeconds;
        LessonplanIndividual *bestIndividual;
        LessonplanScoreList *lessonplanScoreList;

        LessonplanIndividual *
        reformLessonplan(LessonplanIndividual *lessonplanIndividual, SchedulingProblem *schedulingProblem);

        void reformLessonplanTeacherDataItem(LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
                                             SchedulingProblemProperties *schedulingProblemProperties,
                                             vector<unsigned short> *lessonplanDataItem);

        void
        reformLessonplanRoomDataItem(LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
                                     SchedulingProblemProperties *schedulingProblemProperties,
                                     vector<unsigned short> *lessonplanDataItem);

        void reformLessonplanClassSubjectDataItem(LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
                                                  SchedulingProblemProperties *schedulingProblemProperties,
                                                  vector<unsigned short> *lessonplanDataItem);

        void reformLessonplanClassSubjectTeacher(LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
                                                 SchedulingProblemProperties *schedulingProblemProperties,
                                                 vector<unsigned short> *lessonplanDataItem,
                                                 vector<vector<unsigned short>> *classesSubjectsTeachersToAssign);

        static unsigned short
        findTeacherForClassSubject(SchedulingProblemProperties *schedulingProblemProperties, unsigned short subjectId);
    };
}

#endif //ALGORITHM_SCHEDULINGGREEDYALGORITHM_HPP
