//
// CoordinatedItem.
// abstract class.
//

#ifndef EX1_COORDINATEDITEM_H
#define EX1_COORDINATEDITEM_H

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
#include <boost/serialization/base_object.hpp>

using namespace boost::archive;

class CoordinatedItem {

private:
    int distance;
    CoordinatedItem *parent;

public:

    /**
     * destructor.
     */
    virtual ~CoordinatedItem() {
        parent = NULL;
    };

    /**
     * @return the CoordinatedItem's parent
     */
    CoordinatedItem *getParent() {
        return parent;
    }

    /**
     * @return the distance value
     */
    int getDistance() {
        return distance;
    }

    /**
     * @param d the distance value to set
     */
    void setDistance(int d) {
        distance = d;
    }

    /**
     * @param c the CoordinatedItem's parent to set
     */
    void setParent(CoordinatedItem *c) {
        parent = c;
    }

    /**
     * abstract method.
     * @return an array of int that represent the coordinate, depend the grid dimensions
     */
    virtual int **getCoordinates() = 0;

    /**
     * abstract method, needed after use in getCoordinates method.
     * @param coords to delete.
     */
    virtual void deleteCoords(int **coords) = 0;

    /**
     * boost.
     */
    friend class boost::serialization::access;

    /*
     * serialization.
     */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & distance;
        ar & parent;
    }
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(CoordinatedItem);

#endif //EX1_COORDINATEDITEM_H
