#include "homework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

int num_threads;
int resize_factor;
image *global_in;
image *global_out;

int min(int a, int b) {
	return (a < b)? a : b;
}

void allocGrayscale(image *img) {
    int i;
    img->gray_mat = (unsigned char **)malloc(sizeof(unsigned char *) * img->height);
    for(i = 0; i < img->height; ++i) {
        img->gray_mat[i] = (unsigned char *)malloc(img->width);
    }
    img->rgb_mat = NULL;

}

void allocRGB(image *img) {
    int i;
    img->rgb_mat = (rgb **)malloc(sizeof(rgb *) * img->height);
    for(i = 0; i < img->height; ++i) {
        img->rgb_mat[i] = (rgb *)malloc(sizeof(rgb) * img->width);
    }
    img->gray_mat = NULL;

}

void readGrayscale(image *img, unsigned char *buffer) {
    int i, j;
    for(i = 0; i < img->height; ++i) {
        for (j = 0; j < img->width; ++j) {
            img->gray_mat[i][j] = *(buffer++);
        }
    }
}

void readRGB(image *img, unsigned char *buffer) {
    int i, j;
    for(i = 0; i < img->height; ++i) {
        for (j = 0; j < img->width; ++j) {
            img->rgb_mat[i][j].r = *(buffer++);
            img->rgb_mat[i][j].g = *(buffer++);
            img->rgb_mat[i][j].b = *(buffer++);
        }
    }
}


void writeRGB(image *img, FILE *fp){
    int i, j;
    for (i = 0; i < img->height; ++i) {
        for (j = 0; j < img->width; ++j) {
            fputc(img->rgb_mat[i][j].r, fp);
            fputc(img->rgb_mat[i][j].g, fp);
            fputc(img->rgb_mat[i][j].b, fp);
        }
    }
}

void writeGrayscale(image *img, FILE *fp){
    int i, j;
    for (i = 0; i < img->height; ++i) {
        for (j = 0; j < img->width; ++j) {
            fputc(img->gray_mat[i][j], fp);
        }
    }
}

void freeMemory(image *img) {
    int i;
    if (img->type == '5') {
        for (i = 0; i < img->height; ++i)
        {
            free(img->gray_mat[i]);
        }
        free(img->gray_mat);
    } else {
        for (i = 0; i < img->height; ++i)
        {
            free(img->rgb_mat[i]);
        }
        free(img->rgb_mat);
    }
}


void readInput(const char * fileName, image *img) {
    FILE *fp;
    unsigned long img_length, header_length;
    unsigned char *buffer;

    fp = fopen(fileName, "rb");
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    getc(fp); // skipping P
    fscanf(fp, "%c", &(img)->type);
    getc(fp); // skipping \n
    fscanf(fp, "%d", &(img)->width);
    fscanf(fp, "%d", &(img)->height);
    getc(fp); // skipping \n
    fscanf(fp, "%d", &(img)->max_val);
    getc(fp); // skipping \n
    header_length = ftell(fp);

    fseek(fp, 0, SEEK_END);
    img_length = ftell(fp);
    img_length -= header_length;
    rewind(fp);
    fseek(fp, header_length, SEEK_CUR);

    buffer = (unsigned char *)malloc(img_length);
    fread(buffer, sizeof(unsigned char), img_length, fp);



    if (img->type == '5') {
        allocGrayscale(img);
        readGrayscale(img, buffer);
    } else {
        allocRGB(img);
        readRGB(img, buffer);
    }

    fclose(fp);
    free(buffer);
}

void writeData(const char * fileName, image *img) {
    FILE *fpw;
    fpw = fopen(fileName, "w+");
    if (fpw == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fpw, "P%c\n%d %d\n%d\n", img->type, img->width, img->height, img->max_val);
    if (img->type == '5') {
        writeGrayscale(img, fpw);
    } else {
        writeRGB(img, fpw);
    }
    fclose(fpw);
    freeMemory(global_in);
    freeMemory(global_out);
}

void* resizeRGB(void* var) {
    int i, j, w, h; 
    int out_i, out_j;
    int r, g, b;
	int thread_id = *(int*)var;
	int start= (int)ceil(global_in->width / num_threads * thread_id);
	int end= min((int)ceil(global_in->width / num_threads * (thread_id + 1)), global_in->width);

    if (thread_id == num_threads - 1) {
        end = global_in->width;
    }

    int start_out = start/ resize_factor;

    out_i = 0;
    if (resize_factor == 3) {
        for (h = 0; h < global_in->height; h += 3)
        {
            out_j = start_out;

            for (w = start; w < end; w += 3) {
                r = 0;
                g = 0;
                b = 0;

                r += global_in->rgb_mat[h][w].r;
                r += 2 * global_in->rgb_mat[h][w + 1].r;
                r += global_in->rgb_mat[h][w + 2].r;
                r += 2 * global_in->rgb_mat[h + 1][w].r;
                r += 4 * global_in->rgb_mat[h + 1][w + 1].r;
                r += 2 * global_in->rgb_mat[h + 1][w + 2].r;
                r += global_in->rgb_mat[h + 2][w].r;
                r += 2 * global_in->rgb_mat[h + 2][w + 1].r;
                r += global_in->rgb_mat[h + 2][w + 2].r;

                g += global_in->rgb_mat[h][w].g;
                g += 2 * global_in->rgb_mat[h][w + 1].g;
                g += global_in->rgb_mat[h][w + 2].g;
                g += 2 * global_in->rgb_mat[h + 1][w].g;
                g += 4 * global_in->rgb_mat[h + 1][w + 1].g;
                g += 2 * global_in->rgb_mat[h + 1][w + 2].g;
                g += global_in->rgb_mat[h + 2][w].g;
                g += 2 * global_in->rgb_mat[h + 2][w + 1].g;
                g += global_in->rgb_mat[h + 2][w + 2].g;

                b += global_in->rgb_mat[h][w].b;
                b += 2 * global_in->rgb_mat[h][w + 1].b;
                b += global_in->rgb_mat[h][w + 2].b;
                b += 2 * global_in->rgb_mat[h + 1][w].b;
                b += 4 * global_in->rgb_mat[h + 1][w + 1].b;
                b += 2 * global_in->rgb_mat[h + 1][w + 2].b;
                b += global_in->rgb_mat[h + 2][w].b;
                b += 2 * global_in->rgb_mat[h + 2][w + 1].b;
                b += global_in->rgb_mat[h + 2][w + 2].b;

                global_out->rgb_mat[out_i][out_j].r = (unsigned char)floor(r / 16);
                global_out->rgb_mat[out_i][out_j].g = (unsigned char)floor(g / 16);
                global_out->rgb_mat[out_i][out_j].b = (unsigned char)floor(b / 16);

                ++out_j;
            }

            ++out_i;
        }

    } else {

        for (h = 0; h < global_in->height; h += resize_factor)
        {
            out_j = start_out;
            for (w = start; w < end; w += resize_factor)
            {
                r = 0;
                g = 0;
                b = 0;
                for (i = h; i < h + resize_factor; ++i)
                {
                    for (j = w; j < w + resize_factor; ++j)
                    {
                        r += global_in->rgb_mat[i][j].r ;
                        g += global_in->rgb_mat[i][j].g;
                        b += global_in->rgb_mat[i][j].b;
                    }
                }
                global_out->rgb_mat[out_i][out_j].r = (unsigned char)floor(r / (resize_factor * resize_factor));
                global_out->rgb_mat[out_i][out_j].g = (unsigned char)floor(g / (resize_factor * resize_factor));
                global_out->rgb_mat[out_i][out_j].b = (unsigned char)floor(b / (resize_factor * resize_factor));

                ++out_j;
            }
            ++out_i;
        }
    }
    return NULL;
 }


void* resizeGrayscale(void* var) {
    int i, j, w, h, sum = 0;
    int out_i, out_j;

	int thread_id = *(int*)var;
	int start = ceil((global_in->width / num_threads) * thread_id);
    int end = min(ceil(global_in->width / num_threads * (thread_id + 1)), (global_out->width * resize_factor));
    int start_out = start / resize_factor;

    if (thread_id == num_threads - 1) {
        end = global_in->width;
    }

    out_i = 0;

    if (resize_factor == 3) {
        for (h = 0; h < global_in->height; h += 3)
        {
            out_j = start_out;

            for (w = start; w < end; w += 3) {
                // Computing multiplication with gaussian kernel

                sum += global_in->gray_mat[h][w];
                sum += 2 * global_in->gray_mat[h][w + 1];
                sum += global_in->gray_mat[h][w + 2];
                sum += 2 * global_in->gray_mat[h + 1][w];
                sum += 4 * global_in->gray_mat[h + 1][w + 1];
                sum += 2 * global_in->gray_mat[h + 1][w + 2];
                sum += global_in->gray_mat[h + 2][w];
                sum += 2 * global_in->gray_mat[h + 2][w + 1];
                sum += global_in->gray_mat[h + 2][w + 2];

                global_out->gray_mat[out_i][out_j] = (unsigned char)floor((sum / 16));

                sum = 0;
                ++out_j;
            }

            ++out_i;
        }
    } else {

        for (h = 0; h < global_in->height; h += resize_factor)
        {
            out_j = start_out;

            for (w = start; w < end; w += resize_factor)
            {

                for (i = h; i < h + resize_factor; ++i)
                {
                    for (j = w; j < w + resize_factor; ++j)
                    {
                        sum += (global_in->gray_mat[i][j]);
                    }
                }
                global_out->gray_mat[out_i][out_j] = (unsigned char)floor(sum / (resize_factor * resize_factor));
                sum = 0;
                ++out_j;
            }
            ++out_i;
        }
    }

    return NULL;
}
void resize(image *in, image * out) { 
    int i;


    out->width = in->width / resize_factor;
    out->height = in->height / resize_factor;

    in->width = floor(in->width / resize_factor) * resize_factor;
    in->height = floor(in->height / resize_factor) * resize_factor;

    out->max_val = in->max_val;
    out->type = in->type;

	pthread_t tid[num_threads];
	int thread_id[num_threads];

	for(i = 0;i < num_threads; i++)
		thread_id[i] = i;



    if (out->type == '5') { // Type pgm
        allocGrayscale(out);
        global_in = in;
        global_out = out;
        for (i = 0; i < num_threads; i++)
        {
            pthread_create(&(tid[i]), NULL, resizeGrayscale, &(thread_id[i]));
        }
    } else {
        allocRGB(out);
        global_in = in;
        global_out = out;
        for (i = 0; i < num_threads; i++)
        {
            pthread_create(&(tid[i]), NULL, resizeRGB, &(thread_id[i]));
        }
    }

	for(i = 0; i < num_threads; i++) {
		pthread_join(tid[i], NULL);
	}
    in = global_in;
    out = global_out;
}