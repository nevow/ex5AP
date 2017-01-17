// TCP implementation.
// the class inherit from socket.
// methods of tcp socket type

#include "Tcp.h"

/**
 * creating new Tcp. initialize if server and port_num by the input
 * @param isServers Boolean, true - if server, false if client
 * @param port_num is the port number to get
 */
Tcp::Tcp(bool isServers, int port_num) {
    this->descriptorCommunicateClient = 0;
    this->port_number = port_num;
    this->isServer = isServers;
    this->numberOfClients = 0;
}

/**
 * default destructor
 */
Tcp::~Tcp() {
}

/**
 * initialize the Socket object by getting socket descriptor.
 * bind and accept for servers or connect for clients
 * @param clientsNumber
 * @return int number representing the return status
 */
int Tcp::initialize(int clientsNumber) {
    // getting a socket descriptor and check if legal
    this->socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketDescriptor < 0) {
        // return an error represent error at this method
        return ERROR_SOCKET;
    }
    // if server
    if (this->isServer) {
        this->numberOfClients = clientsNumber;
        //initialize the struct
        struct sockaddr_in sin;
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = INADDR_ANY;
        sin.sin_port = htons(this->port_number);
        bzero(&(sin.sin_zero), 8);
        // bind
        if (::bind(this->socketDescriptor,
                   (struct sockaddr *) &sin, sizeof(sin)) < 0) {
            //return an error represent error at this method
            return ERROR_BIND;
        }
        // listen
        if (listen(this->socketDescriptor, this->numberOfClients) < 0) {
            //return an error represent error at this method
            return ERROR_LISTEN;
        }

        // if client
    } else {
        struct sockaddr_in sin;
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = inet_addr((this->ip_address).c_str());
        sin.sin_port = htons(this->port_number);
        if (connect(this->socketDescriptor,
                    (struct sockaddr *) &sin, sizeof(sin)) < 0) {
            // return an error represent error at this method
            return ERROR_CONNECT;
        }
    }
    // return correct if there were no problem
    return CORRECT;
}

/**
 * sending the required data, using his length and the socket descroptor
 * @param data is string data to send
 * @param descriptor is int number representing the descriptor
 * @return int number representing the return status
 */
int Tcp::sendData(string data, int descriptor) {
    int data_len = data.length() + 1;
    const char *datas = data.c_str();
    int sent_bytes = send(this->isServer ? descriptor
                                         : this->socketDescriptor, datas, data_len, 0);
    if (sent_bytes < 0) {
        // return an error represent error at this method
        return ERROR_SEND;
    }
    // return correct if there were no problem
    return CORRECT;
}


/**
 * getting data from the other socket to, enter it to the buffer and print the data
 * @param buffer the place fot the data
 * @param size the size of the place
 * @param descriptor is int number representing the descriptor
 * @return int number representing the return status
 */
int Tcp::receiveData(char *buffer, int size, int descriptor) {
    int read_bytes = recv(this->isServer ? descriptor
                                         : this->socketDescriptor, buffer, size, 0);
    //checking the errors
    if (read_bytes == 0) {
        return CONNECTION_CLOSED;
    } else if (read_bytes < 0) {
        //return an error represent error at this method
        return ERROR_RECIVE;
    }
    //return correct if there were no problem
    return read_bytes;
}

/**
 * @param data is struct used to transfer data to the thread
 * @return NULL
 */
void *acceptClients(void *data) {
    pthread_mutex_t connection_list_locker;
    pthread_mutex_init(&connection_list_locker, 0);       // lock
    connectionData *cd = (connectionData *) data;
    int connectedClient = 0;
    int amountOfClients = cd->sock->getNumberOfClients();
    // as long there are more clients to get
    while (connectedClient < amountOfClients) {
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        try {
            int descriptorCommunicateClient = accept(cd->sock->getSocketDescriptor(),
                                                     (struct sockaddr *) &client_sin, &addr_len);
            if (descriptorCommunicateClient < 0) {
                // return an error represent error at this method
                cout << "accept didn't return a valid number" << endl;
                break;
            }
            connectedClient++;
            // create new Connection for each client
            Connection *c = new Connection(cd->sock, descriptorCommunicateClient);
            pthread_mutex_lock(&connection_list_locker);        // lock
            cd->connections->push_back(c);
            pthread_mutex_unlock(&connection_list_locker);      // unlock
        } catch (...) {
            cout << "failed to connect" << endl;
        }
    }
    pthread_mutex_destroy(&connection_list_locker);
    return NULL;
}