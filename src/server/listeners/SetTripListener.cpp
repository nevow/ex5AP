//
// SetTripListener.
//

#include "SetTripListener.h"

/**
 * constructor.
 * @param trip is a list of trip info
 * @param availDrivers is a list of availDrivers
 * @param tc is the Taxi Center
 */
SetTripListener::SetTripListener(
        std::list<TripInfo *> *trip, std::list<Driver *> *availDrivers,
        TaxiCenter *tc) : trips(trip), availableDrivers(availDrivers), taxiCenter(tc) {};

/**
 * set the trip info that match the current clock to the Closest Driver.
 */
void SetTripListener::notify() {
    // set the trip that match the clock to the Closest Driver.
    while ((!(trips->empty())) && (!(availableDrivers->empty()))) {
        TripInfo *ti = taxiCenter->getUrgentTi();
        // if there is a trip info
        if (ti != NULL) {
            taxiCenter->setDriverToTi(ti);
        } else {
            return;
        }
    }
};
