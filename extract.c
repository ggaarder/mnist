#include <tcclib.h>

#define LABELS "train-labels.idx1-ubyte"
#define IMGS "train-images.idx3-ubyte"
#define IMGDIR "imgs"

uint32_t toggledn(uint32_t value) // Change Endianness
{
    uint32_t result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}

int main() {
  FILE *fp = fopen(LABELS, "rb");
  char *labels;
  uint32_t i;
  uint32_t n;
  uint32_t r, c;
  char b;
  
  fread(&i, 4, 1, fp);
  i = toggledn(i);
  printf("magic number: 0x%08X(%d)\n", i, i);
  fread(&i, 4, 1, fp);
  i = toggledn(i);
  printf("number of items: %d\n", i);

  n = i;
  labels = malloc(n);
  for (i = 0; i < n; ++i)
    fread(labels+i, 1, 1, fp);

  fp = fopen(IMGS, "rb");
  fread(&i, 4, 1, fp);
  i = toggledn(i);
  printf("magic number: 0x%08X(%d)\n", i, i);
  fread(&i, 4, 1, fp);
  i = toggledn(i);
  printf("number of images: %d\n", i);
  n = i;
  fread(&i, 4, 1, fp);
  i = toggledn(i);
  printf("number of rows: %d\n", i);
  r = i;
  fread(&i, 4, 1, fp);
  i = toggledn(i);
  printf("number of cols: %d\n", i);
  c = i;

  char *img = malloc(sizeof(char)*r*c);
  
  for (i = 0; i < n; ++i) {
    FILE *pgm;
    char fn[20];
    int row, col;
    sprintf(fn, IMGDIR "/%d-%d.pgm", i+1, labels[i]);
    printf("extracting %s\n", fn);
    pgm = fopen(fn, "wb");
    fprintf(pgm, "P2\n%d %d\n255\n", c, r);
    fread(img, r*c, 1, fp);
    
    for (row = 0; row < r; ++row) {
      for (col = 0; col < c; ++col) {
        // in MNIST 0 is white and 255 is black
        // in PGM 0 is black and the max value is white
        fprintf(pgm, "%03d ", 255-img[row*c+col]);
      }
      fprintf(pgm, "\n");
    }

    fclose(pgm);
  }

  free(img);
  free(labels);
}
