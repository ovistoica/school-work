#ifndef HOMEWORK_H
#define HOMEWORK_H
#include <stdio.h>
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
}rgb;

typedef struct {
    int height; 
    int width;
    char type; // 5 is .pgm
    rgb **rgb_mat;
    unsigned char **gray_mat;
    int max_val;
}image;

void readInput(const char * fileName, image *img);

void writeData(const char * fileName, image *img);

void resize(image *in, image * out);

void allocRGB(image *img);
void allocGrayscale(image *img);

void readRGB(image *img, unsigned char *buffer);
void readGrayscale(image *img, unsigned char *buffer);

void writeRGB(image *img, FILE *fp);
void writeGrayscale(image *img, FILE *fp);

void* resizeRGB(void* var);
void* resizeGrayscale(void* var);

#endif /* HOMEWORK_H */