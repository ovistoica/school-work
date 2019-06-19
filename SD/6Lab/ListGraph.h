/**
 * LabSD 6
 * ListGraph.h
 * Purpose: Skeleton code for the neighbors list graph.
 *
 * @author Gabriel Bercaru
 */

#ifndef __LISTGRAPH_H__
#define __LISTGRAPH_H__

#include <vector>

/**
 * Node structure is useful only for the neighbors list implementation.
 */
struct Node {
    std::vector<int> neighbors;
    //bool visited;
};

/**
 * Neighbors list implementation.
 */
class ListGraph {
private:
    std::vector<Node> nodes;
    int size;

public:
    // Constructor
    ListGraph(int size): size(size) {
      nodes.resize(size);
     }

    // Destructor
    ~ListGraph() {}

    /**
     * Adds an edge between two existing nodes.
     *
     * @param src Source node of the edge to be added.
     * @param dst Destination node of the edge to be added.
     */
    void addEdge(int src, int dst) {
        nodes.at(src).neighbors.push_back(dst);
    }

    /**
     * Removes an existing edge from the graph.
     *
     * @param src Source node of the edge to be removed.
     * @param dst Destination node of the edge to be removed.
     */
    void removeEdge(int src, int dst) {
      // TODO: check if opposite is neccesary
      std::vector<int>::iterator it;
      for(it = nodes.at(src).neighbors.begin();
        it != nodes.at(src).neighbors.end(); ++it){
          if ((int) * it== dst){
            nodes.at(src).neighbors.erase(it);
            break;
          }
        }
    }

    /**
     * Checks if there is an edge between two existing nodes.
     *
     * @param src Source node of the edge.
     * @param dst Destination node of the edge.
     * @return True if there is an edge between src and dst, False otherwise.
     */
    bool hasEdge(int src, int dst) {
      std::vector<int>::iterator it;
      for(it = nodes.at(src).neighbors.begin();
        it != nodes.at(src).neighbors.end(); ++it){
          if ((int) * it== dst){
            return true;
          }
        }
        return false;
    }

    /**
     * Gets the vector of neighbors associated with the given node.
     *
     * @param node Node whose neighbors will get returned.
     * @return A vector containing the neighbors of the given node.
     */
    std::vector<int> getNeighbors(int node) {
        return nodes.at(node).neighbors;
      }

    /**
     * Gets the graph size.
     *
     * @return Number of nodes in the graph.
     */
    int getSize() {
        return size;
    }
};

#endif // __LISTGRAPH_H__
