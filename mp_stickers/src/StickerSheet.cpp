#include "StickerSheet.h"


// parameterized constructor
StickerSheet::StickerSheet(const Image& picture) {
    background = new Image(picture); // create a heap-allocated image and store the pointer as the background
    // I think this is a deep copy?? not 100% sure though
}


int StickerSheet::addSticker(Image& sticker, int x, int y) {
    stickers.push_back(new Image(sticker));
    x_coords.push_back(x);
    y_coords.push_back(y);
    // add image pointer to stickers, and add coords to respective vectors
}


int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y) {
    if (layer > stickers.size()) {
        stickers.push_back(new Image(sticker));
        x_coords.push_back(x);
        y_coords.push_back(y);
    }
}


bool StickerSheet::translate(unsigned index, int x, int y) {

}


void StickerSheet::removeSticker(unsigned index) {

}


Image* StickerSheet::getSticker(unsigned index) {

}


int StickerSheet::layers() const {

}


Image StickerSheet::render() const {

}