//
// MainFlow.
//

#include "MainFlow.h"

using namespace std;

int validateAllReceivedInfo = 0;
int actionCount = 0;

/**
 * constructor.
 * initialize the environment, get map, obstacles and create a SystemOperations.
 */
MainFlow::MainFlow(int port) {

    int rows, columns, obstacleNum;
    connections = new std::list<Connection *>();
    // creates a socket for connection with the clients
    sock = new Tcp(1, port);

    // get the map's size and create it
    cin >> columns >> rows;
    Map *map = new Map(columns, rows);
    cin.ignore();

    // get the obstacle amount
    obstacleNum = ProperInput::validInt();
    cin.ignore();
    conMap = new std::map<int, Connection *>();
    // create the system operation
    so = new SystemOperations(map, conMap);

    // make the obstacles List from the input
    for (; obstacleNum > 0; obstacleNum--) {
        Point obs = ProperInput::validPoint(columns, rows);
        cin.ignore();
        so->addObstacle(obs);
    }
}

/**
 * get inputs from user and follow the commands.
 */
void MainFlow::input() {
    choice = new int();
    int id, drivers_num, taxi_type, num_passengers, trip_time;
    double tariff;
    char trash, manufacturer, color;
    connectionData cd;
    cd.sock = sock;
    cd.connections = connections;

    do {
        // get the input from user to choose the action
        *choice = ProperInput::validInt();
        cin.ignore();
        switch (*choice) {

            // create drivers, gets from the client
            case 1: {
                drivers_num = ProperInput::validInt();      // amount of drivers
                cin.ignore();
                sock->initialize(drivers_num);
                // create thread that handle with client acceptnes
                int status = pthread_create(&connection_thread, NULL, acceptClients, &cd);
                if (status) {
                    cout << "problem creating thread" << endl;
                    break;
                }
                pthread_join(connection_thread, NULL);      // wait until the the thread finish
                for (std::list<Connection *>::const_iterator con = connections->begin(),
                             end = connections->end(); con != end; ++con) {
                    // receive the driver from the client
                    Driver *driver = (*con)->receiveData<Driver>();
                    // update the connection-id Driver map
                    (*conMap)[driver->getId()] = (*con);
                    // assign the Driver with the taxi, serialize the taxi, send it to the client
                    Taxi *taxi = so->assignDriver(driver);
                    (*con)->sendData<Taxi>(taxi);
                    (*con)->setOption(choice);
                }
                break;
            }
                // create new TripInfo
            case 2: {
                // get the input for the trip info
                id = ProperInput::validInt();
                cin >> trash;
                Point p1 = ProperInput::validPoint(so->getX(), so->getY());
                Point *start = new Point(p1.getX(), p1.getY());
                cin >> trash;
                Point p2 = ProperInput::validPoint(so->getX(), so->getY());
                Point *end = new Point(p2.getX(), p2.getY());
                cin >> trash;
                num_passengers = ProperInput::validInt();
                cin >> trash;
                tariff = ProperInput::validDouble();
                cin >> trash;
                trip_time = ProperInput::validInt();
                cin.ignore();
                TripInfo *tripInfo = new TripInfo(id, start, end, num_passengers, tariff,
                                                  trip_time);
                so->addTI(tripInfo);                        // add the trip info to the system
                break;

            }
                // create new Taxi
            case 3: {
                // get the input for the taxi
                id = ProperInput::validInt();
                cin >> trash;
                taxi_type = ProperInput::validInt();
                cin >> trash >> manufacturer >> trash >> color;
                cin.ignore();
                Taxi *taxi;

                if (taxi_type == 1)                      // create regular cab
                {
                    taxi = new Cab(ColorFactory::charToColor(color),
                                   CarManufactureFactory::charToFirm(manufacturer), id);

                } else if (taxi_type == 2)               // create LuxuryCab cab
                {
                    taxi = new LuxuryCab(ColorFactory::charToColor(color),
                                         CarManufactureFactory::charToFirm(
                                                 manufacturer), id);
                } else {
                    break;                               // wrong input from the user
                }
                so->addTaxi(taxi);                       // add the taxi to the system
                break;
            }
                // request for a driver location by his id
            case 4: {
                id = ProperInput::validInt();            // the id of the requested driver
                cin.ignore();
                Point *location = so->getDriverLocation(id);
                if (location) {
                    cout << *location;
                }
                break;
            }

                // clock time - move one step
            case 9: {
                actionCount++;               // global variable that tells the threads to move
                while (validateAllReceivedInfo < connections->size()) {
                    sleep(1);
                }
                so->moveAll();
                break;
            }
                // in every other case - don't do anything.
            default: {
                break;
            }
        }
        validateAllReceivedInfo = 0;         // initialize for the next choice
        // exit condition
    } while ((*choice) != 7);
    actionCount++;
    // wait that all the clients will finish their exit
    while (validateAllReceivedInfo < connections->size()) {
        sleep(1);
    }
}