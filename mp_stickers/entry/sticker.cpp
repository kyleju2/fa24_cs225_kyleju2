#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
using namespace std;

int main() {

Image alma;     alma.readFromFile("../data/alma.png");
  Image i;        i.readFromFile("../data/i.png");
  Image expected; expected.readFromFile("../data/expected-3.png");

  StickerSheet sheet(alma);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40, 200);
  sheet.addSticker(i, 60, 200);
  sheet.addSticker(i, 80, 200);
  sheet.addSticker(i, 100, 200);
  sheet.addSticker(i, 120, 200);
  sheet.addSticker(i, 140, 200);
  sheet.removeSticker(3);
  sheet.translate(0, 0, 0);


  // Image alma;
  // alma.readFromFile("../data/alma.png");
  // // std::cout << alma.width() << ' ' << alma.height();
  // StickerSheet alma_sheet(alma);


  // // adding a sticker
  // Image blockI;
  // blockI.readFromFile("../data/i.png");
  // alma_sheet.addSticker(blockI, 0,0);


  // Image penguin;
  // penguin.readFromFile("../data/penguin.png");
  // // alma_sheet.addSticker(penguin, 0, 0);


  // cout << alma_sheet.getSticker(1) << endl;
  // cout << "layers: " << alma_sheet.layers() << endl;
  // alma_sheet.translate(1, 500, 250);
  // StickerSheet alma_sheet_2(alma_sheet);
  // cout << &alma_sheet_2 << ' ' << &alma_sheet << endl;
  // cout << alma_sheet_2.getSticker(1) << ' ' << alma_sheet.getSticker(1) << endl;
  // alma_sheet_2.translate(0, 500, 250);


  sheet.render().writeToFile("../data/image1.png");
  // alma_sheet_2.render().writeToFile("image2.png");


  return 0;
}
