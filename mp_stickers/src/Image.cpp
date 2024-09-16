#include "Image.h"
#include <cmath>
#include <iostream>
#define ILLINI_ORANGE 11;
#define ILLINI_BLUE 216;

using namespace std;


void Image::lighten() {
    unsigned width_ = width();
    unsigned height_ = height();

    for (unsigned x = 0; x < width_; x++) {
        for (unsigned y = 0; y < height_; y++) {
            cs225::HSLAPixel & p = getPixel(x, y); 
            if (p.l + .1 < 1)
                p.l += .1;
            else    
                p.l = 1;
        }
    }
}


void Image::lighten(double amount) {
    unsigned width_ = width();
    unsigned height_ = height();

    for (unsigned x = 0; x < width_; x++) {
        for (unsigned y = 0; y < height_; y++) {
            cs225::HSLAPixel & p = getPixel(x, y); 
            if (p.l + amount < 1)
                p.l += amount;
            else    
                p.l = 1;
        }
    }
}


void Image::darken() {
    unsigned width_ = width();
    unsigned height_ = height();

    for (unsigned x = 0; x < width_; x++) {
        for (unsigned y = 0; y < height_; y++) {
            cs225::HSLAPixel & p = getPixel(x, y);
            if ((p.l - .1) > 0)
                p.l -= .1;
            else
                p.l = 0;
        }
    }
}


void Image::darken(double amount) {
    unsigned width_ = width();
    unsigned height_ = height();

    for (unsigned x = 0; x < width_; x++) {
        for (unsigned y = 0; y < height_; y++) {
            cs225::HSLAPixel & p = getPixel(x, y);
            if ((p.l - amount) > 0)
                p.l -= amount;
            else
                p.l = 0;
        }
    }
}


void Image::desaturate() {
    unsigned width_ = width();
    unsigned height_ = height();

    for (unsigned x = 0; x < width_; x++) {
        for (unsigned y = 0; y < height_; y++) {
            cs225::HSLAPixel & p = getPixel(x, y);
            if ((p.s - .1) > 0)
                p.s -= .1;
            else
                p.s = 0;
        }
    }
}


void Image::desaturate(double amount) {
    unsigned width_ = width();
    unsigned height_ = height();

    for (unsigned x = 0; x < width_; x++) {
        for (unsigned y = 0; y < height_; y++) {
            cs225::HSLAPixel & p = getPixel(x, y); 
            if ((p.s - amount) > 0)
                p.s -= amount; 
            else
                p.s = 0;
        }
    }
}


void Image::saturate() {
    unsigned width_ = width();
    unsigned height_ = height();

    for (unsigned x = 0; x < width_; x++) {
        for (unsigned y = 0; y < height_; y++) {
            cs225::HSLAPixel & p = getPixel(x, y); 
            if ((p.s + .1) < 1)
                p.s += .1; 
            else
                p.s = 1;
        }
    }
}


void Image::saturate(double amount) {
    unsigned width_ = width();
    unsigned height_ = height();

    for (unsigned x = 0; x < width_; x++) {
        for (unsigned y = 0; y < height_; y++) {
            cs225::HSLAPixel & p = getPixel(x, y); 
            if ((p.s + amount) < 1)
                p.s += amount; 
            else
                p.s = 1;
        }
    }
}


void Image::grayscale() {
    unsigned width_ = width();
    unsigned height_ = height();

    for (unsigned x = 0; x < width_; x++) {
        for (unsigned y = 0; y < height_; y++) {
            getPixel(x, y).s = 0;
        }
    }
}


void Image::illinify() {
    // using constants, defined as preprocessor directives
    unsigned width_ = width();
    unsigned height_ = height();

    for (unsigned x = 0; x < width_; x++) {
        for (unsigned y = 0; y < height_; y++) {
            cs225::HSLAPixel & p = getPixel(x, y);
            if ((p.h > 113.5) && (p.h < 293.5)) {
                p.h = ILLINI_BLUE;
            }   
            else {
                p.h = ILLINI_ORANGE;
            }
        }
    }
}


void Image::rotateColor(double degrees) {
    unsigned width_ = width();
    unsigned height_ = height();
        
    for (unsigned x = 0; x < width_; x++) {
        for (unsigned y = 0; y < height_; y++) {
            cs225::HSLAPixel & p = getPixel(x, y);
            p.h += degrees;
            if (p.h >= 360) {
                p.h = std::fmod(p.h, 360.0);
            }
            else if (p.h < 0) {
                p.h += 360; 
            }
        }
    }
}


void Image::scale(double factor) {
    unsigned width_ = width();
    unsigned height_ = height();

    double new_width_ = width_*factor;
    double new_height_ = height_*factor;

    double ratio; // check to see if the ratio of height change or width change is greater (mainly for the other scale() definition)
    if ((width_ / new_width_) < (height_ / new_height_)) {
        ratio = width_ / new_width_;
    }
    else {
        ratio = height_ / new_height_;
    }

    Image current_img = *this; // store current image before scaling
    resize(new_width_, new_height_); // resize image stored in *this
    for (unsigned x = 0; x < new_width_; x++) {
        for (unsigned y = 0; y < new_height_; y++) {
            cs225::HSLAPixel& curr = getPixel(x, y);
            curr = current_img.getPixel(x*ratio, y*ratio);
        }
    }
}


void Image::scale(unsigned w, unsigned h) {
    double width_ = width();
    double height_ = height();

    double scale_w = (double) w / width_;
    double scale_h = (double) h / height_;

    if (scale_w < scale_h) {
        scale(scale_w);
    }
    else {
        scale(scale_h);
    }
}