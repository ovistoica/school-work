/**
 * LabSD 6
 * MatrixGraph.h
 * Purpose: Skeleton code for the matrix graph.
 *
 * @author Gabriel Bercaru
 */

#ifndef __MATRIXGRAPH_H__
#define __MATRIXGRAPH_H__

#include <vector>

/**
 * Matrix implementation.
 */
class MatrixGraph {
private:
    std::vector<std::vector<int>> adjacency_matrix;
    int size;

public:
    // Constructor
    MatrixGraph(int size): size(size) {
        adjacency_matrix.resize(size, std::vector<int> (size, 0));
    }

    // Destructor
    ~MatrixGraph() {}

    /**
     * Adds an edge between two existing nodes.
     *
     * @param src Source node of the edge to be added.
     * @param dst Destination node of the edge to be added.
     */
    void addEdge(int src, int dst) {
      adjacency_matrix[src][dst] = 1;
    }

    /**
     * Adds an edge between two existing nodes, with given cost.
     *
     * @param src Source node of the edge to be added.
     * @param dst Destination node of the edge to be added.
     * @param cost The cost associated with the new edge.
     */
    void addEdgeWithCost(int src, int dst, int cost) {
      adjacency_matrix[src][dst] = cost;
    }

    /**
     * Removes an existing edge from the graph.
     *
     * @param src Source node of the edge to be removed.
     * @param dst Destination node of the edge to be removed.
     */
    void removeEdge(int src, int dst) {
      adjacency_matrix[src][dst] = 0;
      // TODO: check if opposite is neccesary
    }

    /**
     * Checks if there is an edge between two existing nodes.
     *
     * @param src Source node of the edge.
     * @param dst Destination node of the edge.
     * @return True if there is and edge between src and dst, False otherwise.
     */
    bool hasEdge(int src, int dst) {
      return (adjacency_matrix[src][dst]);
    }

    /**
     * Returns the cost of the edge described by src and dst.
     *
     * @param src Source node of the edge.
     * @param dst Destination node of the edge.
     * @return Cost of the edge between src and dst.
     */
    int edgeCost(int src, int dst) {
        return adjacency_matrix[src][dst];
    }

    /**
     * Gets the vector of neighbors associated with the given node.
     *
     * @param node Node whose neighbors will get returned.
     * @return A vector containing the neighbors of the given node.
     */
    std::vector<int> getNeighbors(int node) {
        return adjacency_matrix[node];
    }

    std::vector<std::vector<int>> m() {
      return adjacency_matrix;
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

#endif // __MATRIXGRAPH_H__
