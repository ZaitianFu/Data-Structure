#include "StickerSheet.h"
#include <cmath>

StickerSheet::StickerSheet(const Image & picture, unsigned max)
{
	arr=new Image*[max+2];

	for (int i=0; i<max+2; i++)
	{arr[i]=NULL;}

	arr[0]=new Image();
	*arr[0]=picture;
	index=max+2;
	curr=1;	
	xcoor= new int [max+2];
	ycoor= new int [max+2];
	for (int i=0; i<max+2;i++)	{
         	xcoor[i]=0;
		ycoor[i]=0;
	}
}

void StickerSheet::clear(){
	for (int i=0; i<index;i++){
	if (arr[i] != NULL){
		delete arr[i];
		arr[i]=NULL;
	}
}
	delete[]arr;
	arr=NULL;
	if (xcoor !=NULL)
            {delete[] xcoor; xcoor=NULL;}
	if (ycoor !=NULL)
            {delete[] ycoor; ycoor=NULL;}



}

StickerSheet::~StickerSheet()
{
 clear();
}

void StickerSheet::copy(const StickerSheet &other){
	arr=new Image*[other.index];
	xcoor= new int [other.index];
	ycoor= new int [other.index];	
	index= other.index;
	for (int i=0; i<index;i++)	{
	xcoor[i]=0;
	ycoor[i]=0;
}
 for (int i=0; i<other.index;i++){
	arr[i]=NULL;
}
for (int i=0;i<index;i++){
	if (other.arr[i]!=NULL){
	arr[i]=new Image;
	*arr[i]=*(other.arr[i]);
	xcoor[i]=other.xcoor[i];
	ycoor[i]=other.ycoor[i];
	
   }
 }
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
	if (this!= &other){
	clear();
	copy(other);
  }
  return *this;
}

void StickerSheet::changeMaxStickers (unsigned max){
	if (max+2==index)
		return;
	else if (max+2>index){
	   Image** temp = new Image* [max+2];
	   int* txor = new int[max+2];
	   int* tyor = new int[max+2];

	   for (int i=0; i<index; i++){
	    temp[i]=arr[i];
	    txor[i]= xcoor[i];
	    txor[i]= xcoor[i];

	}
	
	for (int i=0; i<index;i++)
	    temp[i]=NULL;
	
	
	clear();
	arr=temp;
	xcoor=txor;
	ycoor=tyor;
	index=max+2;
	return;
  }
 	else{
	Image** temp= new Image*[max+2];
	int* txor= new int[max+2];
	int* tyor= new int[max+2];
	curr=0;
	for (int i=0; i<max+2; i++){
		temp[i]=arr[i];
		txor[i]=xcoor[i];
		tyor[i]=ycoor[i];
		curr++;
}

	clear();
	arr=temp;
	xcoor=txor;
	ycoor=tyor;
	index=max+2;
}
	return;	
}


int 	StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
   for(int i=0;i<index;i++){
	if (arr[i]==NULL){
	   arr[i]=new Image;
	   *arr[i]= sticker;
 	   xcoor[i]=x;
	   ycoor[i]=y;
	return i;
	}

   }
if (curr+1>index)
	return -1;
else {
	arr[curr]=new Image;
	*arr[curr]=sticker;
	xcoor[curr]=x;
	ycoor[curr]=y;
	curr=curr+1;
	return curr-1;

   }
}

bool 	StickerSheet::translate (unsigned ind, unsigned x, unsigned y){
	if ((ind>index)|| (arr[ind]==NULL))
	    return false;
	
        xcoor[ind]=x;
	ycoor[ind]=y;
	return true;
}


void  StickerSheet::	removeSticker (unsigned ind){
	if ((ind>index)|| (arr[ind]==NULL))
	    return ;

	delete arr[ind];
	arr[ind]=NULL;

}


Image * StickerSheet:: getSticker (unsigned ind) const{
	if ((ind>index)|| (arr[ind]==NULL))
	    return NULL;
	else
	    return arr[ind];


}

Image StickerSheet::render () const {
	int nheight=0;
	int nwidth=0;
   for (int i=0; i<index;i++){
	if (arr[i]!=NULL){
	int currheight = arr[i]->height()+ycoor[i];
	int currwidth = arr[i]->width()+xcoor[i];
		if (currheight>nheight)
			currheight=nheight;
		if (currwidth>nwidth)
			currwidth=nwidth;
	}
}

Image output;
output.resize(nwidth,nheight);
HSLAPixel* current;

for (int c=0;c<index;c++){
    if (arr[c]!=NULL){
	int objwidth=arr[c]->width();
	int objheight=arr[c]->height();
	int x=xcoor[c];
	int y=ycoor[c];


	for(int i=0;i<objwidth;i++){
		for (int j=0;i<objheight;j++){
		current=output.getPixel(i+x,j+y);

		if (arr[c]->getPixel(i,j)->a!=0){
		   current->a= arr[c]->getPixel(i,j)->a;
		   current->h= arr[c]->getPixel(i,j)->h;
		   current->l= arr[c]->getPixel(i,j)->l;
		   current->s= arr[c]->getPixel(i,j)->s;

		}

		}

	}

   }

}
		return output;
}
