//
// CarManufactureFactory.
// factory of carManufacture.
//

#ifndef EX2AP_CARMANUFATUREFACTORY_H
#define EX2AP_CARMANUFATUREFACTORY_H

#include "CarManufacture.h"
#include <stdexcept>

class CarManufactureFactory {
public:

    /**
     * static method.
     * @param letter to create CarManufacture from
     * @return the CarManufacture of the letter
     */
    static CarManufacture charToFirm(char letter) {
        switch (letter) {
            case 'H':
                return CarManufacture::HONDA;
            case 'S':
                return CarManufacture::SUBARO;
            case 'T':
                return CarManufacture::TESLA;
            case 'F':
                return CarManufacture::FIAT;
            default:
                throw runtime_error("Wrong Firm");
        }
    }
};

#endif //EX2AP_CARMANUFATUREFACTORY_H
