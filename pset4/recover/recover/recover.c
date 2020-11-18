#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* the first three bytes of a jpeg are 0xff 0xd8 0xff and there forth byte is between 0xe0 and 0xef
each block is 512 bytes */

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./recover image\n");
        return 1;
    }

    unsigned char buffer[512];
    int jpeg = 0;
    char *filename = malloc(9);
    FILE *photo;
    bool begin = false;

    FILE *card = fopen(argv[1], "r");

    if (card == NULL) {
        printf("Something has gone fatally wrong!\n");
        return 1;
    }

    while (fread(buffer, 512, 1, card)) {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef) {
            begin = true;
            if (jpeg != 0) {
                fclose(photo);
            }
            sprintf(filename, "%03d.jpg", jpeg);
            photo = fopen(filename, "a");
            jpeg++;
        }
        if (begin) {
            for (int i = 0; i < 512; i++) {
                fprintf(photo, "%c", buffer[i]);
            }
        }
    }
    fclose(card);
    free(filename);

    return 0;
}