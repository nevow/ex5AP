//
// DataSender.
//

#ifndef EX4AP_DATASENDER_H
#define EX4AP_DATASENDER_H

#include "../sockets/Socket.h"
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

template<class T>
class DataSender {

public:

    static void sendData(Socket *sock, T *item);

    static T *receiveData(Socket *sock);
};


#endif //EX4AP_DATASENDER_H
