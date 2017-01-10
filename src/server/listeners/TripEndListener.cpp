//
// TripEndListener.
// in charge to update the Passenger's Satisfaction on the Driver at the end of the trip.
// change the driver availability.
//

#include "TripEndListener.h"

/**
 * constructor.
 * @param driver of the listener (to listen to)
 * @param tc of the listener (to update)
 */
TripEndListener::TripEndListener(Driver *driver, TaxiCenter *tc) : driver(driver), tc(tc) {}

/**
 * notify all.
 * if the driver arrived to his end point, add him to the available drivers list.
 * change driver satisfaction.
 */
void TripEndListener::notify() {
    TripInfo *ti = driver->getTi();
    // if there is no trip info dont do a thing.
    if (!ti) {
        return;
    }
    // if the driver reached the end of his road
    if (ti->checkEnd(driver->getCab()->getLocation()->getP())) {
        // traverse the passengers of this trip and update the satisfaaction of the driver
        std::list<Passenger *> *passengers = ti->getPassengers();
        for (std::list<Passenger *>::const_iterator iterator = passengers->begin(),
                     end = passengers->end(); iterator != end; ++iterator) {
            driver->getSatisfaction()->update((*iterator)->generateSatisfaction());
        }

        driver->getCab()->resetKm();    // reset the KmPassed to 0

        // traverse over all the working drivers,find the current driver,
        // move him to the available list
        std::list<Driver *> *drivers = tc->getEmployees();
        std::list<Driver *> tempDrivers;
        Driver *d;
        for (std::list<Driver *>::const_iterator iterator = drivers->begin(),
                     end = drivers->end(); iterator != end; ++iterator) {
            // compare each driver until finding the right one
            if (*(*iterator) == *driver) {
                drivers->pop_front();
                // insert all the drivers from the temp list back to the original
                while (!tempDrivers.empty()) {
                    d = tempDrivers.front();
                    tempDrivers.pop_front();
                    drivers->push_front(d);
                }
                break;
            } else {      // if didn't found the right driver, pop and insert to the temp list
                d = drivers->front();
                drivers->pop_front();
                tempDrivers.push_front(d);
            }
        }
        // push the driver to the available list
        tc->getAvailableDrivers()->push_back(driver);
        delete (ti);               // delete the trip info
        driver->setTi(NULL);       // set the trip info to NULL
    }
}

