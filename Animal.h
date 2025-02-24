#ifndef CLASSNOTES9_ANIMAL_H
#define CLASSNOTES9_ANIMAL_H

#include "Organism.h"

namespace jlr {
    class Animal:public Organism {
    public:
        Animal(double s = 1, double rate = 0, double need = 0) {
            Organism(s, rate);
            needEachWeek = need;
        }

        /* This is an additional way to write the above
        Animal (double s = 2, double rate = 3, double need = 0):Organism(s, rate),
        needEachWeek() {

        }
         */

        double getNeed() {return needEachWeek;}

    private:
        double needEachWeek;
        double eatenThisWeek;
    };
}


#endif
