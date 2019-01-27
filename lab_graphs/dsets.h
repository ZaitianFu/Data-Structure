/* Your code here! */
#ifndef DSETS_H 
#define DSETS_H
#include <vector>

using namespace std;

class DisjointSets
{
	public:
		void addelements(int num);//function to add elements
		
		int find(int elem);//compress paths and works as described in lecture; returns the index of the root of the up-tree in which the parameter element resides.
		
		void setunion(int a, int b);//This function should be implemented as union-by-size.
		
	private:
		//up-tree nodes
		vector<int> nodes;
};
#endif //DSETS_H
