//
// SystemOperations.
//

#include <map>
#include "SystemOperations.h"
#include "BFS.h"

// global map of id trips info (key) and threads (value)
std::map<int, pthread_t> computeRoadT;

/**
 * struct ThreadArgs has Map and TripInfo
 */
struct ThreadArgs {
    Map *grid;
    TripInfo *ti;
};

/**
 * constructor.
 * @param map1 the map to do on it the operations
 * @param conMap is a map of ints and connections.
 */
SystemOperations::SystemOperations(Map *map1, std::map<int, Connection *> *conMap) {
    map = map1;
    obstacles = new list<Node *>;
    tc = new TaxiCenter(conMap);
    x = map->getColumns();
    y = map->getRows();
    pthread_mutex_init(&grid_locker, 0);
}

/**
 * @return the x of the so
 */
int SystemOperations::getX() const {
    return x;
}

/**
 * @return the y of the so
 */
int SystemOperations::getY() const {
    return y;
}

/**
 * @param d is the Driver to add to the taxi center
 * @return the cab that set to the driver
 */
Taxi *SystemOperations::assignDriver(Driver *d) {
    Taxi *taxi = tc->getTaxiByID(d->getVehicle_id());
    d->setCab(taxi);
    tc->addDriver(d);
    return taxi;
}

/**
 * @param cab is the Taxi to add to the taxi center
 */
void SystemOperations::addTaxi(Taxi *cab) {
    tc->addTaxi(cab);
}

/**
 * @param obstacle to add to the obstacles List.
 */
void SystemOperations::addObstacle(Point obstacle) {
    Node *n = new Node(&obstacle);
    obstacles->push_front(n);
    map->setItem(n, -2);                    // set the match node on the grid to -2
}

/**
 * addTI add the tripInfo to the taxi center,
 * and create thread with the function ComputeRoad
 * @param tripInfo is the TripInfo to add to the taxi center
 */
void SystemOperations::addTI(TripInfo *tripInfo) {
    pthread_t t1;
    ThreadArgs *threadArgs = new ThreadArgs();
    threadArgs->ti = tripInfo;
    threadArgs->grid = map;

    int status = pthread_create(&t1, NULL, ComputeRoad, threadArgs);
    // if the the thread Succeeded
    if (!status) {
        computeRoadT[tripInfo->getRideId()] = t1;   // add the thread to computeRoadT map
        tc->addTI(tripInfo);                        // add the tripInfo to the taxi center
    } else {
        std::cout << "ComputeRoad fails" << endl;
    }
}

/**
 * @param id is the id of the driver
 * @return the Point of the driver from the taxiCenter
 */
Point *SystemOperations::getDriverLocation(int id) {
    return tc->getDriverLocation(id);
}

/**
 * move all the taxi by call Taxi Center's "moveAll"
 */
void SystemOperations::moveAll() {
    tc->moveAll();
}

/**
 * ComputeRoad use the BFS to calculate the road of the ride.
 * @param threadArgs is the struct with the argumrnts for the calculation
 * @return
 */
void *SystemOperations::ComputeRoad(void *threadArgs) {
    ThreadArgs *args = (ThreadArgs *) threadArgs;
    Node *start = new Node(args->ti->getStart());          // the start of the road
    Point *end = (args->ti->getDestination());             // the end of the road
    CoordinatedItem *dest = args->grid->getCoordinatedItem(end->getX(), end->getY());
    // use BFS algoritem
    std::list<CoordinatedItem *> *road = BFS::use(args->grid, start, dest);
    delete start;
    args->ti->setRoad(road);        // set the road in the Trip Info
    delete (args);
    return NULL;
}