#ifndef CLASSNOTES9_CLOCK_H
#define CLASSNOTES9_CLOCK_H
namespace jlr {
    class clock {
    public:

        // CONSTRUCTOR AND DEFAULT CONSTRUCTOR (is both)
        clock(int h = 0, int m = 0, int s = 0, bool morning = true) {
            hour = h;
            minute = m;
            second = s;
            this->morning = morning;
        }

        // PostCondition: Returns the current hour
        int getHour() const { return hour; }

        // PostCondition: Returns the current minute
        int getMin() const { return minute; }

        // PostCondition: Returns the current second
        int getSecond() const { return second; }

        // PostCondition: Returns if it is morning
        bool isMorning() const { return morning; }

        // PostCondition: clock is advanced m minutes
        void advance(int);

    private:
        int hour;
        int minute;
        int second;
        bool morning;
    };
}


#endif