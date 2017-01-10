//
// Driver.
//

#include "Driver.h"

/**
 * constructor.
 * @param id of the driver
 * @param age of the driver
 * @param status of the driver
 * @param experience of the driver
 */
Driver::Driver(int id, int age, const MartialStatues &status, int experience, int vehicle_id) :
        id(id), age(age), status(status), experience(experience), vehicleId(vehicle_id) {
    satisfaction = new Satisfaction();
    ti = NULL;
}

Driver::Driver(int id, int age, const MartialStatues &status, int experience, int vehicle_id,
               int port) : id(id), age(age), status(status), experience(experience),
                           vehicleId(vehicle_id), port(port) {
    satisfaction = new Satisfaction();
    ti = NULL;
}

/**
 * @return the id of the driver
 */
int Driver::getId() const {
    return id;
}

/**
 * @return the age of the driver
 */
int Driver::getAge() const {
    return age;
}

/**
 * @return the martial status of the driver
 */
const MartialStatues &Driver::getStatus() const {
    return status;
}

/**
 * @return the experience of the driver
 */
int Driver::getExperience() const {
    return experience;
}

/**
 *
 * @return the vehicle id
 */
int Driver::getVehicle_id() const {
    return vehicleId;
}

/**
 * @return the satisfaction of the driver
 */
Satisfaction *Driver::getSatisfaction() const {
    return satisfaction;
}

/**
 * @return the trip info of the driver
 */
TripInfo *Driver::getTi() {
    return ti;
}

/**
 * @return the cab of the driver
 */
Taxi *Driver::getCab() const {
    return cab;
}

/**
 * @return the port of the client driver
 */
int Driver::getPort() const {
    return port;
}

/**
 * @param status of the driver to set.
 */
void Driver::setStatus(const MartialStatues &status) {
    Driver::status = status;
}

/**
 * @param experience of the driver to set.
 */
void Driver::setExperience(int experience) {
    Driver::experience = experience;
}

/**
 * @param tripinfo of the driver to set.
 */
void Driver::setTi(TripInfo *tripinfo) {
    Driver::ti = tripinfo;
    if (tripinfo) {
        cab->setTariff(tripinfo->getTariff());
    } else {
        cab->setTariff(0);
    }
}

/**
 * @param cab of the driver to set.
 */
void Driver::setCab(Taxi *cab) {
    Driver::cab = cab;
}

/**
 * make the driver move one step towards his destination.
 */
void Driver::moveOneStep() {
    if (ti) {
        cab->move(ti->getRoad());
    }
}

/**
 * @param grade to add for the driver satisfaction
 */
void Driver::updateSatisfaction(int grade) {
    satisfaction->update(grade);
}

/**
 * @param otherDriver to compare id with this driver
 * @return true if the drivers have the same id
 */
bool Driver::operator==(const Driver &otherDriver) const {
    return id == otherDriver.id;
}

/**
 * @param otherDriver to compare id with this driver
 * @return false if the drivers are equal
 */
bool Driver::operator!=(const Driver &otherDriver) const {
    return !(otherDriver == *this);
}
