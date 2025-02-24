// Polymorphism, Polymorphism Principle, and Inheritance
#include <iostream>
#include "clock.cpp"
#include "cuckooClock.h"
#include "clock24.cpp"
#include "Organism.cpp"
#include "Animal.h"
#include "classB.cpp"

using namespace std;
using namespace jlr;

int main() {

    // note, must use jlr:: since clock() is a function of time.h, must specify our clock
    jlr::clock c1(2, 30, 35);

    cout << c1.getHour() << ":" << c1.getMin() << "." << c1.getSecond() << " ";
    if (c1.isMorning()) {
        cout << "am" << endl;
    } else {
        cout << "pm" << endl;
    }

    jlr::clock* c2;
    c2 = new jlr::clock(2, 30, 35, false);
    c2->advance(350);
    // note the above use of a ternary operator
    cout << c2->getHour() << " o'clock in the " <<
        (c2->isMorning()? "morning.":"afternoon.") << endl;

    cuckooClock c3;
    cout << "is cucking? " << (c3.isCuckooing()? "Yes.":"No.") << endl;

    // polymorphism, you can declare a dynamic cuckooClock object through a clock
    // pointer variable
    jlr::clock* c4 = new cuckooClock();

    clock24 c5;
    cout << c5.getHour() << endl;


    jlr::clock* c6 = new clock24(); // polymorphism is NOT applied here
    cout << c6->getHour() << endl; // which getHour is called?

    Organism* spot = new Organism(2, 3);
    for (int i = 0; i < 5; ++i) {
        cout << "At week " << i << ", spot weighs " << spot->getSize() << " ounces.\n";
        spot->simulateWeek();
    }

    Animal* spot2 = new Animal(2, 3, 1);
    cout << "spot needs to eat " << spot2->getNeed() << " ounces each week\n";

    classB* cb = new classB();
    cb->foo2();

    return 0;
}

