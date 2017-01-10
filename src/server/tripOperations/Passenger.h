//
// Passenger.
//

#ifndef EX1_PASSENGER_H
#define EX1_PASSENGER_H


#include "../coordinates/Point.h"

class Passenger {
private:
    Point *start;
    Point *destination;

public:
    Passenger() {};

    Passenger(Point *start, Point *destination);

    int generateSatisfaction();

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & start;
        ar & destination;
    }
};


#endif //EX1_PASSENGER_H
