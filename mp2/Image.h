#ifndef IMAGE 
#define IMAGE H
#include "cs225/PNG.h"

using namespace cs225;
class Image: public PNG
{
public:
void lighten();
void lighten (double a);
void darken();
void darken(double a);
void saturate();
void saturate(double a);
void desaturate();
void desaturate(double a);
void grayscale();
void rotateColor(double a);
void illinify();
void scale(double a);
void scale(unsigned w, unsigned h);
};
#endif
