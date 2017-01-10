//
// Cab.
// inherit Taxi.

#include "Cab.h"

/**
 * @param t is the tariff of the taxi
 */
void Cab::setTariff(double t) {
    Taxi::setTariff(t);
}

/**
 * @param road to move the cab according to
 */
void Cab::move(std::list<CoordinatedItem *> *road) {
    if (!road->empty()) {
        CoordinatedItem *item = road->front();
        road->pop_front();
        int **coords = item->getCoordinates();
        Point p(*(coords[0]), *(coords[1]));
        applyToPoint(&p);
        p.deleteCoords(coords);
        increaseKmPassed();
    }
}

BOOST_CLASS_EXPORT(Cab)
