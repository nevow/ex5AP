//
// Taxi - abstract class.
//

#ifndef EX1_TAXI_H
#define EX1_TAXI_H

#include "../enum/Color.h"
#include "../enum/CarManufacture.h"
#include "../coordinates/Node.h"
#include "../coordinates/CoordinatedItem.h"
#include <boost/serialization/base_object.hpp>

class Taxi {

private:
    double tariff;
    Color color;
    CarManufacture firm;
    int kmPassed;
    int id;
    Node *location;

public:

    Taxi() {};

    /**
     * constructor.
     * @param color of the taxi
     * @param firm of the taxi
     * @param id of the taxi
     */
    Taxi(const Color &color, const CarManufacture &firm, int id) :
            color(color), firm(firm), id(id), kmPassed(0) {
        Point p(0, 0);
        location = new Node(&p);
    }

    /**
     * destructor.
     */
    ~Taxi() {
        delete (location);
    };

    /**
     * @return the id of the Taxi.
     */
    int getId() const {
        return id;
    }

    /**
     * @return the location of the taxi
     */
    Node *getLocation() const {
        return location;
    }

    /**
     * abstract method.
     * @param t that needed to set
     */
    virtual void setTariff(double t) {
        tariff = t;
    };

    /**
     * increase the KmPassed at 1.
     */
    void increaseKmPassed() {
        kmPassed++;
    }

    /**
     * reset the KmPassed to 0
     */
    void resetKm() {
        Taxi::kmPassed = 0;
    }

    /**
     * abstract method.
     * @param road that need to follow
     */
    virtual void move(list<CoordinatedItem *> *road) = 0;

    /**
     * @param p the location that the taxi need to get to
     */
    void applyToPoint(Point *p) {
        delete (location->getP());
        location->setP(p);
    }

    /**
     * @param otherTaxi to compare this taxi to
     * @return true if the taxi are the same
     */
    bool operator==(const Taxi &otherTaxi) const {
        return id == otherTaxi.id;
    }

    /**
     * @param otherTaxi to compare this taxi to
     * @return false if the taxi are the same
     */
    bool operator!=(const Taxi &otherTaxi) const {
        return !(otherTaxi == *this);
    }

    /**
     * serialize.
     */
    friend class boost::serialization::access;

    /**
     * serialize function.
     */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & tariff;
        ar & color;
        ar & firm;
        ar & kmPassed;
        ar & id;
        ar & location;
    }
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Taxi);
#endif //EX1_TAXI_H
