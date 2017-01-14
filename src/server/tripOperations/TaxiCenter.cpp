//
// TaxiCenter.
//

#include <map>
#include "TaxiCenter.h"
#include "../listeners/TripEndListener.h"
#include "../listeners/SetTripListener.h"

extern std::map<int, pthread_t> computeRoadT;

/**
 * consturctor.
 * @param sock is the socket of the driver
 */
TaxiCenter::TaxiCenter(map<int, Connection *> *cm) : conMap(cm) {
    employees = new list<Driver *>();
    locations = new list<Node *>();
    cabs = new list<Taxi *>();
    trips = new list<TripInfo *>();
    availableDrivers = new list<Driver *>();
    listeners = new list<EventListener *>();
    EventListener *el = new SetTripListener(trips, availableDrivers, this);
    listeners->push_front(el);
}

/**
 * destructor.
 */
TaxiCenter::~TaxiCenter() {
    // delete the employees list
    while (!employees->empty()) {
        delete (employees->front());
        employees->pop_front();
    }
    delete (employees);

    // delete the locations list
    while (!locations->empty()) {
        delete (locations->front());
        locations->pop_front();
    }
    delete (locations);

    // delete the cabs list
    while (!cabs->empty()) {
        delete (cabs->front());
        cabs->pop_front();
    }
    delete (cabs);

    // delete the trips list
    while (!trips->empty()) {
        delete (trips->front());
        trips->pop_front();
    }
    delete (trips);

    // delete the availableDrivers list
    while (!availableDrivers->empty()) {
        delete (availableDrivers->front());
        availableDrivers->pop_front();
    }
    delete (availableDrivers);

    // delete the listeners list
    while (!listeners->empty()) {
        delete (listeners->front());
        listeners->pop_front();
    }
    delete (listeners);
}

/**
 * @return the working drivers list.
 */
list<Driver *> *TaxiCenter::getEmployees() const {
    return employees;
}

/**
 * @return get the available drivers list.
 */
list<Driver *> *TaxiCenter::getAvailableDrivers() const {
    return availableDrivers;
}

/**
 * @param id of the driver
 * @return the location of the driver
 */
Point *TaxiCenter::getDriverLocation(int id) {
    // search the driver at the employees list
    if (!employees->empty()) {
        for (std::list<Driver *>::const_iterator iterator = employees->begin(),
                     end = employees->end(); iterator != end; ++iterator) {
            if ((*iterator)->getId() == id) {
                return (*iterator)->getCab()->getLocation()->getP();
            }
        }
    }
    // search the driver at the availableDrivers list
    if (!availableDrivers->empty()) {
        for (std::list<Driver *>::const_iterator iterator = availableDrivers->begin(),
                     end = availableDrivers->end(); iterator != end; ++iterator) {
            if ((*iterator)->getId() == id) {
                return (*iterator)->getCab()->getLocation()->getP();
            }
        }
    }
    return NULL;
}

/**
 * @param id of the taxi
 * @return the taxi
 */
Taxi *TaxiCenter::getTaxiByID(int id) {
    for (std::list<Taxi *>::const_iterator iterator = cabs->begin(),
                 end = cabs->end(); iterator != end; ++iterator) {
        if ((*iterator)->getId() == id) {
            return *iterator;
        }
    }
    return NULL;
}

/**
 * @param start point of the trip
 * @return the closest driver to that point, remove him from the list
 */
Driver *TaxiCenter::getClosestDriver(Point *start) {
    std::list<Driver *> temp;
    Driver *d;
    while (!availableDrivers->empty()) {
        d = availableDrivers->front();     // temp driver to check
        availableDrivers->pop_front();
        // if the start point match to the one of the temp driver
        if (*(d->getCab()->getLocation()->getP()) == *start) {
            // return all drivers from the temp list to the available list
            while (!temp.empty()) {
                availableDrivers->push_front((temp.front()));
                temp.pop_front();
            }
            // return the driver
            return d;
        } else {
            // else, push the temp driver to the temp list
            temp.push_front(d);
        }
    }
    // return all the drivers from the temp list to availableDrivers list
    while (!temp.empty()) {
        availableDrivers->push_front((temp.front()));
        temp.pop_front();
    }
    // if no driver has been found return null
    return NULL;
}

/**
 * @param d driver to add to the employees list.s
 */
void TaxiCenter::addDriver(Driver *d) {
    listeners->push_back(new TripEndListener(d, this));
    availableDrivers->push_back(d);
}

/**
 * search the trip info in the trips list that start at the current time and return it.
 * @return the tripInfo that found, if there isn't - return null
 */
TripInfo *TaxiCenter::getUrgentTi() {
    TripInfo *tripInfo = NULL;
    if (!(trips->empty())) {
        // search the earliest trip info and save a pointer to him
        for (std::list<TripInfo *>::const_iterator iterator = trips->begin(),
                     end = trips->end(); iterator != end; ++iterator) {
            if ((*iterator)->getTripTime() == clock) {
                tripInfo = (*iterator);
                break;
            }
        }
        // move all the trips info to the back of the list, until it's match to the one we found.
        if (tripInfo != NULL) {
            TripInfo *temp = trips->front();
            trips->pop_front();
            while (*temp != *tripInfo) {
                trips->push_back(temp);
                temp = trips->front();
                trips->pop_front();
            }
        }
    }
    return tripInfo;
}

/**
 * @param cab to add to the cabs list.
 */
void TaxiCenter::addTaxi(Taxi *cab) {
    cabs->push_back(cab);
}

/**
 * @param ti to add to the trips list.
 */
void TaxiCenter::addTI(TripInfo *ti) {
    trips->push_back(ti);
}

/**
 * @param ti trip info to assign to the driver.
 */
void TaxiCenter::setDriverToTi(TripInfo *ti) {
    // get the closest available driver, assign him with the trip info.
    Driver *d = getClosestDriver(ti->getStart());
    // wait for the thread that compute the rode of the trip info
    pthread_join(computeRoadT[ti->getRideId()], NULL);
    d->setTi(ti);
    Connection *c = (*conMap)[d->getId()];

    // tell the client that his getting trip info
    c->send("get_ready_for_trip_info");
    char buffer[50];
    // receive from the client that his ready
    c->receive(buffer, sizeof(buffer));

    // send the trip info to the client
    c->sendData<TripInfo>(ti);
    // receive confirm from the client
    c->receive(buffer, sizeof(buffer));

    // put the driver at the employees list
    employees->push_back(d);
}

/**
 * iterate over all the drivers and tell them to move.
 */
void TaxiCenter::moveAll() {
    listeners->front()->notify();
    ++clock;
    // iterate over all drivers tell them to move.
    for (std::list<Driver *>::const_iterator iterator = employees->begin(),
                 end = employees->end(); iterator != end; ++iterator) {
        (*iterator)->moveOneStep();
    }
    // tell all listener to notify.
    for (std::list<EventListener *>::const_iterator iterator = listeners->begin(),
                 end = listeners->end(); iterator != end; ++iterator) {
        (*iterator)->notify();
    }
}

