//
// Cab.
// inherit Taxi.

#ifndef EX1_CAB_H
#define EX1_CAB_H


#include "Taxi.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>

class Cab : public Taxi {

public:

    Cab() {};

    Cab(const Color &color, const CarManufacture &firm, int id) : Taxi(color, firm, id) {}

    void setTariff(double t);

    void move(list<CoordinatedItem *> *road);

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Taxi>(*this);
    }
};

#endif //EX1_CAB_H
