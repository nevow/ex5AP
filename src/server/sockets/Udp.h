//
// UDP header file. the class inherit from socket.
// methods of udp socket type
//

#ifndef UDP_H_
#define UDP_H_

#include "Socket.h"

class Udp : public Socket {

public:

    /**
     * creating new Udp socket.
     * @param isServers  true - if server, false if client
     * @param port_num is the port number
     */
    Udp(bool isServers, int port_num);

    /**
     * default destructor
     */
    virtual ~Udp();

    /**
     * initialize the Socket object by using socket(), and bind() if server
     * @return int number representing the return status
     */
    int initialize();

    /**
     * sending the input data to the socket who connect to this socket,check if send successfully.
     * @param data to send
     * @return int number representing the return status
     */
    int sendData(string data);

    /**
     * getting data from the other socket check if there were no error receiving and print
     * @param buffer is string representing the data that has been send.
     * @param size is the size of the data
     * @return int number representing the return status
     */
    int receiveData(char *buffer, int size);
};

#endif /* UDP_H_ */
