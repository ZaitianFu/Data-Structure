/**
 * @file NimLearner.cpp
 * CS 225 - Fall 2017
 */

#include "NimLearner.h"


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true) {
Graph g_(true); 
size_t numT=startingTokens;

 vector<Vertex> vertices(2*numT+2);
    for (size_t i = numT; i >=0; --i) {
        vertices[i] = g_.insertVertex("p1-"+i);
        g_.setVertexName(i, "p1-"+i);
    }

   for (size_t i = 2*numT+1; i >numT; --i) {
        vertices[i] = g_.insertVertex("p2-"+i);
        g_.setVertexName(i, "p2-"+(i-numT-1));
    }

 for (size_t i = numT; i >1; --i) {
        g_.insertEdge(vertices[i], vertices[i+numT]);
        g_.insertEdge(vertices[i], vertices[i+numT-1]);
    }

 g_.insertEdge(vertices[1], vertices[1+numT]);

 for (size_t i = 2*numT+1; i >numT+2; --i) {
        g_.insertEdge(vertices[i], vertices[i-numT-2]);
        g_.insertEdge(vertices[i], vertices[i-numT-3]);
    }

 g_.insertEdge(vertices[numT+2], vertices[0]);

}


/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;

  return path;
}


/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {

}


/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
