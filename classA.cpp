#include <iostream>

class classA {
public:
    void foo1() const {std::cout << "this is foo1 from classA\n";}
    void foo2() const {
        std::cout << "this is foo2 from classA\n";
        foo1();
    }
};