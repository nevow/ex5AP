//
// Point.
// has x and y as coordinates.
//

#include "Point.h"

/**
 * @return the x coordinate of the point
 */
int Point::getX() {
    return x;
}

/**
 * @return the y coordinate of the point
 */
int Point::getY() {
    return y;
}

/**
 * @param xp for the x coordinate of the point
 */
void Point::setX(int xp) {
    x = xp;
}

/**
 * @param yp for the y coordinate of the point
 */
void Point::setY(int yp) {
    y = yp;
}

/**
 * @param coords to delete
 */
void Point::deleteCoords(int **coords) {
    delete (coords[0]);
    delete (coords[1]);
    delete[] (coords);
}

/**
 * @param output to write to
 * @param p is the point to print
 * @return the output after the insertion of p
 */
ostream &operator<<(ostream &output, const Point &p) {
    output << "(" << p.x << "," << p.y << ")" << endl;
    return output;
}

/**
 * @param input to load the Point from
 * @param p is the point to load
 * @return the input after the loading of p
 */
istream &operator>>(istream &input, Point &p) {
    char g;
    input >> p.x >> g >> p.y;
    return input;
}

/**
 * @param otherP to compare with
 * @return true if equal, false otherwise
 */
bool Point::operator==(const Point &otherP) const {
    return x == otherP.x &&
           y == otherP.y;
}

/**
 * @param otherP to compare with
 * @return true if not equal, false otherwise
 */
bool Point::operator!=(const Point &otherP) const {
    return !(otherP == *this);
}
