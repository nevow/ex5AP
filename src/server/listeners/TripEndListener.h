//
// TripEndListener.
//

#ifndef EX1_TRIPENDLISTENER_H
#define EX1_TRIPENDLISTENER_H


#include "EventListener.h"
#include "../tripOperations/Driver.h"
#include "../tripOperations/TripInfo.h"
#include "../tripOperations/TaxiCenter.h"
#include <list>

using namespace std;

class TripEndListener : public EventListener {

private:
    Driver *driver;
    TaxiCenter *tc;
public:

    TripEndListener(Driver *driver, TaxiCenter *tc);

    void notify();

};


#endif //EX1_TRIPENDLISTENER_H
