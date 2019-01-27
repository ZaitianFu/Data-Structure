/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage & theSource,
                       vector<TileImage*> & theTiles)
{
    /**
     * @todo Implement this function!
     */
   
    if (theTiles.empty())
        return NULL;

    map<HSLAPixel, int> tile_avg_map;
    vector<Point<3>> points;
    points.reserve(theTiles.size());
    for (unsigned int i = 0; i < theTiles.size(); ++i) {
        HSLAPixel avg = theTiles[i]->getAverageColor();
        avg.h /= 360;
        tile_avg_map[avg] = i;
        Point<3> mapPt(avg.h, avg.s, avg.l);
        points.push_back(mapPt);
    }

    KDTree<3> tree(points);
    int rows = theSource.getRows();
    int columns = theSource.getColumns();

    MosaicCanvas* mosaic = new MosaicCanvas(rows, columns);
    
    map<Point<3>,int> index;
    
    for (size_t i=0; i< points.size(); i++){
    	index[points[i]]=i;  
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            HSLAPixel pic=theSource.getRegionColor(row,col);
	    Point <3> target(pic.h/360,pic.s,pic.l);
	    Point <3> find=tree.findNearestNeighbor(target);
	    
            mosaic->setTile(row, col, theTiles[index[find]]);
        }
    }

    return mosaic;
}

