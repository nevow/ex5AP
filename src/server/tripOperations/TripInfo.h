//
// TripInfo.
//

#ifndef EX1_TRIPINFO_H
#define EX1_TRIPINFO_H


#include <stack>
#include <list>
#include "../coordinates/Point.h"
#include "Passenger.h"
#include <boost/serialization/list.hpp>


class TripInfo {

private:

    int rideId;
    int currentDistance;
    Point *start;
    Point *destination;
    int amountOfPassengers;
    list<Passenger *> *passengers;
    list<CoordinatedItem *> *road;
    double tariff;
    int tripTime;

public:

    TripInfo() {};

    TripInfo(int rideId, Point *start, Point *destination,
             int amountOfPassengers, double tariff, int tripTime);

    ~TripInfo() {
        while (!passengers->empty()) {
            delete (passengers->front());
            passengers->pop_front();
        }
        delete (passengers);

        delete road;
        delete start;
        delete destination;
    }

    int getRideId() const;

    Point *getStart() const;

    Point *getDestination() const;

    int getTripTime() const;

    list<CoordinatedItem *> *getRoad();

    double getTariff() const;

    int getAmountOfPassengers() const;

    list<Passenger *> *getPassengers() const;

    void setRoad(list<CoordinatedItem *> *road);

    bool checkEnd(Point *location);

    bool operator==(const TripInfo &ti) const;

    bool operator!=(const TripInfo &ti) const;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & rideId;
        ar & currentDistance;
        ar & start;
        ar & destination;
        ar & amountOfPassengers;
        ar & passengers;
        ar & road;
        ar & tariff;
        ar & tripTime;
    }
};

#endif //EX1_TRIPINFO_H

