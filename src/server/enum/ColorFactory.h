//
// ColorFactory.
// factory of colors.
//

#ifndef EX2AP_COLORFACTORY_H
#define EX2AP_COLORFACTORY_H

#include "Color.h"
#include <stdexcept>

class ColorFactory {
public:

    /**
     * static method.
     * @param letter to create Color from
     * @return the Color of the letter
     */
    static Color charToColor(char letter) {
        switch (letter) {
            case 'R':
                return Color::RED;
            case 'B':
                return Color::BLUE;
            case 'G':
                return Color::GREEN;
            case 'P':
                return Color::PINK;
            case 'W':
                return Color::WHITE;
            default:
                throw runtime_error("Wrong Color");
        }
    }
};

#endif //EX2AP_COLORFACTORY_H
