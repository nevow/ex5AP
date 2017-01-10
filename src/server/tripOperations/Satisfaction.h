//
// Satisfaction.
//

#ifndef EX1_SATISFACTION_H
#define EX1_SATISFACTION_H

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

class Satisfaction {
private:
    int amount;
    double average;
public:
    Satisfaction();

    Satisfaction(Satisfaction *s);

    double getAverage() const;

    void update(int grade);

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & amount;
        ar & average;
    }
};


#endif //EX1_SATISFACTION_H
