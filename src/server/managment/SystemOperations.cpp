//
// SystemOperations.
//

#include "SystemOperations.h"
#include "BFS.h"

/**
 * constructor.
 * @param map1 the map to do on it the operations
 * @param obs is a lists of obstacles.
 */
SystemOperations::SystemOperations(Map *map1, Socket *socket) {
    map = map1;
    obstacles = new list<Node *>;
    tc = new TaxiCenter(socket);
    x = map->getColumns();
    y = map->getRows();
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
    Node *start = new Node(tripInfo->getStart());
    Point *end = (tripInfo->getDestination());
    CoordinatedItem *dest = map->getCoordinatedItem(end->getX(), end->getY());
    std::list<CoordinatedItem *> *road = BFS::use(map, start, dest);
    delete start;
    tripInfo->setRoad(road);
    tc->addTI(tripInfo);
}

/**
 * @param id is the id od the driver
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
