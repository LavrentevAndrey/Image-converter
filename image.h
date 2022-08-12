#pragma once
#include <stdio.h> 
#include <stdlib.h> 

// Pixel structure
typedef struct Pixel { 
    unsigned char r, g, b; // Colour is coding by 3 digits from 0 to 255 
} Pixel; 


// image structure
typedef struct Image { 
    int size_x, size_y; // Image dimentions 
    Pixel* data; // Pixels of image   
} Image;

void init_image(Image *image, int size_x, int size_y);
void free_image(Image *image);
// Reading/writing picture from file 
Image* read_image(const char* filename); 
void write_image(const Image *image, const char *filename); 

// Function that reverse colours of image
void reverse_colors(Image *image); 
// Function that mirroring image
void flip_vertically(Image *image); 
// Function that make picture only black and white
void black_white(Image *image);
