//
// LuxuryCab.
// inherit Taxi.

#include "LuxuryCab.h"

/**
 * LuxuryCab move twice faster that cab.
 * @param road to move the cab according to
 */
void LuxuryCab::move(std::list<CoordinatedItem *> *road) {
    if (!road->empty()) {
        CoordinatedItem *item = road->front();
        road->pop_front();
        // if we didn't got to the end of the road - skip on one CoordinatedItem, for double step
        if (!road->empty()) {
            item = road->front();
            road->pop_front();
            increaseKmPassed();                 // increase the km passed at 1
        }
        int **coords = item->getCoordinates();
        Point p(*(coords[0]), *(coords[1]));
        applyToPoint(&p);                       // move the car to the next point
        p.deleteCoords(coords);
        increaseKmPassed();                     // increase the km passed at 1
    }
}

/**
 * the tariff of LuxuryCab is twicer cab.
 * @param t is the tariff of the LuxuryCab
 */
void LuxuryCab::setTariff(double t) {
    Taxi::setTariff(t * 2);
}

BOOST_CLASS_EXPORT(LuxuryCab)
