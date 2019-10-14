#ifndef ALGORITHM_INDIVIDUAL_H
#define ALGORITHM_INDIVIDUAL_H

namespace lessonplans {
    class Individual {
    public:
        Individual();
        virtual ~Individual();
        virtual bool init() = 0;
    };
}

#endif //ALGORITHM_INDIVIDUAL_H
