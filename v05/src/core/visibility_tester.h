#ifndef VISIBILITY_TESTER_H
#define VISIBILITY_TESTER_H

#include "surfel.h"
#include "scene.h"

class VisibilityTester {

    public:
        Surfel *objectContact, *lightContact;
        VisibilityTester()=default;

        // eh consturido com os dois surfel
        VisibilityTester(const Surfel& obj, const Surfel& light);

        // vai iterar por todos objs ta cena vendo se tem contato
        bool unoccluded(Scene& scene);

        void copy_from(const VisibilityTester* other);
};

#endif