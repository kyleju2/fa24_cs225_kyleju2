/**
 * @file sketchify.cpp
 * Implementation of the sketchify function.
 */
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wreturn-stack-address"
#include <cstdlib>
#include <cmath>
#include <iostream>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

/**
 * Creates a new output image.

 * @param w width of the image
 * @param h height of the image

 * @return a pointer to the newly-created image
 */
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

/**
 * Used to customize the color of the sketchified image.

 * @return a pointer to the color to use when sketchifying
 */
HSLAPixel* myFavoriteColor() {
    HSLAPixel p(334, 0.8, 0.5);
    return &p;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG();

    // std::cout << "Reached line 42" << '\n';
    // seg fault caused by dereferencing a null ptr 
    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();

    // std::cout << "Reached line 47" << '\n';

    // Create out.png

    // std::cout << "Reached line 52" << '\n';
    PNG* output = new PNG(width, height);
    // setupOutput(width, height);
    // std::cout << "Reached line 55" << '\n';

    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor();
    // std::cout << "Reached line 59" << '\n';
    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (unsigned y = 1; y < height; y++) {
        for (unsigned x = 1; x < width; x++) {
            // Calculate the pixel difference
            // std::cout << x << ' ' << y << '\n';
            HSLAPixel& prev = original->getPixel(x - 1, y - 1);
            HSLAPixel& curr = original->getPixel(x, y);
            double diff = std::fabs(curr.h - prev.h);
            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            // std::cout << "Reached line 70" << '\n';
            HSLAPixel& currOutPixel = output->getPixel(x, y);
            // std::cout << "Reached line 72" << '\n';
            if (diff > 20) {
                currOutPixel = *myPixel;
            }
        }
    }

    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    // myPixel is defined on the stack and can't be deleted
    // delete myPixel;
    delete output;
    delete original;
    
}
