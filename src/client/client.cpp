//
// client.
//

#include "../server/sockets/Udp.h"
#include "../server/managment/ProperInput.h"
#include "../server/tripOperations/Driver.h"
#include "../server/enum/MartialStatuesFactory.h"
#include "../server/managment/DataSender.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    // put the port
    int portNumber = atoi(argv[2]);
    // create a socket for transferring data between the server and the client
    Socket *sock = new Udp(0, portNumber);
    sock->initialize();

    // get a driver with user input
    int id, age, experience, vehicleId;
    char trash, status;
    id = ProperInput::validInt();
    cin >> trash;
    age = ProperInput::validInt();
    cin >> trash >> status >> trash;
    experience = ProperInput::validInt();
    cin >> trash;
    vehicleId = ProperInput::validInt();
    cin.ignore();
    char buffer[50];

    // create a driver with the user input
    Driver *driver = new Driver(id, age, MartialStatuesFactory::getMartialStatus(status),
                                experience, vehicleId, portNumber);
    // serialize and send the driver
    DataSender<Driver>::sendData(sock, driver);

    // deserialize the taxi from the server
    Taxi *cab = DataSender<Taxi>::receiveData(sock); // wait to receive a cab from the server
    driver->setCab(cab);                             // set the cab to the driver

    TripInfo *ti = NULL;
    std::list<CoordinatedItem *> *tempRoad = NULL;   // to save the road of  the trip info
    // do while the server still sends orders different from the exit order "exit"
    do {
        sock->receiveData(buffer, sizeof(buffer));   // wait to receive the orders from the server
        if (!strcmp(buffer, "get_ready_for_trip_info")) {
            sock->sendData("waiting_for_trip");      // tell the server that the client is waiting

            // deserialize the trip info from the server
            ti = DataSender<TripInfo>::receiveData(sock);
            tempRoad = new list<CoordinatedItem *>;
            std::list<CoordinatedItem *> *road = ti->getRoad();
            // pass the coordinated items of the road to the tempRoad
            for (std::list<CoordinatedItem *>::const_iterator iterator = road->begin(),
                         end = road->end(); iterator != end; ++iterator) {
                tempRoad->push_back(*(iterator));
            }

            driver->setTi(ti);                     // set the driver with the trip info
        } else if (!strcmp(buffer, "9") && (ti != NULL)) {
            driver->moveOneStep();                 // move the driver one step

            if (driver->getTi()->checkEnd(cab->getLocation()->getP())) { // if reached the end
                delete ti;                         // delete the trip info
                while (!tempRoad->empty()) {       // delete all the items of the tempRoad
                    delete tempRoad->front();
                    tempRoad->pop_front();
                }
                delete tempRoad;
                // set all to null
                tempRoad = NULL;
                driver->setTi(NULL);
                ti = NULL;
            }

        }
        // if the client received the advance order
    } while (strcmp(buffer, "exit"));

    // delete all objects in the client
    if (tempRoad != NULL) {
        while (!tempRoad->empty()) {
            delete tempRoad->front();
            tempRoad->pop_front();
        }
        delete tempRoad;
    }
    delete cab;
    delete driver;
    delete sock;
    return 0;
}