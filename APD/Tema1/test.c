#include "homework.c"
#include "homework.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[] = "./in/lenna_color.pnm";
    char filename_out[] = "./out_res_color.pnm";
    image my_img;
    image out_img;
    readInput(filename, &my_img);
    resize(&my_img, &out_img);
    writeData(filename_out, &out_img);
    freeMemory(&my_img);
    freeMemory(&out_img);
    return 0;
}

