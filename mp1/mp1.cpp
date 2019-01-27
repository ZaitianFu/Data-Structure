#include <string>
#include <cstdlib>
#include "mp1.h"
#include <cmath>
#include <iostream>
using namespace std;
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
// Load in.png
    PNG pic1; PNG pic2;
    pic1.readFromFile(inputFile);
    pic2.readFromFile(inputFile);

 for (unsigned y = 0;y < pic1.height(); y++) {
	 for (unsigned x = 0;  x < pic1.width(); x++) {
	 HSLAPixel* temp=pic1.getPixel(x,y);
	 temp->s=(pic2.getPixel(pic1.width()-x-1,pic1.height()-y-1))->s;
	 temp->h=(pic2.getPixel(pic1.width()-x-1,pic1.height()-y-1))->h;
	 temp->l=(pic2.getPixel(pic1.width()-x-1,pic1.height()-y-1))->l;
	 temp->a=(pic2.getPixel(pic1.width()-x-1,pic1.height()-y-1))->a;

            }
        }

    // Save the output file
    pic1.writeToFile(outputFile);	
}

