#include "StickerSheet.h"
#include <algorithm>


// parameterized constructor
StickerSheet::StickerSheet(const Image& picture) {
    base_img = new Image(picture); // create a heap-allocated image and store the pointer as the background
    // I think this is a deep copy?? not 100% sure though
}


StickerSheet::~StickerSheet() {
    for (size_t i = 0; i < stickers.size(); i++) {
        delete stickers[i];
    }
}


int StickerSheet::addSticker(Image& sticker, int x, int y) {
    stickers.push_back(new Image(sticker));
    x_coords.push_back(x);
    y_coords.push_back(y);
    return stickers.size();
    // add image pointer to stickers, and add coords to respective vectors
}


int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y) {
    // if layer is greater than the size of the stickers vector
    if (layer >= stickers.size()) {
        addSticker(sticker, x, y);
        return stickers.size();
    }
    
    stickers[layer] = new Image(sticker);
    x_coords[layer] = x;
    y_coords[layer] = y;

    return layer;
    
}


bool StickerSheet::translate(unsigned index, int x, int y) {
    if (stickers.at(index) == nullptr) {return false;}
    if (index >= stickers.size()) {return false;}

    x_coords[index] = x;
    y_coords[index] = y;
    return true;
}


void StickerSheet::removeSticker(unsigned index) {
    if (index < 0 || index + 1 > stickers.size()) {
        return;
    }

    delete stickers[index];
    stickers[index] = nullptr;
    x_coords[index] = 0;
    y_coords[index] = 0;
}


Image* StickerSheet::getSticker(unsigned index) {
    if (index < 0 || index + 1 > stickers.size()) {
        return nullptr;
    }
    return stickers.at(index);

}


int StickerSheet::layers() const {
    return stickers.size();
}


Image StickerSheet::render() const {
    auto x_bounds = std::minmax_element(x_coords.begin(), x_coords.end());
    auto y_bounds = std::minmax_element(x_coords.begin(), x_coords.end());

    int width = *x_bounds.second - *x_bounds.first;
    int height = *y_bounds.second - *y_bounds.first;

    Image* rend  = new Image(width, height); 
    return *rend;
    // for (auto i = 0; i < stickers.size(); i++) {

    // }
}