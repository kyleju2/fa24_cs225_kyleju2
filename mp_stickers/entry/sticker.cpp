#include "Image.h"
#include "StickerSheet.h"
#include <iostream>

int main() {

  Image alma;
  alma.readFromFile("../data/alma.png");
  std::cout << alma.width() << ' ' << alma.height();
  StickerSheet alma_sheet(alma);




  // // // adding a sticker
  // Image blockI;
  // blockI.readFromFile("../data/i.png");
  // alma_sheet.addSticker(blockI, -100, -100);


  // Image blockI2;
  // blockI2.readFromFile("../data/i.png");
  // alma_sheet.addSticker(blockI2, 900, 600);

  
  
  




  alma_sheet.render().writeToFile("testingfml.png");



  return 0;
}
