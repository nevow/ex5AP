//
// MartialStatuesFactory.
// factory for martial status
//

#ifndef EX2AP_MARTIALSTATUESFACTORY_H
#define EX2AP_MARTIALSTATUESFACTORY_H


#include "MartialStatues.h"
#include <stdexcept>

class MartialStatuesFactory {
public:

    /**
     * static method.
     * @param letter to decide which status to return.
     * @return the appropriate status
     */
    static MartialStatues getMartialStatus(char letter) {
        switch (letter) {
            case 'S':
                return MartialStatues::SINGLE;
            case 'M':
                return MartialStatues::MARRIED;
            case 'D':
                return MartialStatues::DIVORCED;
            case 'W':
                return MartialStatues::WIDOWED;
            default:
                throw runtime_error("Wrong status");
        }
    }
};

#endif //EX2AP_MARTIALSTATUESFACTORY_H
