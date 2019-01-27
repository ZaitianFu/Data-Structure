/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
vector <Vertex> vertexlist=graph.getVertices();
vector <Edge> edgelist=graph.getEdges();

for (unsigned i=0; i<vertexlist.size(); i++)
	graph.setVertexLabel(vertexlist[i],"unvisited");

for (unsigned i=0; i<edgelist.size(); i++ )
	graph.setEdgeLabel(edgelist[i].source, edgelist[i].dest, "unvisited" );

queue <Vertex> q;
	q.push(vertexlist[0]);
	graph.setVertexLabel(vertexlist[0], "visited");	
	Vertex startDest = (graph.getAdjacent(vertexlist[0]))[0];
	int minWeight = graph.getEdgeWeight(vertexlist[0], startDest);
	Vertex min1 = vertexlist[0];
	Vertex min2 = startDest;
	while(!q.empty())
	{
		Vertex w = q.front();
		q.pop();
		vector <Vertex> adjacent = graph.getAdjacent(w);
		for(size_t i = 0; i < adjacent.size(); i++)
		{
			if(graph.getVertexLabel(adjacent[i]) == "unvisited")
			{
				graph.setEdgeLabel(w, adjacent[i], "DISCOVERY");
				graph.setVertexLabel(adjacent[i], "visited");
				int currWeight = graph.getEdgeWeight(adjacent[i], w);
				if(currWeight < minWeight)
				{
					minWeight = currWeight;
					min1 = w;
					min2 = adjacent[i];
				}
				q.push(adjacent[i]); 
			}
			else if(graph.getEdgeLabel(w, adjacent[i]) == "unvisited")
			{
				graph.setEdgeLabel(w, adjacent[i], "CORSS");
				int currWeight = graph.getEdgeWeight(adjacent[i], w);
				if(currWeight < minWeight)
				{
					minWeight = currWeight;
					min1 = w;
					min2 = adjacent[i];
				}
			}
		}
	}
	
	graph.setEdgeLabel(min1, min2, "MIN");
	return minWeight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
  
vector <Vertex> vertixlist=graph.getVertices();
vector <Edge> edgelist=graph.getEdges();

for (unsigned i=0; i<vertixlist.size(); i++)
	graph.setVertexLabel(vertixlist[i],"unvisited");

for (unsigned i=0; i<edgelist.size(); i++ )
	graph.setEdgeLabel(edgelist[i].source, edgelist[i].dest, "unvisited" );
	
	queue <Vertex> q;
	unordered_map <Vertex, Vertex> parent;
	q.push(start);
	graph.setVertexLabel(start, "visited");	
	while(!q.empty())
	{
		Vertex w = q.front();
		q.pop();
		vector <Vertex> adjacent = graph.getAdjacent(w);
		for(size_t i = 0; i < adjacent.size(); i++)
		{
			if(graph.getVertexLabel(adjacent[i]) == "unvisited")
			{
				graph.setEdgeLabel(w, adjacent[i], "DISCOVERY");
				graph.setVertexLabel(adjacent[i], "visited");
				pair <Vertex, Vertex> pairVertex (adjacent[i], w);
				parent.insert(pairVertex);
				q.push(adjacent[i]); 
			}
			else if(graph.getEdgeLabel(w, adjacent[i]) == "unvisited")
			{
				graph.setEdgeLabel(w, adjacent[i], "CORSS");
			}
		}
	}
	int distance = 0;
	while(end != start)
	{
		graph.setEdgeLabel(end, parent[end], "MINPATH");
		end = parent[end];
		distance ++;
	}
	return distance;	
}


/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    vector< Vertex > vertexlist = graph.getVertices();
	int numV = vertexlist.size();
	DisjointSets setVertices;
	setVertices.addelements(numV);

	int count = 0;

	vector< Edge > edgelist = graph.getEdges();
	int numE = edgelist.size();
	std::sort(edgelist.begin(), edgelist.end());

	for(int i = 0; i < numE && count < numV - 1; i++)
	{
		if(setVertices.find(edgelist[i].source) != setVertices.find(edgelist[i].dest))
		{
			setVertices.setunion(edgelist[i].source, edgelist[i].dest);
			graph.setEdgeLabel(edgelist[i].source, edgelist[i].dest, "MST");
			count++;
		}
	}

}

