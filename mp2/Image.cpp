#include "Image.h"
#include <cmath>

void Image::lighten()
{
	for (unsigned y = 0;y < height(); y++) {
	 for (unsigned x = 0;  x < width(); x++) {
		HSLAPixel*temp=getPixel(x,y);
		if (temp->l<0.9)
		temp->l=temp->l+0.1;
		else
		temp->l=1;
		
		}
	}
}


void Image::lighten(double a)
{
	for (unsigned y = 0;y < height(); y++) {
	 for (unsigned x = 0;  x < width(); x++) {
		HSLAPixel*temp=getPixel(x,y);
		if (temp->l<1-a)
		temp->l=temp->l+a;
		else
		temp->l=1;
		
		}
	}
}


void Image::darken()
{
	for (unsigned y = 0;y < height(); y++) {
	 for (unsigned x = 0;  x < width(); x++) {
		HSLAPixel*temp=getPixel(x,y);
		if (temp->l>0.1)
		temp->l=temp->l-0.1;
		else
		temp->l=0;
		
		}
	}
}

void Image::darken(double a)
{
	for (unsigned y = 0;y < height(); y++) {
	 for (unsigned x = 0;  x < width(); x++) {
		HSLAPixel*temp=getPixel(x,y);
		if (temp->l>a)
		temp->l=temp->l-a;
		else
		temp->l=0;
		
		}
	}
}


void Image::saturate()
{
for (unsigned y = 0;y < height(); y++) {
   for (unsigned x = 0;  x < width(); x++) {
		HSLAPixel*temp=getPixel(x,y);
	if (temp->s<0.9)
		temp->s=temp->s+0.1;
	else
		temp->s=1;
		}
	}

}


void Image::saturate(double a)
{
for (unsigned y = 0;y < height(); y++) {
   for (unsigned x = 0;  x < width(); x++) {
		HSLAPixel*temp=getPixel(x,y);
	if (temp->s<1-a)
		temp->s=temp->s+a;
	else
		temp->s=1;
		}
	}

}

void Image::desaturate()
{
for (unsigned y = 0;y < height(); y++) {
   for (unsigned x = 0;  x < width(); x++) {
		HSLAPixel*temp=getPixel(x,y);
	if (temp->s>0.1)
		temp->s=temp->s-0.1;
	else
		temp->s=0;
		}
	}

}


void Image::desaturate(double a)
{
for (unsigned y = 0;y < height(); y++) {
   for (unsigned x = 0;  x < width(); x++) {
		HSLAPixel*temp=getPixel(x,y);
	if (temp->s>a)
		temp->s=temp->s-a;
	else
		temp->s=0;
		}
	}

}

void Image::grayscale()
{
for (unsigned y = 0;y < height(); y++) {
   for (unsigned x = 0;  x < width(); x++) {
		HSLAPixel*temp=getPixel(x,y);
		temp->s=0;
		}
	}
	
}


void Image::rotateColor(double a)
{
for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);
      if (a<0)
	a=360+a;

      if (pixel->h+a<360)
	pixel->h = pixel->h+a;
      else
	pixel->h=pixel->h+a-360;
		
	}
    }
  }
	



void Image::illinify()
{
for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel *pixel = getPixel(x, y);
	double disTo11a =abs(pixel->h-11);
	double disTo11b =360-pixel->h+11;
	double disTo216a=abs(pixel->h-216);
	double disTo216b=360-pixel->h+216;
      if (min(disTo11a,disTo11b) < min(disTo216a,disTo216b))
	pixel->h = 11;
      else
	pixel->h= 216;
    }
  }
	
}

void Image::scale(double a)
{
	Image newIm;
	newIm.resize(a*this->width(),a*this->height());
 
	for (unsigned int i=0; i<newIm.width();i++)
	{
	   for (unsigned int j=0; j<newIm.height(); j++)
		{
		   newIm.getPixel(i,j)->s=(this->getPixel(i/a,j/a))->s;
		   newIm.getPixel(i,j)->h=(this->getPixel(i/a,j/a))->h;
		   newIm.getPixel(i,j)->a=(this->getPixel(i/a,j/a))->a;
		   newIm.getPixel(i,j)->l=(this->getPixel(i/a,j/a))->l;

		}
	}
	 *this=newIm;	
  } 

void Image::scale(unsigned w, unsigned h)
{
	unsigned a=this->width();
	unsigned b=this->height();
	double factor=1.0;
   if (w<h)
	   factor=(double)w/a;
   else
	   factor=(double)h/b;

 this->scale(factor);
}
