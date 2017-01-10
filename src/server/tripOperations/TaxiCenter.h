//
// TaxiCenter.
//

#ifndef EX1_TAXICENTER_H
#define EX1_TAXICENTER_H


#include <list>
#include "Driver.h"
#include "../coordinates/Point.h"
#include "Passenger.h"
#include "../listeners/EventListener.h"
#include "../sockets/Socket.h"
#include "../sockets/Udp.h"

using namespace std;

class TaxiCenter {

private:

    list<Driver *> *employees;
    list<Node *> *locations;
    list<Taxi *> *cabs;
    list<TripInfo *> *trips;
    list<Driver *> *availableDrivers;
    list<EventListener *> *listeners;
    Socket *socket;
    int clock;

public:

    TaxiCenter(list<Driver *> *employees, list<Node *> *locations, list<Taxi *> *cabs,
               list<TripInfo *> *trips)
            : employees(employees), locations(locations), cabs(cabs), trips(trips),
              availableDrivers(employees), clock(0) {}

    TaxiCenter(Socket *sock);

    ~TaxiCenter();

    list<Driver *> *getEmployees() const;

    list<Driver *> *getAvailableDrivers() const;

    Point *getDriverLocation(int id);

    Taxi *getTaxiByID(int id);

    Driver *getClosestDriver(Point *start);

    void addDriver(Driver *d);

    void addTaxi(Taxi *cab);

    void addTI(TripInfo *ti);

    TripInfo *getUrgentTi();

    void setDriverToTi(TripInfo *ti);

    void moveAll();

    //void removeListener(EventListener *el);

    //TripInfo *answerCall(Passenger *p);

    //void sendTaxi(Driver *d);
};


#endif //EX1_TAXICENTER_H
