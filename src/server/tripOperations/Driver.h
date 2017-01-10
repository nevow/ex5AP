//
// Driver.
//

#ifndef EX1_DRIVER_H
#define EX1_DRIVER_H


#include "../enum/MartialStatues.h"
#include "TripInfo.h"
#include "Satisfaction.h"
#include "../taxi/Taxi.h"

using namespace boost::archive;

class Driver {
private:
    int id;
    int age;
    MartialStatues status;
    int experience;
    TripInfo *ti;
    Satisfaction *satisfaction;
    Taxi *cab;
    int vehicleId;
    int port;

public:

    Driver() {};

    Driver(int id, int age, const MartialStatues &status, int experience, int vehicle_id);

    Driver(int id, int age,const MartialStatues &status, int experience, int vehicle_id, int port);

    ~Driver() {
        delete (satisfaction);
        if (ti) {
            delete (ti);
        }
    }

    int getId() const;

    int getAge() const;

    int getExperience() const;

    TripInfo *getTi();

    int getVehicle_id() const;

    Taxi *getCab() const;

    Satisfaction *getSatisfaction() const;

    const MartialStatues &getStatus() const;

    int getPort() const;

    void setStatus(const MartialStatues &status);

    void setExperience(int experience);

    void setTi(TripInfo *tripinfo);

    void setCab(Taxi *cab);

    void updateSatisfaction(int grade);

    void moveOneStep();

    bool operator==(const Driver &otherDriver) const;

    bool operator!=(const Driver &otherDriver) const;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & id;
        ar & age;
        ar & status;
        ar & experience;
        ar & ti;
        ar & satisfaction;
        ar & cab;
        ar & vehicleId;
        ar & port;
    }

};


#endif //EX1_DRIVER_H
