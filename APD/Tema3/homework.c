#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb;

rgb **apply_filter_rgb(int height, int width, int rank, int nProcesses, rgb **image, char *filter_type)
{
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

    float(*filter)[3];
    int low = rank * height / nProcesses;
    int high = (rank + 1) * height / nProcesses - 1;
    int diff = high - low + 3;
    if (high == height - 1 || low == 0)
    {
        diff--;
    }
    if (nProcesses == 1) {
        diff--;
    }
    rgb **copy;
    copy = (rgb **)malloc(diff * sizeof(rgb *));
    for (int i = 0; i < diff; ++i) {
        copy[i] = (rgb *)malloc(width * sizeof(rgb));
    }
    for (int i = 0; i < diff; ++i)
    {
        memcpy(copy[i], image[i], width * sizeof(rgb));
    }

    if (strncmp(filter_type, "blur", 4) == 0)
    {
        filter = BLUR;
    }
    else if (strncmp(filter_type, "smooth", 6) == 0)
    {
        filter = SMOOTH;
    }
    else if (strncmp(filter_type, "mean", 4) == 0)
    {
        filter = MEAN;
    }
    else if (strncmp(filter_type, "sharpen", 7) == 0)
    {
        filter = SHARPEN;
    }
    else if (strncmp(filter_type, "emboss", 6) == 0)
    {
        filter = EMBOSS;
    }
    else
    {
        filter = IDENTITY;
    }

    for (int i = 1; i < diff - 1; ++i)
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
    for (int i = 0; i < diff; ++i)
    {
        memcpy(image[i], copy[i], width * sizeof(rgb));
    }
    for (int i = 0; i < diff; ++i)
    {
        free(copy[i]);
    }
    free(copy);
    return image;
}

unsigned char **apply_filter_gr(int height, int width, int rank, int nProcesses, unsigned char **image, char *filter_type)
{
    float(*filter)[3];
    int low = rank * height / nProcesses;
    int high = (rank + 1) * height / nProcesses - 1;
    int diff = high - low + 3;
     
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


    if (high == height - 1 || low == 0)
    {
        diff--;
    }
    if (nProcesses == 1) {
        diff--;
    }
    unsigned char **copy;
    copy = (unsigned char **)malloc(diff * sizeof(unsigned char*));
    for (int i = 0; i < diff; ++i) {
        copy[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
    }
    for (int i = 0; i < diff; ++i)
    {
        memcpy(copy[i], image[i], width * sizeof(unsigned char));
    }

    if (strncmp(filter_type, "blur", 4) == 0)
    {
        filter = BLUR;
    }
    else if (strncmp(filter_type, "smooth", 6) == 0)
    {
        filter = SMOOTH;
    }
    else if (strncmp(filter_type, "mean", 4) == 0)
    {
        filter = MEAN;
    }
    else if (strncmp(filter_type, "sharpen", 7) == 0)
    {
        filter = SHARPEN;
    }
    else if (strncmp(filter_type, "emboss", 6) == 0)
    {
        filter = EMBOSS;
    }
    else
    {
        filter = IDENTITY;
    }

    for (int i = 1; i < diff - 1; ++i)
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
    for (int i = 0; i < diff; ++i)
    {
        memcpy(image[i], copy[i], width * sizeof(unsigned char));
    }

    for (int i = 0; i < diff; ++i)
    {
        free(copy[i]);
    }
    free(copy);

    return image;
}

int main(int argc, char *argv[])
{

    int height, width, max_value;
    char type;
    int values[4];
    int low, high;

    int rank, nProcesses;
    MPI_Status status;
    MPI_Datatype mpi_rgb;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

    MPI_Type_contiguous(3, MPI_UNSIGNED_CHAR, &mpi_rgb);
    MPI_Type_commit(&mpi_rgb);

    if (rank == 0)
    {

        FILE *fp, *fpw;
        fp = fopen(argv[1], "rb");
        if (fp == NULL)
        {
            exit(EXIT_FAILURE);
        }

        fscanf(fp, "P%c\n%d %d\n%d\n", &type, &width, &height, &max_value);
        values[0] = height;
        values[1] = width;
        values[2] = (type == '5') ? 5 : 6;
        values[3] = max_value;
        for (int i = 1; i < nProcesses; ++i)
        {
            MPI_Send(values, 4, MPI_INT, i, 2, MPI_COMM_WORLD);
        }

        // INTERVAL FOR RANK )
        low = 0;
        high = (height / nProcesses) - 1;

        // IF IMAGE IS GRAYSCALE
        if (type == '5')
        {
            //INITIALIZING MATRIX
            unsigned char **gray_mat = (unsigned char **)malloc(height * sizeof(unsigned char *));
            for (int i = 0; i < height; ++i)
            {
                gray_mat[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
            }
            for (int i = 0; i < height; ++i)
            {
                fread(gray_mat[i], sizeof(unsigned char), width, fp);
            }

            for (int i = 1; i < nProcesses; ++i)
            {
                int low_i = i * height / nProcesses;
                int high_i = ((i + 1) * height / nProcesses) - 1;
                int total = (high_i - low_i + 3);
                if (i == nProcesses - 1)
                {
                    total--;
                }
                for (int j = low_i - 1; j < total + low_i - 1; ++j)
                {
                    MPI_Send(gray_mat[j], width, MPI_UNSIGNED_CHAR, i, 2, MPI_COMM_WORLD);
                }
            }

            int interval_0 = high - low + 2;
            if (nProcesses == 1) interval_0--;
            unsigned char **cut_matrix;
            cut_matrix = (unsigned char **)malloc(interval_0 * sizeof(unsigned char *));
            for (int i = 0; i < interval_0; ++i)
            {
                cut_matrix[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
                memcpy(cut_matrix[i], gray_mat[i], width * sizeof(unsigned char));
            }

            for (int i = 3; i < argc; ++i)
            {
                cut_matrix = apply_filter_gr(height, width, rank, nProcesses, cut_matrix, argv[i]);
                if (nProcesses > 1){
                    MPI_Sendrecv(cut_matrix[interval_0 - 2], width, MPI_UNSIGNED_CHAR,
                                 1, 3,
                                 cut_matrix[interval_0 - 1], width, MPI_UNSIGNED_CHAR,
                                 1, 3, MPI_COMM_WORLD, &status);
                }
            }


            // PUTTING IMAGE TOGHETHER FROM OTHER PROCESSES
            for (int i = 1; i < nProcesses; ++i)
            {
                int low_i = i * height / nProcesses;
                int high_i = ((i + 1) * height / nProcesses) - 1;
                int total = high_i - low_i + 1;
                for (int j = low_i; j <= low_i + total - 1; j++)
                {
                    MPI_Recv(gray_mat[j], width, MPI_UNSIGNED_CHAR, i, 2,
                             MPI_COMM_WORLD, &status);
                }
            }

            for (int i = 1; i < interval_0 - 1; ++i)
            {
                memcpy(gray_mat[i], cut_matrix[i], width * sizeof(unsigned char));
                free(cut_matrix[i]);
            }
            free(cut_matrix[0]);
            free(cut_matrix[interval_0 - 1]);
            free(cut_matrix);

            // WRITING TO OUTPUT FILE
            fpw = fopen(argv[2], "w+");
            if (fpw == NULL)
            {
                return -1;
            }
            fprintf(fpw, "P%c\n%d %d\n%d\n", type, width, height, max_value);
            for (int i = 0; i < height; ++i)
            {
                fwrite(gray_mat[i], sizeof(unsigned char), width, fpw);
            }
            fclose(fpw);

            // FREEING MATRIX
            for (int j = 0; j < height; ++j)
            {
                free(gray_mat[j]);
            }
            free(gray_mat);
        }
        else
        { // RGB
            //INITIALIZING MATRIX
            rgb **rgb_mat = (rgb **)malloc(height * sizeof(rgb *));
            for (int i = 0; i < height; ++i)
            {
                rgb_mat[i] = (rgb *)malloc(width * sizeof(rgb));
            }
            for (int i = 0; i < height; ++i)
            {
                fread(rgb_mat[i], sizeof(rgb), width, fp);
            }

            for (int i = 1; i < nProcesses; ++i)
            {
                int low_i = i * height / nProcesses;
                int high_i = ((i + 1) * height / nProcesses) - 1;
                int total = (high_i - low_i + 3);
                if (i == nProcesses - 1)
                {
                    total--;
                }
                for (int j = low_i - 1; j < total + low_i - 1; ++j)
                {
                    MPI_Send(rgb_mat[j], width, mpi_rgb, i, 2, MPI_COMM_WORLD);
                }
            }

            int interval_0 = high - low + 2;
            if (nProcesses == 1) interval_0--;
            rgb **cut_matrix;
            cut_matrix = (rgb **)malloc(interval_0 * sizeof(rgb *));
            for (int i = 0; i < interval_0; ++i)
            {
                cut_matrix[i] = (rgb *)malloc(width * sizeof(rgb));
                memcpy(cut_matrix[i], rgb_mat[i], width * sizeof(rgb));
            }

            for (int i = 3; i < argc; ++i)
            {
                cut_matrix = apply_filter_rgb(height, width, rank, nProcesses, cut_matrix, argv[i]);

                if (nProcesses > 1) {
                    MPI_Sendrecv(cut_matrix[interval_0 - 2], width, mpi_rgb,
                                 1, 3,
                                 cut_matrix[interval_0 - 1], width, mpi_rgb,
                                 1, 3, MPI_COMM_WORLD, &status);
                }
            }
            // PUTTING IMAGE TOGHETHER FROM OTHER PROCESSES
            for (int i = 1; i < nProcesses; ++i)
            {
                int low_i = i * height / nProcesses;
                int high_i = ((i + 1) * height / nProcesses) - 1;
                int total = high_i - low_i + 1;
                for (int j = low_i; j <= low_i + total - 1; j++)
                {
                    MPI_Recv(rgb_mat[j], width, mpi_rgb, i, 2,
                             MPI_COMM_WORLD, &status);
                }
            }

            for (int i = 1; i < interval_0 - 1; ++i)
            {
                memcpy(rgb_mat[i], cut_matrix[i], width * sizeof(rgb));
                free(cut_matrix[i]);
            }
            free(cut_matrix[0]);
            free(cut_matrix[interval_0 - 1]);
            free(cut_matrix);

            // WRITING TO OUTPUT FILE
            fpw = fopen(argv[2], "w+");
            if (fpw == NULL)
            {
                return -1;
            }
            fprintf(fpw, "P%c\n%d %d\n%d\n", type, width, height, max_value);
            for (int i = 0; i < height; ++i)
            {
                fwrite(rgb_mat[i], sizeof(rgb), width, fpw);
            }
            fclose(fpw);

            // FREEING MATRIX
            for (int j = 0; j < height; ++j)
            {
                free(rgb_mat[j]);
            }
            free(rgb_mat);
        }
        fclose(fp);
    }
    else
    { // THE REST OF PROCESSES
        MPI_Recv(values, 4, MPI_INT, 0, 2, MPI_COMM_WORLD, &status);

        low = rank * values[0] / nProcesses;
        high = ((rank + 1) * values[0] / nProcesses) - 1;
        int diff = high - low + 3;
        if (rank == nProcesses - 1)
            diff--;

        if (values[2] == 5)
        { // GRAYSCALE
            unsigned char **rank_image;
            rank_image = (unsigned char **)malloc(diff * sizeof(unsigned char *));
            for (int i = 0; i < diff; ++i)
            {
                rank_image[i] = (unsigned char *)malloc(values[1] * sizeof(unsigned char));
            }

            for (int i = 0; i < diff; ++i)
            {
                MPI_Recv(rank_image[i], values[1], MPI_UNSIGNED_CHAR, 0, 2, MPI_COMM_WORLD, &status);
            }

            for (int i = 3; i < argc; ++i)
            {
                rank_image = apply_filter_gr(values[0], values[1], rank, nProcesses, rank_image, argv[i]);
                // SYNCHRONIZE DOWN
                MPI_Sendrecv(rank_image[1], values[1], MPI_UNSIGNED_CHAR,
                             rank - 1, 3,
                             rank_image[0], values[1], MPI_UNSIGNED_CHAR,
                             rank - 1, 3, MPI_COMM_WORLD, &status);

                // SYNCHRONIZE UP
                if (rank != nProcesses - 1)
                {
                    MPI_Sendrecv(rank_image[diff - 2], values[1], MPI_UNSIGNED_CHAR,
                                 rank + 1, 3,
                                 rank_image[diff - 1], values[1], MPI_UNSIGNED_CHAR,
                                 rank + 1, 3, MPI_COMM_WORLD, &status);
                }
            }

            for (int i = 1; i <= high - low + 1; ++i)
            {
                MPI_Send(rank_image[i], values[1], MPI_UNSIGNED_CHAR, 0, 2,
                         MPI_COMM_WORLD);
            }
        }
        else
        { // RGB
            rgb **rank_image;
            rank_image = (rgb **)malloc(diff * sizeof(rgb *));
            for (int i = 0; i < diff; ++i)
            {
                rank_image[i] = (rgb *)malloc(values[1] * sizeof(rgb));
            }

            for (int i = 0; i < diff; ++i)
            {
                MPI_Recv(rank_image[i], values[1], mpi_rgb, 0, 2, MPI_COMM_WORLD, &status);
            }

            for (int i = 3; i < argc; ++i)
            {
                rank_image = apply_filter_rgb(values[0], values[1], rank, nProcesses, rank_image, argv[i]);
                // SYNCHRONIZE DOWN
                MPI_Sendrecv(rank_image[1], values[1], mpi_rgb,
                             rank - 1, 3,
                             rank_image[0], values[1], mpi_rgb,
                             rank - 1, 3, MPI_COMM_WORLD, &status);

                // SYNCHRONIZE UP
                if (rank != nProcesses - 1)
                {
                    MPI_Sendrecv(rank_image[diff - 2], values[1], mpi_rgb,
                                 rank + 1, 3,
                                 rank_image[diff - 1], values[1], mpi_rgb,
                                 rank + 1, 3, MPI_COMM_WORLD, &status);
                }
            }

            for (int i = 1; i <= high - low + 1; ++i)
            {
                MPI_Send(rank_image[i], values[1], mpi_rgb, 0, 2,
                         MPI_COMM_WORLD);
            }
        }
    }
    MPI_Finalize();
    return 0;
}
