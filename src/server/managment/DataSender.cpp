//
// DataSender.
//

#include "DataSender.h"

/**
 * @tparam T type of item
 * @param sock socket to transfer the data with
 * @param item to send using the socket
 * @param descriptor identify the client
 */
template<class T>
void DataSender<T>::sendData(Socket *sock, T *item, int descriptor) {
    std::string serial_str;
    {
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::
        back_insert_device<std::string>> s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << item;
        s.flush();
    }
    sock->sendData(serial_str, descriptor);
}

/**
 * @tparam T type of item
 * @param sock socket to transfer the data with
 * @param descriptor identify the client
 * @return the T item received
 */
template<class T>
T *DataSender<T>::receiveData(Socket *sock, int descriptor) {
    char buffer[70000];
    sock->receiveData(buffer, sizeof(buffer), descriptor);
    T *item;
    {
        boost::iostreams::basic_array_source<char> dev(buffer, sizeof(buffer));
        boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s2(dev);
        boost::archive::binary_iarchive ia(s2);
        ia >> item;
    }
    return item;
}