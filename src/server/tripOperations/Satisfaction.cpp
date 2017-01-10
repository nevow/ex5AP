//
// Satisfaction.
//

#include "Satisfaction.h"

/**
 * constructor.
 */
Satisfaction::Satisfaction() {
    amount = 0;
    average = 0;
}

/**
 * copy constructor.
 */
Satisfaction::Satisfaction(Satisfaction *s) {
    amount = s->amount;
    average = s->average;
}

/**
 * @return the average satisfaction.
 */
double Satisfaction::getAverage() const {
    return average;
}

/**
 * @param grade to add to the average grade.
 * if the grade is above 5 or below 1, dont do a thing
 */
void Satisfaction::update(int grade) {
    if ((grade > 0) && (grade <= 5)) {
        average = ((average * amount) + grade) / (amount + 1);
        amount++;
    }
}

