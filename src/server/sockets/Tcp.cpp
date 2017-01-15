/************************************************************
* File description: TCP implementation.						*
* the class inherit from socket. 							*
* methods of tcp socket type								*
************************************************************/

#include "Tcp.h"

/***********************************************************************
* function name: Tcp												   *
* The Input: Boolean, true - if server, false if client	and port number*
* The output: none										               *
* The Function operation: creating new Tcp. initialize if server and   *
* port_num by the input												   *
***********************************************************************/
Tcp::Tcp(bool isServers, int port_num) {
    this->descriptorCommunicateClient = 0;
    this->port_number = port_num;
    this->isServer = isServers;
    this->numberOfClients = 0;
}

/***********************************************************************
* function name: ~Tcp												   *
* The Input: none													   *
* The output: none										               *
* The Function operation: default destructor					       *
***********************************************************************/
Tcp::~Tcp() {
}

/***********************************************************************
* function name: initialize											   *
* The Input: none              										   *
* The output: int number representing the return status		           *
* The Function operation: initialize the Socket object by getting	   *
* socket descriptor. bind and accept for servers or connect for clients*
***********************************************************************/
int Tcp::initialize(int clientsNumber) {
    //getting a socket descriptor and check if legal
    this->socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketDescriptor < 0) {
        //return an error represent error at this method
        return ERROR_SOCKET;
    }
    //if server
    if (this->isServer) {
        this->numberOfClients = clientsNumber;
        //initialize the struct
        struct sockaddr_in sin;
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = INADDR_ANY;
        sin.sin_port = htons(this->port_number);
        bzero(&(sin.sin_zero), 8);
        //bind
        if (::bind(this->socketDescriptor,
                   (struct sockaddr *) &sin, sizeof(sin)) < 0) {
            //return an error represent error at this method
            return ERROR_BIND;
        }
        //listen
        if (listen(this->socketDescriptor, this->numberOfClients) < 0) {
            //return an error represent error at this method
            return ERROR_LISTEN;
        }

        //if client
    } else {
        struct sockaddr_in sin;
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = inet_addr((this->ip_address).c_str());
        sin.sin_port = htons(this->port_number);
        if (connect(this->socketDescriptor,
                    (struct sockaddr *) &sin, sizeof(sin)) < 0) {
            //return an error represent error at this method
            return ERROR_CONNECT;
        }
    }
    //return correct if there were no problem
    return CORRECT;
}

/***********************************************************************
* function name: sendData											   *
* The Input: string data to send									   *
* The output: int number representing the return status		           *
* The Function operation: sending the required data, using his length  *
* and the socket descroptor											   *
***********************************************************************/
int Tcp::sendData(string data, int descriptor) {
    int data_len = data.length() + 1;
    const char *datas = data.c_str();
    int sent_bytes = send(this->isServer ? descriptor
                                         : this->socketDescriptor, datas, data_len, 0);
    if (sent_bytes < 0) {
        //return an error represent error at this method
        return ERROR_SEND;
    }
    //return correct if there were no problem
    return CORRECT;
}

/***********************************************************************
* function name: recive	`											   *
* The Input: none										               *
* The output: int number representing the return status	               *
* The Function operation: getting data from the other socket to,	   *
* enter it to the buffer and print the data							   *
***********************************************************************/
int Tcp::receiveData(char *buffer, int size, int descriptor) {
    int read_bytes = recv(this->isServer ? descriptor
                                         : this->socketDescriptor, buffer, size, 0);
    //checking the errors
    if (read_bytes == 0) {
        return CONNECTION_CLOSED;
    } else if (read_bytes < 0) {
        //return an error represent error at this method
        return ERROR_RECIVE;
    } else {
        //prinrting the massege
//		cout<<buffer<<endl;
    }
    //return correct if there were no problem
    return read_bytes;
}

void *acceptClients(void *data) {
    pthread_mutex_t connection_list_locker;
    pthread_mutex_init(&connection_list_locker, 0);
    connectionData *cd = (connectionData *) data;
    int connectedClient = 0;
    int amountOfClients = cd->sock->getNumberOfClients();
    //accept
    while (connectedClient < amountOfClients) {
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        try {
            int descriptorCommunicateClient = accept(cd->sock->getSocketDescriptor(),
                                                     (struct sockaddr *) &client_sin, &addr_len);
            if (descriptorCommunicateClient < 0) {
                //return an error represent error at this method
                cout << "accept didn't return a valid number" << endl;
                break;
            }
            connectedClient++;
            Connection *c = new Connection(cd->sock, descriptorCommunicateClient);
            pthread_mutex_lock(&connection_list_locker);
            cd->connections->push_back(c);
            pthread_mutex_unlock(&connection_list_locker);
        } catch (...) {
            cout << "failed to connect" << endl;
        }
    }
    pthread_mutex_destroy(&connection_list_locker);
    return NULL;
}