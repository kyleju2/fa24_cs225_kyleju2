/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}
// renamed parameters... hope it still works???
MosaicCanvas* mapTiles(SourceImage const& source,
                       vector<TileImage>& tiles)
{
    if (tiles.size() == 0)
        return NULL;
    

    int rows = source.getRows();
    int cols = source.getColumns();
    MosaicCanvas* mosaic = new MosaicCanvas(rows, cols); // allocate new canvas with dimensions

    std::vector<Point<3>> tileColors;
    std::map<Point<3>, int> colorToTileMap; // store point and index in tiles of its match

    // populate tileColors vector
    for (size_t i = 0; i < tiles.size(); i++) {
        tileColors.push_back(convertToXYZ(tiles[i].getAverageColor()));
        colorToTileMap[tileColors[i]] = i;
    }

    // create new kd tree
    KDTree<3> colorTree(tileColors);

    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            Point<3> regionColor = convertToXYZ(source.getRegionColor(x, y)); // get RGB values
            Point<3> nearestTileColor = colorTree.findNearestNeighbor(regionColor);
            mosaic->setTile(x, y,  &tiles[colorToTileMap[nearestTileColor]]);
        }
    }

    return mosaic;
}

