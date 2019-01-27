/* Your code here! */
#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include "dsets.h"

using namespace std;

class SquareMaze{

public:
 	SquareMaze ();
 
	void makeMaze (int width, int height);
 	
	bool canTravel (int x, int y, int dir) const;
 	
	void setWall (int x, int y, int dir, bool exists);

	vector< int > solveMaze ();
 
	PNG * 	drawMaze () const;
 
	PNG * 	drawMazeWithSolution ();

private:
	int width;

	int height;
	
	int size;

	DisjointSets setofcells;

	vector< bool > rightWall;

	vector< bool > downWall;

	
};

#endif
