/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int n){   //Creates n unconnected root nodes at the end of the vector
	for (int i = 0; i<n; i++)
		nodes.push_back(-1);	
}


//finds the index of the elem, return elem if empty
int DisjointSets::find(int elem){
	if(nodes[elem] <0)
		return elem;
	return find(nodes[elem]);
}

//unions set a and set b
void DisjointSets::setunion(int a, int b){
	int seta = find(a);
	int setb = find(b);
	//if 2 sets have same size, break
	if(seta == setb)
		return;
	
	//differnt size, union 2 sets
	int size = nodes[seta]+nodes[setb];
	if(nodes[seta]<= nodes[setb]){
		nodes[setb] = seta;
		nodes[seta] = size;
	}
	else{
		nodes[seta] = setb;
		nodes[setb] = size;
	}
	
}
