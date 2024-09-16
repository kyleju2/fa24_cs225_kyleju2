#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
using namespace std;

int main() {




  Image alma;
  alma.readFromFile("../data/alma.png");
  StickerSheet alma_sheet(alma);


  // adding a sticker
  Image blockI;
  blockI.readFromFile("../data/i.png");
  alma_sheet.addSticker(blockI, 0,0);

    cout << &blockI << endl;
    cout << alma_sheet.getSticker(0) << endl;


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


  alma_sheet.render().writeToFile("../data/image1.png");
  // alma_sheet_2.render().writeToFile("image2.png");


  return 0;
}
