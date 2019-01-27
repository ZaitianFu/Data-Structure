/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
 
 #include <cmath>
 using namespace std;
 
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     
     int b[9];
     if(curDim>= 0 && curDim< Dim)               // valid input;
	{
		if(first[curDim]!=second[curDim])             //compare elements in two points;
			return (first[curDim] < second[curDim]);
		else 
			return (first < second);            //call operator when elements are equal;
	}

    else                                     // invalid input, return false;
    	return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double currdis = finddis(target, currentBest);          //get two distance values of two points;
     double potentialdis = finddis(target, potential);
     
	if(currdis != potentialdis)
		return (potentialdis < currdis);           //return true if the distance of potentialBest is shorter;
	else
		return (potential < currentBest);          //call operator when distances are equal;
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     points = newPoints;
    
     
}

template<int Dim>
void KDTree<Dim>::KDTreehelper(vector< Point<Dim> > & newPoints, int L, int R, int dimension)
{
    if (L > R) return;
	
	int mid = (L+R) / 2;    //find mid
	points[mid] = Quickselect(newPoints, L, R, mid, dimension);
	
    //recurse through left and right partitions
    
        KDTreehelper(newPoints, L, mid - 1, (dimension + 1) % Dim);  //divide kd tree
    
        KDTreehelper(newPoints, mid + 1, R, (dimension + 1) % Dim);
}

template<int Dim>
Point<Dim> KDTree<Dim>::Quickselect(vector< Point<Dim> > & newPoints, int L, int R, int mid, int dimension)
{
	
	
	
	swap(newPoints[mid], newPoints[R]);        // Move mid(pivot) to the end
	int newIndex = L;
	for (int i = L; i < R ; i++)          //ordering each elem
	{
		if (smallerDimVal(newPoints[i], newPoints[mid], dimension))
		{
            		swap(newPoints[i], newPoints[newIndex]);
			newIndex++;
		}
		
	}
	
	swap(newPoints[R], newPoints[newIndex]); // Move back
	
	
	while(L < R) 
	{			
       	        if (newIndex == mid)
			return newPoints[newIndex];

		else if (newIndex > mid)
			R = newIndex - 1; // search left part
		
                else if (newIndex < mid)
			L = newIndex + 1; // search right part
	}
	
	return newPoints[L];   
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     return findNearestNeighborhelper(0, query, 0, points.size()-1, points[(points.size()-1)/2]);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighborhelper(int dimension, const Point<Dim> &query, int L, int R, const Point<Dim> &currentBest) const
{
    /**
     * @todo Implement this function!
     */
    bool target_left = true;
    Point<Dim> ret = currentBest;
    if (L == R)           //leaf node, base case
    {
        if (shouldReplace(query, currentBest, points[L]))//update curbest when leaf node is closer
        {
             ret = points[L];
            return ret;
        }
        ret = currentBest;  // return curbest
        return ret;
    }
    
    int mid = (L + R)/2;
    if (smallerDimVal(points[mid], query, dimension) && R > mid)   //update ret when left part is closer
    {
        ret = findNearestNeighborhelper((dimension+1)%Dim, query, mid+1, R, currentBest);
        target_left = false;
       
    }
    if (smallerDimVal(query, points[mid], dimension) && L < mid)    //update ret when right part is closer
    {   
        ret = findNearestNeighborhelper((dimension+1)%Dim, query, L, mid-1, currentBest);
        target_left = true;
        
    }

    
    if (shouldReplace(query, ret, points[mid]))  //back to check if cur node is closer
        ret = points[mid];
    
    if (sqrt(pow(points[mid][dimension] - query[dimension],2)) <= finddis(query, ret))   //check other subtrees if its distance is closer
    {
        if (target_left && R > mid)
            ret = findNearestNeighborhelper((dimension+1)%Dim, query, mid+1, R, ret);    //recursion
        if (!target_left && L < mid)
            ret =findNearestNeighborhelper((dimension+1)%Dim, query, L, mid-1, ret);
    }
    return ret;
}

template <int Dim>
double KDTree<Dim>:: finddis(const Point<Dim>& p1,const Point<Dim>& p2) const
{
    /**
     * @todo Implement this function!
     */
      int dis = 0;
	for(int i = 0; i < Dim; i++)                      // get distance between two given points;
		dis = dis+ (int)pow(p1[i]-p2[i],2);
	
     dis=sqrt(dis);
    return dis;
}
