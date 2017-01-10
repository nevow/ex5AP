//
// ProperInput.
//

#ifndef EX2AP_PROPERINPUT_H
#define EX2AP_PROPERINPUT_H


#include "../coordinates/Map.h"

class ProperInput {

public:

    static Point validPoint(int columns, int rows);

    static int validInt();

    static double validDouble();

};


#endif //EX2AP_PROPERINPUT_H
