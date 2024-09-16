#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
using namespace std;

int main() {
  Image alma; alma.readFromFile("../data/alma.png");
  Image i;    i.readFromFile("../data/i.png");

  StickerSheet sheet(alma);

  /**
   * For testing deep copy of base image
   * The {...} are used for a block statement
   * and are intentional
   */
  // {
  //   Image almaDuplicate = alma;

  //   StickerSheet sheetDuplicate(almaDuplicate);
  //   sheet = sheetDuplicate;
  // }

  cout << "layers: " << sheet.layers() << endl;


  sheet.addSticker(i, 800, 200);
  sheet.addSticker(i, 50, 500);
  cout << "layers: " << sheet.layers() << endl;
 

  sheet.removeSticker(1);

  const Image &renderXBound = sheet.render();
  sheet.render().writeToFile("../data/renderx.png");
  cout << "renderxBound dims: " << renderXBound.width() << " " << renderXBound.height() << endl; 
  cout << i.width() + 800 << endl;
  // REQUIRE( renderXBound.width() == i.width() + 800 );
  // REQUIRE( renderXBound.height() == alma.height() );

  // checkStickerPlacement(i, renderXBound, 800, 200);

  sheet.removeSticker(0);

  // REQUIRE( sheet.render() == alma );

  sheet.addSticker(i, 20, 500);

  const Image &renderYBound = sheet.render();
  sheet.render().writeToFile("../data/rendery.png");
  cout << "renderyBound dims: " << renderYBound.width() << " " << renderYBound.height() << endl; 
  cout << i.height() + 500 << endl;
  // REQUIRE( renderYBound.width() == alma.width() );
  // REQUIRE( renderYBound.height() == i.height() + 500 );

  // checkStickerPlacement(i, renderYBound, 20, 500);

  sheet.removeSticker(0);

  // REQUIRE( sheet.render() == alma );

  sheet.addSticker(i, 800, 200);
  sheet.addSticker(i, -100, -500);

  const Image &renderXYBound = sheet.render();
  sheet.render().writeToFile("../data/renderxy.png");
  cout << "renderxyBound dims: " << renderXYBound.width() << " " << renderXYBound.height() << endl; 
  // cout << i.width() + 800 << endl;
  // checkStickerPlacement(i, renderXYBound, 900, 700);
  // checkStickerPlacement(i, renderXYBound, 0, 0);
  sheet.removeSticker(3);
  sheet.removeSticker(4);
  sheet.removeSticker(5);

  cout << "sheet.render() == alma | pass?  :  " << to_string(sheet.render() == alma ) << endl;


  return 0;
}
