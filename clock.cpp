#include "clock.h"

namespace jlr {

    void clock::advance(int m) {
        int newMinute = minute + m;
        minute = newMinute % 60;
        int newHour = hour + newMinute / 60;
        hour = newHour % 12;

        if((newHour / 12) % 2 != 0) {
            morning != morning;
        }
    }

}
