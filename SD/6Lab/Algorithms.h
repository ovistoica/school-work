/**
 * Lab6 SD
 * Algorithms.h
 * Purpose: Wrapper class for Lab6 algorithms.
 *
 * @author Gabriel Bercaru
 */

#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <vector>
#include <queue>
#include <stack>
#include <iostream>

#include "ListGraph.h"
#include "MatrixGraph.h"

class Algorithms {
public:
    /**
     * Returns a breadth-first traversal of the given matrix graph.
     *
     * @param matrixGraph Matrix representation of a graph.
     * @return A vector containing indexes of the nodes, visited using BFS.
     */
    static std::vector<int> BFS(MatrixGraph matrixGraph) {
        return std::vector<int>();
    }

    /**
     * Returns a breadth-first traversal of the given list graph.
     *
     * @param listGraph Neighbors list representation of a graph.
     * @return A vector containing indexes of the nodes, visited using BFS.
     */
     static std::vector<int> BFS(ListGraph listGraph) {
       std::queue<int> Q;
       std::vector<bool> visited(listGraph.getSize(), false);
       std::vector<int> toRet;
       visited[0] = true;
       Q.push(0);
       while (!Q.empty()){
         int cur = Q.back();
         Q.pop();
         toRet.push_back(cur);
         std::vector<int> neighbors = listGraph.getNeighbors(cur);
         std::vector<int>::iterator it;
         for(it = neighbors.begin(); it !=neighbors.end(); ++it ){
           if(!visited[*it]){
             visited[*it] = true;
             Q.push(*it);
           }
         }
       }
       return toRet;
     }

    /**
     * Returns a depth-first traversal of the given matrix graph.
     *
     * @param matrixGraph Matrix representation of a graph.
     * @return A vector containing indexes of the nodes, visited using DFS.
     */
    static std::vector<int> DFS(MatrixGraph matrixGraph) {
        // TODO: TASK 3
        return std::vector<int>();
    }

    /**
     * Returns a depth-first traversal if the given graph.
     *
     * @param listGraph Neighbors list representation of a graph.
     * @return A vector containing indexes of the nodes, visited using DFS.
     */
    static std::vector<int> DFS(ListGraph listGraph) {
        // TODO: TASK 3
        std::stack<int> S;
        std::vector<bool> visited(listGraph.getSize(), false);
        std::vector<int> toRet;
        visited[0] = true;
        S.push(0);
        while (!S.empty()){
          int cur = S.top();
          S.pop();
          toRet.push_back(cur);
          std::vector<int> neighbors = listGraph.getNeighbors(cur);
          std::vector<int>::iterator it;
          for(it = neighbors.begin(); it !=neighbors.end(); ++it ){
            if(!visited[(int) * it]){
              S.push((int) * it);
            }
          }
        }
       return toRet;
    }

    /**
     * Applies recursive DFS on the given graph.
     * The result of the traversal must be placed in nodeList.
     *
     * @param listGraph Neighbors list representation of a graph.
     * @param visited Vector containing the visit status of each node.
     * @param nodeList Vector which must contain the result of the traversal.
     * @param node The starting point of the traversal.
     */
    static void rDFS(ListGraph& listGraph, std::vector<bool>& visited,
        std::vector<int>& nodeList, int node) {
        visited[node] = true;
        nodeList.push_back(node);
        std::vector<int> neighbors = listGraph.getNeighbors(node);
        std::vector<int>::iterator it;
        for(it = neighbors.begin(); it !=neighbors.end(); ++it ){
          if(!visited[*it]){
            rDFS(listGraph, visited, nodeList, *it);
          }
        }
      }

    /**
     * Applies Floyd-Warshall on the given graph.
     *
     * @param matrixGraph Matrix representation of a graph.
     * @return A matrix where A[i][j] contains the shortest path from node i to node j.
     */
    static std::vector<std::vector<int>> Floyd_Warshall(MatrixGraph matrixGraph) {
      std::vector<std::vector<int>> m = matrixGraph.m();
      for(int k = 0; k < matrixGraph.getSize(); k++){
        for(int i = 0; i < matrixGraph.getSize(); i++){
          for(int j = 0; j < matrixGraph.getSize(); j++){
            if(m[i][j] > m[i][k] + m[k][j]){
                m[i][j] = m[i][k] + m[k][j];
              }
          }
        }
      }

        return m;
    }

    /**
     * Applies Kruskal on the given graph.
     *
     * @param matrixGraph Matrix representation of a graph.
     * @return A vector of edges (described by the two adjacent nodes) which compose the minimum spanning tree.
     */
    static std::vector<std::pair<int, int>> Kruskal(MatrixGraph matrixGraph) {
        // TODO: BONUS 3
        return std::vector<std::pair<int, int>>();
    }
};

#endif // __ALGORITHMS_H__
