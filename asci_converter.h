#pragma once
#include "image.h" 

static const char* details = {".'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"};
static const int details_length = 69;

char** convert_image2str(Image* image, int x_size_of_text_image, int y_size_of_text_image, Pixel **p_block_colur);

unsigned char block_mean(Pixel **data, int x, int y, int length, int high, Pixel *block_colour);

char symbol_picker(unsigned char colour);

void asci_print(char **data, int length, int high, Pixel *block_colur);

void free_asci(char **data, int length);