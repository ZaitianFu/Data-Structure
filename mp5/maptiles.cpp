/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
	int b[9];
    vector< Point<3> > colors;  // kdtree with a vector of colors
    
    //map :color->tile
    map<Point<3>, TileImage> Map;
    Point<3> p2;
    
    int r = theSource.getRows();  // create new canvas
    int c = theSource.getColumns();
    MosaicCanvas::MosaicCanvas *canvas = new MosaicCanvas(r, c);
    
    for (int i = 0; i < (int)theTiles.size(); i++)
    {
        //get average color
        HSLAPixel p1 = theTiles[i].getAverageColor();
        p2=Point<3>(p1.h/360, (p1.s), p1.l);
        
        Map[p2] = theTiles[i];
        colors.push_back(p2);   //puts into the vector
    }

   
    KDTree<3>::KDTree tree(colors);   //create a kdtree 

    

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            HSLAPixel regionColor = theSource.getRegionColor(i, j); // get pixle
            p2= Point<3>((regionColor.h) /360.0, regionColor.s, regionColor.l);                                           //get the closest average color 
            Point<3> closestPoint = tree.findNearestNeighbor(p2);
           
            TileImage theTile = Map[closestPoint]; //mapping the tile

            canvas->setTile(i,j,theTile); // put the tile into canvas
        }
    }

    return canvas;   // return
}

