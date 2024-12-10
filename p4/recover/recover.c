#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./recover FILE\n");
    return 1;
  }

  FILE *card = fopen(argv[1], "r");

  if (card == NULL) {
    printf("card is not open.");
    return 2;
  }

  uint8_t buffer[512];

  bool found_jpg = false;
  int count = 0;
  char filename[10];
  FILE *output = NULL;

  while (fread(buffer, 512, 1, card) == 1) {
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0) {
      if (found_jpg) {
        fclose(output);
      } else {
        found_jpg = true;
      }
      sprintf(filename, "%03d.jpg", count);
      output = fopen(filename, "w");
      if (output == NULL) {
        fclose(card);
        printf("cannot create %s", filename);
        return 3;
      }
      count++;
    }
    if (found_jpg) {
      fwrite(buffer, 512, 1, output);
    }
  }
  fclose(card);
  if (found_jpg) {
    fclose(output);
  }
  return 0;
}
