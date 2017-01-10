//
// ProperInput.
//

#include "ProperInput.h"
#include <stdexcept>

using namespace std;

/**
 * @return Point correct, after tests.
 */
Point ProperInput::validPoint(int columns, int rows) {
    Point point;
    cin >> point;

    // check if the point is in the map's boundary
    if ((point.getX() < columns) && (point.getY() < rows) &&
        (point.getX() >= 0) && (point.getY() >= 0)) {
        return point;
    } else {
        throw std::runtime_error("the point is not on the map boundaries");
    }
}

/**
 * @return int correct, after tests
 */
int ProperInput::validInt() {
    int num;
    cin >> num;

    //check if the num is positive
    if (num >= 0) {
        return num;
    } else {
        throw std::runtime_error("negative number");
    }
}

/**
 * @return double correct, after tests.
 */
double ProperInput::validDouble() {
    double num;
    cin >> num;

    //check if the num is positive
    if (num >= 0) {
        return num;
    } else {
        throw std::runtime_error("negative number");
    }
}