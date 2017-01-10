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
        // if we didn't got to the end of the road - move to the next CoordinatedItem
        if (!road->empty()) {
            item = road->front();
            road->pop_front();
            increaseKmPassed();
        }
        int **coords = item->getCoordinates();
        Point p(*(coords[0]), *(coords[1]));
        applyToPoint(&p);
        p.deleteCoords(coords);
        increaseKmPassed();

    }
}

/**
 * @param t is the tariff of the LuxuryCab
 */
void LuxuryCab::setTariff(double t) {
    Taxi::setTariff(t * 2);
}

BOOST_CLASS_EXPORT(LuxuryCab)
