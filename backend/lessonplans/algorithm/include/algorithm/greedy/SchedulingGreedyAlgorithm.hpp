#ifndef ALGORITHM_SCHEDULINGGREEDYALGORITHM_HPP
#define ALGORITHM_SCHEDULINGGREEDYALGORITHM_HPP

#include "../SchedulingProblem.hpp"
#include "../SchedulingProblemProperties.hpp"
#include "../../lessonplan/LessonplanIndividual.hpp"
#include "../SchedulingSolution.hpp"

namespace lessonplans {
    class SchedulingGreedyAlgorithm {
    public:
        SchedulingGreedyAlgorithm(int iterationsCount);

        SchedulingSolution *findBestLessonplan(SchedulingProblem *schedulingProblem);

    private:
        int iterationsCount;
        LessonplanIndividual *bestIndividual;
        vector<vector<int>> individualsHardScores;
        vector<vector<int>> individualsSoftScores;
        vector<int> individualsSummaryHardScores;
        vector<int> individualsSummarySoftScores;

        LessonplanIndividual *
        reformLessonplan(LessonplanIndividual *lessonplanIndividual, SchedulingProblem *schedulingProblem);

        void reformLessonplanTeacherDataItem(LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
                                             SchedulingProblemProperties *schedulingProblemProperties,
                                             vector<unsigned short> *lessonplanDataItem,
                                             vector<vector<vector<unsigned short>>> *assignedLessonAndDaysToTeachers);

        void
        reformLessonplanRoomDataItem(LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
                                     SchedulingProblemProperties *schedulingProblemProperties,
                                     vector<unsigned short> *lessonplanDataItem,
                                     vector<vector<vector<unsigned short>>> *assignedLessonAndDaysToRooms);

        void reformLessonplanClassSubjectDataItem(LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
                                                  SchedulingProblemProperties *schedulingProblemProperties,
                                                  vector<unsigned short> *lessonplanDataItem,
                                                  vector<vector<vector<unsigned short>>> *assignedLessonAndDaysToClasses);

        void reformLessonplanClassSubjectTeacher(LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
                                                 SchedulingProblemProperties *schedulingProblemProperties,
                                                 vector<unsigned short> *lessonplanDataItem,
                                                 vector<vector<unsigned short>> *assignedTeachersToClassesSubjects,
                                                 vector<vector<unsigned short>> *classesSubjectsTeachersToAssign);

        static unsigned short
        findTeacherForClassSubject(SchedulingProblemProperties *schedulingProblemProperties, unsigned short subjectId);
    };
}

#endif //ALGORITHM_SCHEDULINGGREEDYALGORITHM_HPP
