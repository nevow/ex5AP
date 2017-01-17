// TCP header file. the class inherit from socket
// methods of tcp socket type

#ifndef TCP_H_
#define TCP_H_

#include <vector>
#include "Socket.h"
#include "Connection.h"
#include <list>

class Tcp : public Socket {

private:
    int descriptorCommunicateClient;

public:

    Tcp(bool isServers, int port_num);

    virtual ~Tcp();

    int initialize(int clientsNumber);

    int sendData(string data, int descriptor);

    int receiveData(char *buffer, int size, int descriptor);
};

void *acceptClients(void *data);

/**
 * struct used to transfer data to the thread
 */
struct connectionData {
    Socket *sock;
    std::list<Connection *> *connections;
};

#endif /* TCP_H_ */
