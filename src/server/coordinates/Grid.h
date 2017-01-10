//
// Grid.
// an abstract class.
//

#ifndef EX1_GRID_H
#define EX1_GRID_H

#include "CoordinatedItem.h"

class Grid {

public:

    /**
     * abstract method.
     * @param item is the CoordinatedItem that need his neighbours
     * @return an array of the item's Neighbours
     */
    virtual CoordinatedItem **getAllNeighbours(CoordinatedItem *item) = 0;

    /**
     * abstract method.
     * @return the root (CoordinatedItem)
     */
    virtual CoordinatedItem *getRoot() = 0;

    /**
     * abstract method.
     * @param r represent the x point of the CoordinatedItem
     * @param c represent the y point of the CoordinatedItem
     * @return the CoordinatedItem in the needed position
     */
    virtual CoordinatedItem *getCoordinatedItem(int r, int c) = 0;

    /**
     * abstract method.
     * @param dist is the value to set at all the CoordinatedItems
     */
    virtual void setAll(int dist) = 0;

    /**
     * abstract method.
     * @param item the need to be set.
     * @param dist is the value to set in the CoordinatedItem
     */
    virtual void setItem(CoordinatedItem *item, int dist) = 0;

};


#endif //EX1_GRID_H
