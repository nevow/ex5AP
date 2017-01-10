//
// BFS.
// has three static methods that use the algorithm and can print the road.
//

#ifndef EX1_BFS_H
#define EX1_BFS_H

#include "../coordinates/Point.h"
#include "../coordinates/Grid.h"
#include "../coordinates/Node.h"

class BFS {

public:

    static list<CoordinatedItem *> *use(Grid *Graph, CoordinatedItem *root,CoordinatedItem *dest);

    static void BFSAlgo(Grid *Graph, CoordinatedItem *root);

    static list<CoordinatedItem *> *getTrip(CoordinatedItem *dest);
};


#endif //EX1_BFS_H
