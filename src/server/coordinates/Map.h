//
// Matrix.
// inherit Grid, has rows, columns and list of nodes
//

#ifndef EX1_MAP_H
#define EX1_MAP_H

#include "Point.h"
#include "Grid.h"
#include "Node.h"
#include "CoordinatedItem.h"

class Map : public Grid {
private:
    int rows;
    int columns;
    Node ***matrix;

public:
    Map(int c, int r);

    ~Map();

    int getRows() const;

    int getColumns() const;

    CoordinatedItem *getCoordinatedItem(int r, int c);

    Node *getRoot();

    void setAll(int dist);

    void setItem(CoordinatedItem *item, int dist);

    CoordinatedItem **getAllNeighbours(CoordinatedItem *item);

};

#endif //EX1_MATRIX_H
