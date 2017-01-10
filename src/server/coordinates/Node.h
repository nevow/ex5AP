//
// Node.
// inherit CoordinatedItem, has a point.
//

#ifndef EX1_NODE_H
#define EX1_NODE_H

#include "Point.h"
#include "CoordinatedItem.h"
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

class Node : public CoordinatedItem {
private:
    Point *p;

public:
    Node() {};

    Node(Point *point) : p(new Point(point->getX(), point->getY())) {
        setDistance(-1);
    }

    ~Node() {
        delete (p);
    }

    Point *getP();

    void setP(Point *p);

    void deleteCoords(int **coords);

    int **getCoordinates();

    bool operator==(const Node &otherNode) const;

    bool operator!=(const Node &rhs) const;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<CoordinatedItem>(*this);
        ar & p;
    }
};

#endif //EX1_NODE_H
