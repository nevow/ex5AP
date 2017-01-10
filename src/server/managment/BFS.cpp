//
// BFS.
// has three static methods that use the algorithm and can print the road.
//

#include <queue>
#include "BFS.h"

/**
 * @param Graph that the algorithm run on
 * @param root of the Graph
 * @param dest od calculate the road to
 * @return stack of CoordinatedItem represent the road
 */
list<CoordinatedItem *> *BFS::use(Grid *Graph, CoordinatedItem *root, CoordinatedItem *dest) {
    // spread the distances using the BFS algorithm
    BFS::BFSAlgo(Graph, root);
    return (getTrip(dest));
}

/**
 * @param graph to run the algorithm on.
 * @param root to start from
 */
void BFS::BFSAlgo(Grid *graph, CoordinatedItem *root) {

    graph->setAll(-1);        // for each node in Graph set to -1, and reset his father to null

    queue<CoordinatedItem *> queue;
    graph->setItem(root, 0);                // set root distance to 0
    queue.push(graph->getRoot());

    CoordinatedItem *current;

    while (!queue.empty()) {                // run until there is no node left in the queue

        // save and pop the first in the queue
        current = queue.front();
        queue.pop();
        // get the neighbours
        CoordinatedItem **neighbours = graph->getAllNeighbours(current);

        /**
         * go over all the neighbours of i, according to 9,12,3,6
         * set the distance from the start point,
         * set the father
         */
        for (int i = 0; neighbours[i] != NULL; i++) {
            CoordinatedItem *neighbour = neighbours[i];
            if (neighbour->getDistance() == -1) {
                neighbour->setDistance(current->getDistance() + 1);
                neighbour->setParent(current);
                queue.push(neighbour);
            }
        }
        delete[] (neighbours);
    }
}

/**
 * @param graph to search in it
 * @param dest of the road
 * @return list of CoordinatedItem represent the road
 */
list<CoordinatedItem *> *BFS::getTrip(CoordinatedItem *dest) {
    std::list<CoordinatedItem *> *road = new list<CoordinatedItem *>;

    // insert the items to the stack from the end point to the start traversing over the parent.
    while (dest->getDistance() >= 0) {
        road->push_front(dest);
        if (dest->getDistance() == 0) {
            break;
        } else {
            dest = dest->getParent();
        }
    }
    road->pop_front();
    road->front()->setParent(NULL);
    return road;
}
