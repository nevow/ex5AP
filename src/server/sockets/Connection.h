//
// Connection.
//

#ifndef EX5AP_CONNECTION_H
#define EX5AP_CONNECTION_H


#include <sys/types.h>
#include "Socket.h"
#include "../managment/DataSender.cpp"

extern pthread_mutex_t global_validator_locker;

class Connection {

private:

    Socket *sock;
    pthread_t t;
    int *option;
    int descriptor;

public:

    Connection(Socket *s, int dcc) : sock(s), descriptor(dcc), option(NULL) {};

    ~Connection() {
        pthread_join(t, NULL);
        pthread_mutex_destroy(&global_validator_locker);
    }

    void setOption(int *status);

    template<class T>
    void sendData(T *item) {
        DataSender<T>::sendData(sock, item, descriptor);
    }

    template<class T>
    T *receiveData() {
        return DataSender<T>::receiveData(sock, descriptor);
    }

    void send(string c);

    char *receive(char *c, int size);

};

static void *sendInfoToClient(void *status);

#endif //EX5AP_CONNECTION_H
