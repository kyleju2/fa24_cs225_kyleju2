#include "StickerSheet.h"
#include <algorithm>


// parameterized constructor
StickerSheet::StickerSheet(const Image& picture) {
    base_img = new Image(picture);
}

StickerSheet::StickerSheet(const StickerSheet& other) {
    base_img = new Image(*(other.base_img));
    for (unsigned i = 0; i < other.stickers.size(); i++) {
        x_coords[i] = other.x_coords[i];
        y_coords[i] = other.y_coords[i];
        stickers[i] = new Image(*(other.stickers[i]));
    }
}


StickerSheet::~StickerSheet() {
    for (size_t i = 0; i < stickers.size(); i++) {
        delete stickers[i];
    }

    delete base_img;
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
    if (layer > stickers.size()) {
        addSticker(sticker, x, y);
        return stickers.size() - 1; // size - 1 == index
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
    int min_x = 0;
    int min_y = 0;
    int max_x = base_img->width() - 1;
    int max_y = base_img->height() - 1;

    for (unsigned i = 0; i < stickers.size(); i++) {
        if (stickers[i] != nullptr) {
            min_x = std::min(min_x, x_coords[i]);
            min_y = std::min(min_y, y_coords[i]);
            max_x = std::max(max_x, x_coords[i] + (int)stickers[i]->width() - 1);
            max_y = std::max(max_y, y_coords[i] + (int)stickers[i]->height() - 1);            
        }
    }
    // calculate the new height and width based on difference
    // between the max and mins of x and y
    int new_width = max_x - min_x + 1;
    int new_height = max_y - min_y + 1;

    // create render() output based on dimensions calculated above

    Image* canvas = new Image(new_width, new_height);

    // for (unsigned i = 0; i < width_ * height_; i++) {
    //   imageData_[i] = other.imageData_[i];
    // }
    // copy base image over to the new rendered image 
    for (unsigned x = 0; x < base_img->width(); x++) {
        for (unsigned y = 0; y < base_img->height(); y++) {
            canvas->getPixel(x - min_x, y - min_y) = base_img->getPixel(x, y);
        }
    }


    for (unsigned i = 0; i < stickers.size(); i++) {
        if (stickers[i] == nullptr) 
            continue;

        for (unsigned x = 0; x < stickers[i]->width(); x++) {
            for (unsigned y = 0; y < stickers[i]->height(); y++) {
                canvas->getPixel(x - min_x + x_coords[i], y - min_y + y_coords[i]) = stickers[i]->getPixel(x, y);
            }
        }
    }

    return *canvas;
}