//
// MainFlow.
//

#ifndef EX1_MAINFLOW_H
#define EX1_MAINFLOW_H

#include <list>

#include "SystemOperations.h"
#include "../enum/ColorFactory.h"
#include "../enum/CarManufactureFactory.h"
#include "../taxi/LuxuryCab.h"
#include "ProperInput.h"
#include "../sockets/Udp.h"
#include "../taxi/Cab.h"
#include "../taxi/LuxuryCab.h"

class MainFlow {

private:
    SystemOperations *so;
    Socket *sock;

public:

    MainFlow(int ip);

    ~MainFlow() {
        delete so;
        delete sock;
    }

    void input();
};


#endif //EX1_MAINFLOW_H
