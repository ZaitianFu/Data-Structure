#include"StickerSheet.h"
#include "cs225/PNG.h"

int main() {

  Image base;
  base.readFromFile("alma.png");
  StickerSheet a = StickerSheet(base,5);

  Image p1;
  p1.readFromFile("1.png");
  Image p2;
  p1.readFromFile("2.png");
  Image p3;
  p1.readFromFile("3.png");
	a.addSticker (p1, 90, 90);
	a.addSticker (p2, 80, 80);
	a.addSticker (p3, 100, 100);
  a.render().writeToFile("myImage.png");
return 0 ;
}
