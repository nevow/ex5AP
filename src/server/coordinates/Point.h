//
// Point.
// has x and y as coordinates.
//


#ifndef EX1_POINT_H
#define EX1_POINT_H

#include <iostream>
#include "CoordinatedItem.h"
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


using namespace std;
using namespace boost::archive;

class Point {
private:
    int x;
    int y;

public:
    Point() {}

    Point(int x, int y) : x(x), y(y) {};

    ~Point() {}

    int getX();

    int getY();

    void setX(int x);

    void setY(int y);

    void deleteCoords(int **coords);

    friend ostream &operator<<(ostream &output, const Point &p);

    friend istream &operator>>(istream &input, Point &p);

    bool operator==(const Point &otherP) const;

    bool operator!=(const Point &rhs) const;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & x;
        ar & y;
    }

};


#endif //EX1_POINT_H
