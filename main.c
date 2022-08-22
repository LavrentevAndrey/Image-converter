#include "image.h"
#include "asci_converter.h"
#include <string.h>
#include <unistd.h>
#define MAXLEN 100

int main() {
     printf("\x1B[40m");
     int mode = 1;
     printf("Select mode: (1 - ppm) (2 - ppm gif)\n");
     scanf("%d", &mode);
     if (mode == 1) {
          char pic[MAXLEN];
          printf("PPM picture name:\n");
          scanf("%s", pic);
          Image* image = read_image(pic);
          //black_white(image);
          int x, y;
          printf("Size of picture in letter (x, y): \n");
          scanf("%d %d", &x, &y);
          Pixel **block_colour;
          char **asci = convert_image2str(image, x, y, block_colour);
          asci_print(asci, x, y, *block_colour);
          
          free_asci(asci, y);
          free_image(image);
          free(*block_colour);
     }
     else if (mode == 2) {
          printf("PPM pictures amount:\n");
          int amount;
          scanf("%d", &amount);
          Image **images = (Image**)calloc(amount, sizeof(Image*));
          char file_name[20];
          char path[] = "data/";
          char type[] = ".ppm";
          char file_path[26];
          for (int i = 0; i < amount; i++) {
               strcpy(file_path, path);
               sprintf(file_name, "%d", i);
               strcat(file_path, file_name);
               strcat(file_path, type);
               //printf("%s ", file_path);
               images[i] = read_image(file_path);
          }

          Pixel ***block_colours = (Pixel***)calloc(amount, sizeof(Pixel**));
          for (int i = 0; i < amount; i++) {
               block_colours[i] = (Pixel**)malloc(sizeof(Pixel*));
          }

          int x, y;
          printf("Size of picture in letter (x, y): \n");
          scanf("%d %d", &x, &y);

          char ***images_asci = (char***)calloc(amount, sizeof(char**));
          for (int i = 0; i < amount; i++) {
               images_asci[i] = convert_image2str(images[i], x, y, block_colours[i]);
          }

          int time = 10;
          while (time--) {
               for (int i = 0; i < amount; i++) {
                    asci_print(images_asci[i], x, y, *(block_colours[i]));
                    usleep(80000);
                    printf("\033[2J");
               }
          }

          for (int i = 0; i < amount; i++) {
               free_asci(images_asci[i], y);
               free_image(images[i]);
               free(*(block_colours[i]));
               free(block_colours[i]);
          }
          free(block_colours);
     }
     else {
          printf("Incorrect mode\n");
     }
     return 0;
}