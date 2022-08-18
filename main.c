#include "image.h"
#include "asci_converter.h"
#define MAXLEN 100

int main() {
     char pic[MAXLEN];
     printf("PPM picture name:\n");
     scanf("%s", pic);
     Image* image = read_image(pic);
     //black_white(image);
     int x, y;
     printf("Size of picture in letter (x, y): \n");
     scanf("%d %d", &x, &y);
     Pixel tmp;
     Pixel *ptmp = &tmp;
     Pixel **block_colour = &ptmp;
     char **asci = convert_image2str(image, x, y, block_colour);
     asci_print(asci, x, y, *block_colour);
     
     free_asci(asci, y);
     free_image(image);
     free(*block_colour);
     return 0;
}