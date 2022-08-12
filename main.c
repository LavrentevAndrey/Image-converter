#include "image.h"
#include "asci_converter.h"
#define MAXLEN 100

int main() {
     char pic[MAXLEN];
     scanf("%s", pic);
     Image* image = read_image(pic);
     black_white(image);
     int x, y;
     scanf("%d %d", &x, &y);
     char **asci = convert_image2str(image, x, y);
     asci_print(asci, x, y);
     
     free_asci(asci, y);
     free_image(image);
     return 0;
}