//
// Node.
// inherit CoordinatedItem, has a point.
//

#include "Node.h"

/**
 * @return the point of the node
 */
Point *Node::getP() {
    return p;
}

/**
 * @param p to set the point.
 */
void Node::setP(Point *p) {
    Node::p = new Point(p->getX(), p->getY());
}

/**
 * @param coords to delete
 */
void Node::deleteCoords(int **coords) {
    p->deleteCoords(coords);
}

/**
 * @return array with the coordinate of the point
 */
int **Node::getCoordinates() {
    int **coords = new int *[2];
    coords[0] = new int(p->getX());
    coords[1] = new int(p->getY());
    return coords;
}

/**
 * @param otherNode to compare with
 * @return true if equal, false otherwise
 */
bool Node::operator==(const Node &otherNode) const {
    return *p == *otherNode.p;
}

/**
 * @param otherNode to compare with
 * @return  true if not equal, false otherwise
 */
bool Node::operator!=(const Node &otherNode) const {
    return !(otherNode == *this);
}

BOOST_CLASS_EXPORT(Node);
