// Socket class header file.
// contains socket properties as members, declaration on methods,
// and const numbers using by all classes which inherit from Socket class

#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

//return values to each function if error happened
#define CORRECT 0
#define ERROR_SOCKET 1
#define ERROR_BIND 2
#define ERROR_LISTEN 3
#define ERROR_CONNECT 4
#define ERROR_SEND 5
#define ERROR_RECIVE 6
#define ERROR_ACCEPT 7
#define CONNECTION_CLOSED 8

#define IP "127.0.0.1"


class Socket {

protected:
    //true is the socket is for a server, false if for a client
    bool isServer;
    //the socket descriptor return from sock()
    int socketDescriptor;
    //ip address
    string ip_address;
    int backLog;
    //port number
    int port_number;

public:

    /**
     * creating new Socket object, with the computer ip,
     * and no port number and socket descriptor, 0 backlogs.
     */
    Socket();

    /**
     * default destructor
     */
    virtual ~Socket();

    /**
     * pure virtual method.
     * initialize the Socket object and getting a socket descriptor.
     * @return int number representing the return status
     */
    virtual int initialize() = 0;

    /**
     * pure virtual method.
     * sending the input data to the socket who connect to this socket.
     * @param data is the string representing the data to send
     * @return int number representing the return status
     */
    virtual int sendData(string data) = 0;

    /**
     * getting data from the other socket and print the data
     * @param buffer is string representing the data that has been send.
     * @param size is the size of the data
     * @return int number representing the return status
     */
    virtual int receiveData(char *buffer, int size) = 0;
};

#endif /* SOCKET_H_ */
