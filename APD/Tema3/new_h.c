#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb;

float BLUR[3][3] = {
    {(1.0f / 16), (2.0f / 16), (1.0f / 16)},
    {(2.0f / 16), (4.0f / 16), (2.0f / 16)},
    {(1.0f / 16), (2.0f / 16), (1.0f / 16)}};

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

rgb ** apply_filter_rgb(int height, int width, int max_value, 
            rgb **image, char *filter_type) {

    float BLUR[3][3] = {
        {(1.0f / 16), (2.0f / 16), (1.0f / 16)},
        {(2.0f / 16), (4.0f / 16), (2.0f / 16)},
        {(1.0f / 16), (2.0f / 16), (1.0f / 16)}};

    float SMOOTH[3][3] = {
        {0.111111111f, 0.111111111f, 0.111111111f},
        {0.111111111f, 0.111111111f, 0.111111111f},
        {0.111111111f, 0.111111111f, 0.111111111f},
    };

    float IDENTITY[3][3] = {
        {0.0f, 0.0f, 0.0f},
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
        {0.0f, (-2.0f / 3.0f), 0.0f}};

    float EMBOSS[3][3] = {
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, -1.0f, 0.0f}};
    float (*filter)[3];

    rgb copy[height][width];
    for (int i = 0; i < height; ++i) {
        memcpy(copy[i], image[i], width * sizeof(rgb));
    }

    if (strncmp(filter_type, "blur", 4) == 0) {
        filter= BLUR;
    }else if (strncmp(filter_type, "smooth", 6) == 0) {
        filter= SMOOTH;
    } else if (strncmp(filter_type, "mean", 4) == 0) {
        filter= MEAN;
    } else if (strncmp(filter_type, "sharpen", 7) == 0) {
        filter= SHARPEN;
    } else if (strncmp(filter_type, "emboss", 6) == 0) {
        filter= EMBOSS;
    } else {
        filter= IDENTITY;
    }
    printf("Applying filter\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%.5f ", filter[i][j]);
        }
        printf("\n");
    }

    for (int i = 1; i < height - 1; ++i)
    {
        for (int j = 1; j < width - 1; ++j)
        {
            float r = 0.0f;
            float g = 0.0f;
            float b = 0.0f;
            r += image[i - 1][j - 1].r * filter[0][0];
            r += image[i - 1][j].r * filter[0][1];
            r += image[i - 1][j + 1].r * filter[0][2];
            r += image[i][j - 1].r * filter[1][0];
            r += image[i][j].r * filter[1][1];
            r += image[i][j + 1].r * filter[1][2];
            r += image[i + 1][j - 1].r * filter[2][0];
            r += image[i + 1][j].r * filter[2][1];
            r += image[i + 1][j + 1].r * filter[2][2];

            g += image[i - 1][j - 1].g * filter[0][0];
            g += image[i - 1][j].g * filter[0][1];
            g += image[i - 1][j + 1].g * filter[0][2];
            g += image[i][j - 1].g * filter[1][0];
            g += image[i][j].g * filter[1][1];
            g += image[i][j + 1].g * filter[1][2];
            g += image[i + 1][j - 1].g * filter[2][0];
            g += image[i + 1][j].g * filter[2][1];
            g += image[i + 1][j + 1].g * filter[2][2];

            b += image[i - 1][j - 1].b * filter[0][0];
            b += image[i - 1][j].b * filter[0][1];
            b += image[i - 1][j + 1].b * filter[0][2];
            b += image[i][j - 1].b * filter[1][0];
            b += image[i][j].b * filter[1][1];
            b += image[i][j + 1].b * filter[1][2];
            b += image[i + 1][j - 1].b * filter[2][0];
            b += image[i + 1][j].b * filter[2][1];
            b += image[i + 1][j + 1].b * filter[2][2];
            copy[i][j].r = r;
            copy[i][j].g = g;
            copy[i][j].b = b;
        }
    }

    for (int i = 0; i < height; ++i) {
        memcpy(image[i], copy[i], width * sizeof(rgb));
    }
    return image;
}

unsigned char ** apply_filter_grayscale(int height, int width, int max_value, 
            unsigned char **image, char *filter_type) {

    float (*filter)[3];

    unsigned char copy[height][width];
    for (int i = 0; i < height; ++i) {
        memcpy(copy[i], image[i], width * sizeof(unsigned char));
    }

    if (strncmp(filter_type, "blur", 4) == 0) {
        filter= BLUR;
    }else if (strncmp(filter_type, "smooth", 6) == 0) {
        filter= SMOOTH;

    } else if (strncmp(filter_type, "mean", 4) == 0) {
        filter= MEAN;
    } else if (strncmp(filter_type, "sharpen", 7) == 0) {
        filter= SHARPEN;
    } else if (strncmp(filter_type, "emboss", 6) == 0) {
        filter= EMBOSS;
    } else {
        filter= IDENTITY;
    }
    printf("Applying filter\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%.5f ", filter[i][j]);
        }
        printf("\n");
    }

    for (int i = 1; i < height - 1; ++i)
    {
        for (int j = 1; j < width - 1; ++j)
        {
            float res = 0.0f;
            float sum = 0.0f;
            res = image[i - 1][j - 1] * filter[0][0];
            sum += res;
            res = image[i - 1][j] * filter[0][1];
            sum += res;
            res = image[i - 1][j + 1] * filter[0][2];
            sum += res;
            res = image[i][j - 1] * filter[1][0];
            sum += res;
            res = image[i][j] * filter[1][1];
            sum += res;
            res = image[i][j + 1] * filter[1][2];
            sum += res;
            res = image[i + 1][j - 1] * filter[2][0];
            sum += res;
            res = image[i + 1][j] * filter[2][1];
            sum += res;
            res = image[i + 1][j + 1] * filter[2][2];
            sum += res;
            copy[i][j] = sum;
        }
    }

    for (int i = 0; i < height; ++i) {
        memcpy(image[i], copy[i], width * sizeof(unsigned char));
    }
    return image;
}

int main(int argc, char *argv[]) {
    int height, width, max_value;
    char type;
    FILE *fp, *fpw;
    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        perror("Error while opening input file\n");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "P%c\n%d %d\n%d\n", &type, &width, &height, &max_value);

    if (type == '5') {
        //INITIALIZING MATRIX
        unsigned char **gray_mat = (unsigned char **)malloc(height * sizeof(unsigned char *));
        for (int i = 0; i < height; ++i) {
            gray_mat[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
        }
        for(int i = 0; i < height; ++i) {
            fread(gray_mat[i], sizeof(unsigned char),width, fp);
        }

        // APPLY FILTERS
        for (int i = 3; i < argc; ++i) {
            gray_mat = apply_filter_grayscale(height, width, max_value, gray_mat, argv[i]);
        }

        // WRITING TO OUTPUT FILE
        fpw = fopen(argv[2], "w+");
        if (fpw == NULL) {
            perror("Error while opening input file\n");
            exit(EXIT_FAILURE);
        }
        fprintf(fpw, "P%c\n%d %d\n%d\n", type, width, height, max_value);
        for (int i = 0; i < height; ++i) {
            fwrite(gray_mat[i], sizeof(unsigned char),width, fpw);
        }
        fclose(fpw);

        for (int j = 0; j < height; ++j) {
            free(gray_mat[j]);
        }
        free(gray_mat);

    } else { // RGB
        rgb **rgb_mat = (rgb **)malloc(height * sizeof(rgb *));
        for (int i = 0; i < height; ++i) {
            rgb_mat[i] = (rgb *)malloc(width * sizeof(rgb));
        }

        for(int i = 0; i < height; ++i) {
            fread(rgb_mat[i], sizeof(rgb),width, fp);
        }

        // APPLY FILTERS
        for (int i = 3; i < argc; ++i) {
            rgb_mat = apply_filter_rgb(height, width, max_value, rgb_mat, argv[i]);
        }

        // WRITING TO OUTPUT FILE
        fpw = fopen(argv[2], "w+");
        if (fpw == NULL) {
            perror("Error while opening input file\n");
            exit(EXIT_FAILURE);
        }
        fprintf(fpw, "P%c\n%d %d\n%d\n", type, width, height, max_value);
        for (int i = 0; i < height; ++i) {
            fwrite(rgb_mat[i], sizeof(rgb),width, fpw);
        }
        fclose(fpw);

        // FREE MEMORY
        for (int j = 0; j < height; ++j) {
            free(rgb_mat[j]);
        }
        free(rgb_mat);
    }
    fclose(fp);
    return 0;
}