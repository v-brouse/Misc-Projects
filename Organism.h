#ifndef CLASSNOTES9_ORGANISM_H
#define CLASSNOTES9_ORGANISM_H


class Organism {
public:
    Organism(double s = 1.0, double rate = 0.0) {
        this->size = size;
        this->growRate = growRate;

    }

    double getSize() const {return size;}

    double getRate() const {return growRate;}

    bool isAlive() const {return size == 0;}

    void alterSize(double amount) {size = amount;}

    void death() {size = 0; growRate = 0;}

    void simulateWeek() {
        size += size * growRate;
    }

private:
    double size;
    double growRate;
};


#endif //CLASSNOTES9_ORGANISM_H
