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

    /*template<class Archive>
    void save(Archive &ar, const unsigned int version) const {
        ar & rideId;
        ar & currentDistance;
        ar & start;
        ar & destination;
        ar & amountOfPassengers;
        ar & passengers;
        int size = 0;
        std::stack<CoordinatedItem *> temp;
        while (!(road->empty())) {
            temp.push((road->top()));
            road->pop();
            size++;
        }
        ar & size;
        while (!(temp.empty())) {
            CoordinatedItem *item = temp.top();
            road->push(item);
            ar & item;
            temp.pop();
        }
        ar & tariff;
        ar & tripTime;
    }

    template<class Archive>
    void load(Archive &ar, const unsigned int version) {
        ar & rideId;
        ar & currentDistance;
        ar & start;
        ar & destination;
        ar & amountOfPassengers;
        ar & passengers;
        int size = 0;
        CoordinatedItem *item;
        ar & size;
        std::stack<CoordinatedItem *> temp;
        for (int i = 0; i < size; i++) {
            ar & item;
            temp.push(item);
        }
        while (!(temp.empty())) {
            road->push((temp.top()));
            temp.pop();
        }
        ar & tariff;
        ar & tripTime;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()*/

};

#endif //EX1_TRIPINFO_H

