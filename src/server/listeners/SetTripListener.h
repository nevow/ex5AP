//
// SetTripListener.
//

#ifndef EX4AP_MATCHTRIPTODRIVERLISTENER_H
#define EX4AP_MATCHTRIPTODRIVERLISTENER_H

#include "EventListener.h"
#include "../tripOperations/TaxiCenter.h"
#include <list>

class SetTripListener : public EventListener {
private:
    list<TripInfo *> *trips;
    list<Driver *> *availableDrivers;
    TaxiCenter *taxiCenter;
public:
    SetTripListener(list<TripInfo *> *trip, list<Driver *> *availDrivers, TaxiCenter *tc);

    void notify();

};


#endif //EX4AP_MATCHTRIPTODRIVERLISTENER_H
