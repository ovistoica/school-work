#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

float BLUR[3][3] = {
    {0.0625f, 0.125f, 0.0625f},
    {0.125f, 0.25f, 0.125f},
    {0.0625f, 0.125f, 0.0625f}};

float SMOOTH[3][3] = {
    {0.111111111f, 0.111111111f,0.111111111f},
    {0.111111111f, 0.111111111f,0.111111111f},
    {0.111111111f, 0.111111111f,0.111111111f},
};

float IDENTITY[3][3] = {
    {0.0f, 0.0f,0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
};

float MEAN[3][3] = {
    {-1, -1, -1},
    {-1, 9, -1},
    {-1, -1, -1}};

float SHARPEN[3][3] = {
    {0.0f, (-2.0f / 3.0f), 0.0f},
    {(-2.0f / 3.0f), (11.0f / 3), (-2.0f / 3.0f)},
    {0.0f, (-2.0f / 3.0f), 0.0f}
};

float EMBOSS[3][3] = {
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, -1.0f, 0.0f}
};

typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb;

typedef struct
{
    int height;
    int width;
    char type; // 5 IS PGM
    rgb **rgb_mat;
    unsigned char **gray_mat;
    int max_val;
} image;

int min(int a, int b)
{
    return (a < b) ? a : b;
}

unsigned char *readInput(const char *fileName, int *height, int *width, char *type, int *max_val)
{
    FILE *fp;
    unsigned long img_length, header_length;
    unsigned char *buffer = NULL;

    fp = fopen(fileName, "rb");
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    getc(fp); // SKIPPING P
    fscanf(fp, "%c", type);
    getc(fp); // SKIPPING \n
    fscanf(fp, "%d", width);
    fscanf(fp, "%d", height);
    getc(fp); // SKIPPING \n
    fscanf(fp, "%d", max_val);
    getc(fp); // SKIPPING \n

    buffer = (unsigned char *)malloc((*height) * *(width)  * sizeof(unsigned char));
    fread(buffer, sizeof(unsigned char), *(height) * *(width), fp);

    fclose(fp);
    return buffer;
}

// USE FLOAT AS TYPE FOR FILTER_MATRICES

unsigned char **apply_filter_grayscale(int height, int width, unsigned char **gray_mat, char *filter)
{
    printf("Applying filter %s\n", filter);
    unsigned char **copy;
    size_t matrix_length = (size_t)height * width * sizeof(unsigned char);
    float (*filter_mat)[3];

    // ASSIGN FILTER MATRIX
    if (strncmp(filter, "blur", 4) == 0) {
        filter_mat = BLUR;
    }else if (strncmp(filter, "smooth", 6) == 0) {
        filter_mat = SMOOTH;

    } else if (strncmp(filter, "mean", 4) == 0) {
        filter_mat = MEAN;
    } else if (strncmp(filter, "sharpen", 7) == 0) {
        filter_mat = SHARPEN;
    } else if (strncmp(filter, "emboss", 6) == 0) {
        filter_mat = EMBOSS;
    } else {
        filter_mat = IDENTITY;
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%f ", filter_mat[i][j]);
        }
        printf("\n");
    }

    // MAKE COPY OF IMAGE MATRIX
    copy = (unsigned char **)malloc(height * sizeof(unsigned char *));
    for (int i = 0; i < height; ++i)
    {
        copy[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
    }
    memcpy(copy, gray_mat, matrix_length);
    // APPLY FILTER
    for (int i = 1; i < height - 1; ++i)
    {
        for (int j = 1; j < width - 1; ++j)
        {
            float result = 0.0f;
            result += (gray_mat[i - 1][j - 1] * filter_mat[0][0]);
            result += (gray_mat[i - 1][j] * filter_mat[0][1]);
            result += (gray_mat[i - 1][j + 1] * filter_mat[0][2]);
            result += (gray_mat[i][j - 1] * filter_mat[1][0]);
            result += (gray_mat[i][j] * filter_mat[1][1]);
            result += (gray_mat[i][j + 1] * filter_mat[1][2]);
            result += (gray_mat[i + 1][j - 1] * filter_mat[2][0]);
            result += (gray_mat[i + 1][j] * filter_mat[2][1]);
            result += (gray_mat[i + 1][j + 1] * filter_mat[2][2]);
            if (result < 0.0f) {
                copy[i][j] = 0.0f;
            }else if (result > 255) {
                copy[i][j] = 255;
            } else {
                copy[i][j] = result;
            }
        }
    }
    return copy;
}

int main(int argc, char *argv[])
{
    int height, width, max_val;
    char type; // 5 IS PGM
    unsigned char *buffer = NULL, **gray_mat = NULL;
    unsigned char *to_free;
    rgb **rgb_mat = NULL;

    buffer = readInput(argv[1], &height, &width, &type, &max_val); // BUFFER NEEDS TO BE FREED

    // ALLOC BUFFER TO AN IMAGE MATRIX
    to_free = buffer;
    if (type == '5')
    {
        // GRAYSCALE
        gray_mat = (unsigned char **)malloc(sizeof(unsigned char *) * height);
        for (int i = 0; i < height; ++i)
        {
            gray_mat[i] = (unsigned char *)malloc(width);
        }
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                gray_mat[i][j] = *(buffer++);
            }
        }
    }
    else
    {
        //RGB
        rgb_mat = (rgb **)malloc(sizeof(rgb *) * height);
        for (int i = 0; i < height; ++i)
        {
            rgb_mat[i] = (rgb *)malloc(sizeof(rgb) * width);
        }
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                rgb_mat[i][j].r = *(buffer++);
                rgb_mat[i][j].g = *(buffer++);
                rgb_mat[i][j].b = *(buffer++);
            }
        }
    }

    if (type == '5') { //GRAYSCALE
        for (int i = 3; i < argc; i++)
        {
            unsigned char **old_mat = gray_mat;
            gray_mat = apply_filter_grayscale(height, width, gray_mat, argv[i]);
            for (int j = 0; j < height; j++) {
                free(old_mat[j]);
            }
            free(old_mat);
        }
    } else { // RGB
        printf("Image is RGB\n");
    }

    // WRITING IMAGE TO FILE
    FILE *fpw;
    fpw = fopen(argv[2], "w+");
    if (fpw == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fpw, "P%c\n%d %d\n%d\n", type, width, height, max_val);
    if (type == '5')
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                fputc(gray_mat[i][j], fpw);
            }
        }
    }
    else
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                fputc(rgb_mat[i][j].r, fpw);
                fputc(rgb_mat[i][j].g, fpw);
                fputc(rgb_mat[i][j].b, fpw);
            }
        }
    }
    fclose(fpw);
    // FREE RGB OR GRAYSCALE MATRIX
    if (type == '5')
    {
        for (int i = 0; i < height; ++i)
        {
            free(gray_mat[i]);
        }
        free(gray_mat);
    }
    else
    {
        for (int i = 0; i < height; ++i)
        {
            free(rgb_mat[i]);
        }
        free(rgb_mat);
    }
    free(to_free);
    return 0;
}
