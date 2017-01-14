//
// SystemOperations.
//

#include <map>
#include "SystemOperations.h"
#include "BFS.h"

std::map<int, pthread_t> computeRoadT;              // global map of id trips info (key) and threads (value)

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
    map->setItem(n, -2);            // set the match node on the grid to -2
}

/**
 * addTI use the BFS to calculate the road of the ride, add the tripInfo to the taxi center
 * @param tripInfo is the TripInfo to add to the taxi center
 */
void SystemOperations::addTI(TripInfo *tripInfo) {
    pthread_t t1;
    ThreadArgs *threadArgs = new ThreadArgs();
    threadArgs->ti = tripInfo;
    threadArgs->grid = map;
    int status = pthread_create(&t1, NULL, ComputeRoad, threadArgs);
    if (!status) {
        computeRoadT[tripInfo->getRideId()] = t1;
        tc->addTI(tripInfo);
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

void *SystemOperations::ComputeRoad(void *threadArgs) {
    ThreadArgs *args = (ThreadArgs *) threadArgs;
    Node *start = new Node(args->ti->getStart());
    Point *end = (args->ti->getDestination());
    CoordinatedItem *dest = args->grid->getCoordinatedItem(end->getX(), end->getY());
    std::list<CoordinatedItem *> *road = BFS::use(args->grid, start, dest);
    delete start;
    args->ti->setRoad(road);
    delete (args);
    cout << "finished calculating road" << endl;
}