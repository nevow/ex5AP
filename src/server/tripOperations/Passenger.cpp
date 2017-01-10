//
// Passenger.
//

#include "Passenger.h"

/**
 * @param start point of this passenger trip
 * @param destination point of this passenger trip
 */
Passenger::Passenger(Point *start, Point *destination) : start(start), destination(destination) {}

/**
 * @return a random number between 1 to 5 (for now)
 */
int Passenger::generateSatisfaction() {
    return (rand() % 5) + 1;
}
