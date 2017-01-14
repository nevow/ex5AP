//
// MainFlow.
//

#ifndef EX1_MAINFLOW_H
#define EX1_MAINFLOW_H

#include <list>
#include <map>

#include "SystemOperations.h"
#include "../enum/ColorFactory.h"
#include "../enum/CarManufactureFactory.h"
#include "../taxi/LuxuryCab.h"
#include "ProperInput.h"
#include "../taxi/Cab.h"
#include "../taxi/LuxuryCab.h"
#include "../sockets/Tcp.h"

class MainFlow {

private:

    SystemOperations *so;
    Socket *sock;
    list<Connection *> *connections;
    pthread_t connection_thread;
    map<int, Connection *> *conMap;
    int *choice;

public:

    MainFlow(int port);

    ~MainFlow() {
        delete so;
        delete conMap;
        while (!(connections->empty())) {
            delete connections->front();
            connections->pop_front();
        }
        delete connections;
        delete sock;
        delete choice;
    }

    void input();
};


#endif //EX1_MAINFLOW_H
