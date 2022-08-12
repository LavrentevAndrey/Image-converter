#include <stdio.h> 
#include <stdlib.h> 
#include "image.h"

void init_image(Image *image, int size_x, int size_y) { 
    image->data = (Pixel*)calloc(size_x * size_y, sizeof(Pixel)); 
} 

void free_image(Image *image) {
    free(image->data);
}

Image* read_image(const char* filename) {
    const char format_lenth = 16;
    const unsigned char max_clour_value = 255;
    const char lenth_of_rgb = 3;
    Image* image = (Image*)malloc(sizeof(Image));

    FILE *fp; 
    int c, rgb_comp_color; 
    //open PPM file for reading 
    fp = fopen(filename, "rb"); 
    if (!fp) { 
        fprintf(stderr, "Unable to open file '%s'\n", filename); 
        exit(1); 
    } 

    // data for format information
    char buff[format_lenth]; 
    //read image format 
    if (!fgets(buff, sizeof(buff), fp)) { 
        perror(filename); 
        exit(1); 
    } 

    //check the image format 
    if (buff[0] != 'P' || buff[1] != '6') { 
        fprintf(stderr, "Invalid image format (must be 'P6')\n"); 
        exit(1); 
    } 

    //check for comments 
    c = getc(fp); 
    while (c == '#') { 
        while (getc(fp) != '\n'); 
        c = getc(fp); 
    } 

    ungetc(c, fp); 
    //read image size information 
    if (fscanf(fp, "%d %d", &(image->size_x), &(image->size_y)) != 2) { 
        fprintf(stderr, "Invalid image size (error loading '%s')\n", filename); 
        exit(1); 
    } 

    //read rgb component 
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) { 
        fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename); 
        exit(1); 
    } 

    //check rgb component depth 
    if (rgb_comp_color != max_clour_value) { 
        fprintf(stderr, "'%s' does not have 8-bits components\n", filename); 
        exit(1); 
    } 

    while (fgetc(fp) != '\n') ; 
    //memory allocation for pixel data 
    image->data = (Pixel*)malloc(image->size_x * image->size_y * sizeof(Pixel)); 

    //read pixel data from file 
    if (fread(image->data, lenth_of_rgb * image->size_x, image->size_y, fp) != (size_t)image->size_y) { 
        fprintf(stderr, "Error loading image '%s'\n", filename); 
        exit(1); 
    } 

    fclose(fp); 
    return image;
} 

void write_image(const Image *image, const char *filename) {
    const unsigned char max_clour_value = 255;
    const char lenth_of_rgb = 3;

    Pixel *data = image->data;
    int size_x = image->size_x;
    int size_y = image->size_y;

    FILE *fp; 
    //open file for output 
    fp = fopen(filename, "wb"); 
    if (!fp) { 
        fprintf(stderr, "Unable to open file '%s'\n", filename); 
        exit(1); 
    } 

    //write the header file 
    //image format 
    fprintf(fp, "P6\n"); 

    //image size 
    fprintf(fp, "%d %d\n", size_x, size_y); 

    // rgb component depth 
    fprintf(fp, "%d\n", max_clour_value); 

    // pixel data 
    fwrite(data, lenth_of_rgb * size_x, size_y, fp); 
    fclose(fp); 
} 


void reverse_colors(Image *image) {
    Pixel *data = image->data;
    int size_x = image->size_x;
    int size_y = image->size_y;

    if(!data) 
        return;  
    for (int i = 0; i < size_x * size_y; i++) { 
        data[i].r = 255 - data[i].r; 
        data[i].g = 255 - data[i].g; 
        data[i].b = 255 - data[i].b; 
    } 
} 


void flip_vertically(Image *image) { 
    Pixel *data = image->data;
    int size_x = image->size_x;
    int size_y = image->size_y;

    if(!data)  
        return; 

    Pixel temp; 
    for (int j = 0; j < size_y / 2; j++) { 
        for (int i = 0; i < size_x; i++) { 
            temp = data[i + j * size_x]; 
            data[i + j * size_x] = data[i + (size_y - j - 1) * size_x]; 
            data[i + (size_y - j - 1) * size_x] = temp; 
        } 
    } 
}

void black_white(Image* image) {
    Pixel *data = image->data;
    int size_x = image->size_x;
    int size_y = image->size_y;

    if(!data)  
        return; 

    int mean = 0;
    for (int i = 0; i < size_y * size_x; i++) { 
        mean = (data[i].r + data[i].g + data[i].b) / 3;
        data[i].r = mean;
        data[i].g = mean;
        data[i].b = mean;
    }
}
