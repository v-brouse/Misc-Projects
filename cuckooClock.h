#include "clock.cpp"

class cuckooClock:public jlr::clock {
public:
    bool isCuckooing() const {return getMin() == 0;}
};
