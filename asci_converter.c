#include "asci_converter.h"

char** convert_image2str(Image* image, int x_size_of_text_image, int y_size_of_text_image, Pixel **p_block_colur) {
    char **output = (char**)malloc(y_size_of_text_image * sizeof(char*));
    for (int i = 0; i < y_size_of_text_image; i++)
        output[i] = (char*)malloc(x_size_of_text_image * sizeof(char));
    Pixel* data = image->data;
    int size_x = image->size_x, size_y = image->size_y;
    int block_x = size_x / x_size_of_text_image;
    int block_y = size_y / y_size_of_text_image;
    Pixel *block_colour = (Pixel*)calloc(x_size_of_text_image * y_size_of_text_image, sizeof(Pixel));

    Pixel **image_data = (Pixel**)malloc(size_y * sizeof(Pixel*));
    for (int i = 0; i < size_y; i++)
        image_data[i] = data + i * size_x;
    for (int i = 0; i < y_size_of_text_image; i++) {
        for (int j = 0; j < x_size_of_text_image; j++) {
            output[i][j] = symbol_picker(block_mean(image_data, j * block_x, i * block_y, block_x, block_y, block_colour + i * x_size_of_text_image + j));
            //printf("%c", output[i][j]);
        }
        //printf("\n");
    }
    printf("asd\n");
    *p_block_colur = block_colour;
    printf("asd\n");
    free(image_data);
    printf("asd\n");
    return output;
}

unsigned char block_mean(Pixel **data, int x, int y, int length, int high, Pixel *block_colour) {
    unsigned long long int sumr = 0, sumg = 0, sumb = 0;
    for (int i = y; i < y + high; i++) {
        for (int j = x; j < x + length; j++) {
            sumr += data[i][j].r;
            sumg += data[i][j].g;
            sumb += data[i][j].b;
        }
    }
    block_colour->r = sumr / (high * length);
    block_colour->g = sumg / (high * length);
    block_colour->b = sumb / (high * length);
    return (block_colour->r + block_colour->g + block_colour->b) / 3;
}

char symbol_picker(unsigned char colour) {
    char out = details[details_length - 1];
    float step = 255 / details_length;
    for (int i = 0; i < details_length; i++) {
        if (colour >= i * step && colour < (i + 1) * step)
            return details[i];
    }
    return out;
}

void asci_print(char **symbols, int length, int high, Pixel *block_colur) {
    for (int i = 0; i < high; i++) {
        for (int j = 0; j < length; j++) {
            printf("\033[38;2;%d;%d;%dm", block_colur[i * length + j].r, block_colur[i * length + j].g, block_colur[i * length + j].b);
            printf("%c", symbols[i][j]);
        }
        printf("\n");
    }
}

void free_asci(char **data, int length) {
    for (int i = 0; i < length; i++)
        free(data[i]);
    free(data);
    return;
}