#ifndef STICKERSHEET_H
#define STICKERSHEET_H
#include "cs225/PNG.h"
#include "Image.h"

using namespace cs225;
class StickerSheet{
public:
Image**arr;
int curr;
int index;
void copy(const StickerSheet &other);
void clear();
StickerSheet (const Image &picture, unsigned max);
 ~StickerSheet ();
 StickerSheet (const StickerSheet &other);
const StickerSheet & 	operator= (const StickerSheet &other);
void 	changeMaxStickers (unsigned max);
int 	addSticker (Image &sticker, unsigned x, unsigned y);
bool 	translate (unsigned index, unsigned x, unsigned y);
void 	removeSticker (unsigned index);
Image * getSticker (unsigned index) const ;
Image 	render () const ;
int* xcoor;
int* ycoor;




};
#endif
