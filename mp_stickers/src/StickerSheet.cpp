#include "StickerSheet.h"
#include <algorithm>


// parameterized constructor
StickerSheet::StickerSheet(const Image& picture) {
    base_img = new Image(picture);
    
}


StickerSheet::StickerSheet(StickerSheet& other) {
    base_img = (other.base_img != nullptr) ? new Image(*(other.base_img)) : nullptr;

    stickers.resize(other.stickers.size(), nullptr);

    for (unsigned i = 0; i < other.stickers.size(); i++) {
        if (other.stickers[i] != nullptr) {
            stickers[i] = new Image(*(other.stickers[i]));
        }
    }
    x_coords = other.x_coords;
    y_coords = other.y_coords;
}


StickerSheet& StickerSheet::operator=(const StickerSheet& rhs) {
    // check for self assignment
    if (this == &rhs) {
        return *this;
    }

    delete base_img;
    for (unsigned i = 0; i < stickers.size(); i++) {
        delete stickers[i];
    }

    base_img = (rhs.base_img != nullptr) ? new Image(*(rhs.base_img)) : nullptr;

    return *this;

    stickers.resize(rhs.stickers.size(), nullptr);
    for (unsigned i = 0; i < rhs.stickers.size(); i++) {
        if (rhs.stickers[i] != nullptr) {
            stickers[i] = new Image(*(rhs.stickers[i]));
        }
    }

    // Copy coordinates
    x_coords = rhs.x_coords;
    y_coords = rhs.y_coords;

    return *this;
}


StickerSheet::~StickerSheet() {
    delete base_img;
    for (unsigned i = 0; i < stickers.size(); i++) {
        delete stickers[i];
    }
}

int StickerSheet::addSticker(Image& sticker, int x, int y) {
    stickers.push_back(new Image(sticker));
    x_coords.push_back(x);
    y_coords.push_back(y);
    return stickers.size() - 1;
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
    if (index >= stickers.size() || stickers[index] == nullptr) 
        return false;

    x_coords[index] = x;
    y_coords[index] = y;
    return true;
}


void StickerSheet::removeSticker(unsigned index) {
    if (index >= stickers.size())
        return;

    if (stickers[index] != nullptr) {
        delete stickers[index];       // Delete the dynamically allocated sticker
        stickers[index] = nullptr;    // Set the pointer to nullptr
    }
}


Image* StickerSheet::getSticker(unsigned index) {
    if (index >= stickers.size() || stickers[index] == nullptr) {
        return nullptr;
    }
    return stickers[index];
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
                cs225::HSLAPixel& p = stickers[i]->getPixel(x, y);
                // check alpha value of pixel before writing to canvas
                if (p.a == 0)
                    continue;

                canvas->getPixel(x - min_x + x_coords[i], y - min_y + y_coords[i]) = p;
            }
        }
    }

    return *canvas;
}