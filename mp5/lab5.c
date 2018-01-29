/* lab5.c
 * Wenkang Wei
 * wenkanw
 * ECE 2220, Fall 2017
 *
 * Purpose:
 *        a program to take commands and check whehter commands are valid
 *        and then parse the bmp file declared in command to allocate a dynamic
 *        space for the image. This program will also perform different image processing
 *        operations,truncation, center, magnitude, scale to bmp image based on the input
 *        command. Eventually, it store the new image with given name
 * Assumptions:
 *       The file must be 24-bit color, without compression, and without
 *       a color map.
 *
 *       Some bmp files do not set the ImageSize field.  This code
 *       prints a warning but does not consider this an error since the
 *       size of the image can be calculated from other values.
 *
 *       Input command format should be:  lab5 command input_image output_image
 *
 * Command line argument
 *       name of bit mapped image file (bmp file) to read
 *       command string should be trunc or center or mag or scale
 * Bugs:
 *      unknown
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* WARNING: the header is 14 bytes, however on most systems
 * you will find that sizeof(struct Header) is 16 due to alignment
 * Thus trying to read the header with one fread may fail.  So,
 * read each member separately
 */
struct Header {
    unsigned short int Type;                 /* Magic identifier            */
    unsigned int Size;                       /* File size in bytes          */
    unsigned short int Reserved1, Reserved2;
    unsigned int Offset;                     /* Offset to image data, bytes */
};

struct InfoHeader {
    unsigned int Size;               /* header size in bytes      */
    int Width, Height;               /* Width and height of image */
    unsigned short int Planes;       /* Number of colour planes   */
    unsigned short int Bits;         /* Bits per pixel            */
    unsigned int Compression;        /* Compression type          */
    unsigned int ImageSize;          /* Image size in bytes       */
    int xResolution,yResolution;     /* Pixels per meter          */
    unsigned int Colors;             /* Number of colors         */
    unsigned int ImportantColors;    /* Important colors         */
};

const char Matrix[3][3] = {
    {  0, -1,  0 },
    { -1,  4, -1 },
    {  0, -1,  0 }
};

#define LINE 256

struct Pixel {
    unsigned char Blue, Green, Red;
};

typedef struct Pixel PIXEL;


/*---------------function prototype----------*/
int check_Bmp(char* src, int len);
void Filter(const char (*filter)[3] , int f_ROWS, int f_COLS,
            PIXEL **org_img, int ROWS, int COLS,
            int **filtered_img);

void convert_Trunc(int **filtered_img, int ROWS, int COLS, PIXEL **output_image);
void convert_Center(int **filtered_img, int ROWS, int COLS, PIXEL **output_image);
void convert_Mag(int **filtered_img, int ROWS, int COLS, PIXEL **output_image);
void convert_Scale(int **filtered_img, int ROWS, int COLS, PIXEL **output_image);


/*----------------------------------------------------------*/
int main(int argc, char const *argv[])
{
    char filein[LINE];
    char filename[LINE];
    int command=0;
    FILE *fpin;
    struct InfoHeader infoheader;
    struct Header header;
    int expected_bytes;
    int error_code = 0;
    int row, col;
    int pixel_cols, pixel_rows, pixel_count;
    int items_found;
    PIXEL **OrignalImage, **OutputImage;
    int **filtered_img;
    /*Check input command*/
    if (argc != 4) {
        printf("Invalid usage.\n");
        printf("Usage: lab5 command input.bmp output.bmp\n");
        printf("command should be one of following string: \n");
        printf("        {trunc, center, mag, scale}\n\n");
        exit(0);
    } else {
        strcpy(filein, argv[1]);
        if (strcmp(filein, "trunc")==0) {
            command=1;
        } else if (strcmp(filein, "center")==0) {
            command=2;
        } else if(  strcmp(filein,"mag")==0) {
            command=3;
        } else if ( strcmp(filein, "scale")==0) {
            command=4;
        } else {
            printf("Invalid command: %s\n",filein );
            printf("Input command must be one of following string:\n");
            printf("      {trunc center mag scale}\n\n");
            exit(0);
        }
        strcpy(filein, argv[2]);
        if (strcmp(filein, argv[3]) ==0) {
            printf("input.bmp must be different from output.bmp\n\n");
            exit(0);
        } else {

            strcpy(filename, argv[3]);
            if(check_Bmp(filein, strlen(filein)))
            {
                printf("Input is not a bmp file\n");
                printf("argv[%d]: %s\n",2, filein );
                exit(0);
            }
            if ( check_Bmp(filename, strlen(filename)))
            {
                printf("Output is not a bmp file\n");
                printf("argv[%d]: %s\n",3, filename );
                exit(0);

            }

            if ((fpin = fopen(filein, "rb")) == NULL) {
                printf("Cannot Open File. %s\n", filein);
                exit (1);
            }

            /* Read header */
            fread(&header.Type, sizeof(short int), 1, fpin);
            fread(&header.Size, sizeof(int), 1, fpin);
            fread(&header.Reserved1, sizeof(short int), 1, fpin);
            fread(&header.Reserved2, sizeof(short int), 1, fpin);
            fread(&header.Offset, sizeof(int), 1, fpin);

            printf("header.Type = %x\n", header.Type);
            printf("header.Size = %d\n", header.Size);
            printf("header.Offset = %d\n", header.Offset);

            if (header.Type != 0x4D42) {
                printf("This does not appear to be a bmp file: %s\n", filein);
                exit(1);
            }
            fread(&infoheader.Size, sizeof(int), 1, fpin);
            fread(&infoheader.Width, sizeof(int), 1, fpin);
            fread(&infoheader.Height, sizeof(int), 1, fpin);
            fread(&infoheader.Planes, sizeof(short int), 1, fpin);
            fread(&infoheader.Bits, sizeof(short int), 1, fpin);
            fread(&infoheader.Compression, sizeof(int), 1, fpin);
            fread(&infoheader.ImageSize, sizeof(int), 1, fpin);
            fread(&infoheader.xResolution, sizeof(int), 1, fpin);
            fread(&infoheader.yResolution, sizeof(int), 1, fpin);
            fread(&infoheader.Colors, sizeof(int), 1, fpin);
            fread(&infoheader.ImportantColors, sizeof(int), 1, fpin);

            printf("infoheader.Size = %d\n", infoheader.Size);
            printf("infoheader.Width = %d\n", infoheader.Width);
            printf("infoheader.Height = %d\n", infoheader.Height);
            printf("infoheader.Planes = %d\n", infoheader.Planes);
            printf("infoheader.Bits = %d\n", infoheader.Bits);
            printf("infoheader.Compression = %d\n", infoheader.Compression);
            printf("infoheader.ImageSize = %d\n", infoheader.ImageSize);
            printf("infoheader.xResolution = %d\n", infoheader.xResolution);
            printf("infoheader.yResolution = %d\n", infoheader.yResolution);
            printf("infoheader.Colors = %d\n", infoheader.Colors);
            printf("infoheader.ImportantColors = %d\n", infoheader.ImportantColors);

            if (header.Offset != 54) {
                printf("problem with offset.  Cannot handle color table\n");
                error_code +=1;
            }
            if (infoheader.Size != 40) {
                printf("Size is not 40, perhaps a bmp format not handled\n");
                error_code +=2;
            }
            if (infoheader.Planes != 1 || infoheader.Compression != 0) {
                printf("Planes or Compression format not handled\n");
                error_code +=4;
            }
            if (infoheader.Bits != 24) {
                printf("Only 24 bit color handled\n");
                error_code +=8;
            }
            expected_bytes = (infoheader.Width * infoheader.Height * infoheader.Bits)/8;
            if (expected_bytes != infoheader.ImageSize) {
                printf("Problem with image size.  Sometimes this field is not set so we will ignore the error.\n");
                error_code +=16;
            }
            if (expected_bytes + 14 + 40 != header.Size) {
                printf("Problem with size in header\n");
                error_code +=32;
            }
            if (infoheader.Colors != 0 || infoheader.ImportantColors != 0) {
                printf("Cannot handle color map\n");
                error_code +=64;
            }
            if (error_code != 0 && error_code != 16) {
                printf("exit with code %x\n", error_code);
                exit(EXIT_FAILURE);
            }

            printf("Reading image...\n");
            //obtain image rows and cols
            pixel_cols= infoheader.Width;
            pixel_rows= infoheader.Height;
            pixel_count=0;
            //allocate memory for bmp image
            OrignalImage =(PIXEL **) calloc(pixel_rows, sizeof(PIXEL* ));
            OutputImage =(PIXEL **) calloc(pixel_rows, sizeof(PIXEL*));
            filtered_img =(int **) calloc(pixel_rows, sizeof(int*));
            for(row = 0; row <pixel_rows ; ++row) {
                OrignalImage[row] = (PIXEL*) calloc(pixel_cols, sizeof(PIXEL));
                OutputImage[row] = (PIXEL*) calloc(pixel_cols, sizeof(PIXEL));
                filtered_img[row] = (int*) calloc(pixel_cols*3, sizeof(int));
            }
            for (row = 0; row < pixel_rows; ++row)
                for (col = 0; col < pixel_cols; ++col) {
                    items_found= fread(& OrignalImage[row][col] , sizeof(PIXEL),1,fpin);
                    if (items_found !=1) {
                        printf("Failed to read pixel[%d][%d]\n", row, col);
                        exit(0);
                    }
                    printf("RGB R: %u\n",OrignalImage[row][col].Red);
                    pixel_count++;
                }
            printf("Total pixel: %d \n", pixel_count);
            Filter( Matrix, 3, 3, OrignalImage, pixel_rows, pixel_cols, filtered_img);
        }
        if (command==1) {
            convert_Trunc( filtered_img, pixel_rows, pixel_cols, OutputImage);
        } else if (command == 2) {
            convert_Center( filtered_img, pixel_rows, pixel_cols, OutputImage);
        } else if (command == 3) {
            convert_Mag( filtered_img, pixel_rows, pixel_cols, OutputImage);
        } else if (command == 4)
            convert_Scale( filtered_img, pixel_rows, pixel_cols, OutputImage);

    }
    //write output image
    if((fpin =fopen(filename, "w")) !=NULL) {
        //write header
        fwrite(&header.Type, sizeof(short int), 1, fpin);
        fwrite(&header.Size, sizeof(int), 1, fpin);
        fwrite(&header.Reserved1, sizeof(short int), 1, fpin);
        fwrite(&header.Reserved2, sizeof(short int), 1, fpin);
        fwrite(&header.Offset, sizeof(int), 1, fpin);
        //write info header
        fwrite(&infoheader.Size, sizeof(int), 1, fpin);
        fwrite(&infoheader.Width, sizeof(int), 1, fpin);
        fwrite(&infoheader.Height, sizeof(int), 1, fpin);
        fwrite(&infoheader.Planes, sizeof(short int), 1, fpin);
        fwrite(&infoheader.Bits, sizeof(short int), 1, fpin);
        fwrite(&infoheader.Compression, sizeof(int), 1, fpin);
        fwrite(&infoheader.ImageSize, sizeof(int), 1, fpin);
        fwrite(&infoheader.xResolution, sizeof(int), 1, fpin);
        fwrite(&infoheader.yResolution, sizeof(int), 1, fpin);
        fwrite(&infoheader.Colors, sizeof(int), 1, fpin);
        fwrite(&infoheader.ImportantColors, sizeof(int), 1, fpin);
        //write image to output.bmp
        for (row = 0; row < pixel_rows; ++row)
            fwrite(OutputImage[row], sizeof(PIXEL)* pixel_cols,1, fpin);
        fclose(fpin);
    } else
        printf("Can't write bmp! \n");

       for(row = 0; row <pixel_rows ; ++row) {
            free(OutputImage[row]);
            free(OrignalImage[row]);
            free(filtered_img[row]);
               
            }
    free(OutputImage);
    free(OrignalImage);
    free(filtered_img);
               
    return 0;
}


/*
*  @brief check_Bmp
*           This file is to check whether the input filename and
*           output filename are correct bmp filename
*  @para  src:
*           the filename string
*  @para  len
*           length of filename string
* @return
*        1: it is not a correct bmp filename
*        0: it is a correct bmp filename 
*/
int check_Bmp(char* src, int len)
{
    char *surfix=".bmp";
    int index=len-4;
    for(; index< len; index++)
    {
        if (src[index]!=surfix[index-(len-4)])
            return 1;
    }
    return 0;
}
/*
*@brief Filter
*          This function is to perform a convolution operation on original
*           image with laplacian filter. It takes the filter matrix , original image
*           and filtered_image pointer as input
*@para  (*filter)[3]
*           The pointor array which passes the Laplacian filter value to function
*@para  f_ROW
*           amount of rows of filter
*@para f_COLS
*           amount of columns of filter
*@para **org_img
*           The pointer pointing to original image
*@para ROWS
*           The amount of rows of original image
*@para COLS
*           The amount of columns of original image
*@para **filtered_img
*           return the filtered image matrix
*
*/
void Filter( const char (*filter)[3] , int f_ROWS, int f_COLS,
             PIXEL **org_img, int ROWS, int COLS,
             int **filtered_img)
{
    int r=0, c=0;
    int r2,c2;
    int red_sum=0, green_sum=0, blue_sum=0;
    //scan each pixel in original image
    for (r=0; r< ROWS; ++r) {
        for (c = 0; c <COLS ; ++c) {
            //check boundary of image
            //if it is in boundary, return origin value
            if (r<f_ROWS/2 || r >(ROWS-1-f_ROWS/2) || c <f_COLS/2 || c >(COLS-1- f_COLS/2) ) {
                filtered_img[r][3*c]=(int)org_img[r][c].Blue;
                filtered_img[r][3*c+1]=(int) org_img[r][c].Green;
                filtered_img[r][3*c+2]=(int) org_img[r][c].Red;
            } else {
                red_sum=0;
                blue_sum=0;
                green_sum=0;
                // convolute with laplacian filter in a 3x3 window
                for (r2 = -f_ROWS/2; r2 <= f_ROWS/2; ++r2)
                    for (c2 = -f_COLS/2; c2 <= f_COLS/2; ++c2) {
                        //convolute red color
                        red_sum+=filter[ (r2+f_ROWS/2)][c2+f_COLS/2 ] * org_img[r+r2][c+c2].Red;
                        //convolute green color
                        green_sum+= filter[r2+f_ROWS/2][c2+f_COLS/2] * org_img[r+r2][c+c2].Green;
                        //convolute blue color
                        blue_sum+= filter[ r2+f_ROWS/2][(c2+f_COLS/2)] * org_img[r+r2][c+c2].Blue;
                    }
                filtered_img[r][3*c]=blue_sum;
                filtered_img[r][3*c+1]=green_sum;
                filtered_img[r][3*c+2]=red_sum;
            }
        }
    }

}


/*
* @brief convert_Trunc
*         This function is to normalize the image and convert the
*         pixel values in the image back to 8bits (0~255) using truncation
*         method that takes lowest 8 bits value of pixel value as result
* @para  **filtered_img
*        The pointer pointing to filtered image
* @para  ROWS
*        the amount of rows of filtered image
*
* @para  COLS
*       the amount of columns of filtered image
*
* @para  **output_image
*        return the normalized output image
*/
void convert_Trunc(int **filtered_img, int ROWS, int COLS, PIXEL **output_image)
{
    int r=0, c=0;
    for (r=0; r< ROWS; ++r) {
        for (c = 0; c < COLS; ++c) {
            output_image[r][c].Red= (unsigned char) (filtered_img[r][3*c+2] &0xFF);
            output_image[r][c].Green= (unsigned char) (filtered_img[r][3*c+1] &0xFF);
            output_image[r][c].Blue= (unsigned char) (filtered_img[r][3*c] &0xFF);
        }
    }
}
/*
* @brief convert_Center
*         This function is to normalize the image and convert the
*         pixel values in the image back to 8bits (0~255) using center clipped
*         method that add 128 to pixel value and clip the pixel value back to 0~255
* @para  **filtered_img
*        The pointer pointing to filtered image
* @para  ROWS
*        the amount of rows of filtered image
*
* @para  COLS
*       the amount of columns of filtered image
*
* @para  **output_image
*        return the normalized output image
*/
void convert_Center(int **filtered_img, int ROWS, int COLS, PIXEL **output_image)
{
    int r=0, c=0;
    int red=0, green=0, blue=0;
    for (r=0; r< ROWS; ++r) {
        for (c = 0; c < COLS; ++c) {
            red= filtered_img[r][2+3*c]+128;
            green= filtered_img[r][1+3*c]+128;
            blue= filtered_img[r][3*c]+128;

            red= red>255? 255: (red<0? 0: red);
            green= green>255? 255: (green<0? 0: green);
            blue= blue>255? 255: (blue<0? 0: blue);

            output_image[r][c].Red= (unsigned char) red;
            output_image[r][c].Green= (unsigned char) green;
            output_image[r][c].Blue= (unsigned char) blue;
        }
    }
}

/*
* @brief convert_Trunc
*         This function is to normalize the image and convert the
*         pixel values in the image back to 8bits (0~255) using magnitude
*         method that takes absolute value of pixel value and clip them
*         back to 0~255
* @para  **filtered_img
*        The pointer pointing to filtered image
* @para  ROWS
*        the amount of rows of filtered image
*
* @para  COLS
*       the amount of columns of filtered image
*
* @para  **output_image
*        return the normalized output image
*/
void convert_Mag(int **filtered_img, int ROWS, int COLS, PIXEL **output_image)
{
    int r=0, c=0;
    int red=0, green=0, blue=0;
    for (r=0; r< ROWS; ++r) {
        for (c = 0; c < COLS; ++c) {
            red= abs(filtered_img[r][2+3*c]);
            green=abs(filtered_img[r][1+3*c]);
            blue= abs(filtered_img[r][0+3*c]);

            red= red>255? 255 :red;
            green= green>255? 255: green;
            blue= blue>255? 255: blue;

            output_image[r][c].Red= (unsigned char) red;
            output_image[r][c].Green= (unsigned char) green;
            output_image[r][c].Blue= (unsigned char) blue;
        }
    }
}
/*
* @brief convert_Trunc
*         This function is to normalize the image and convert the
*         pixel values in the image back to 8bits (0~255) using scale
*         method that use 128 + (pixel value)/8 to calculate result values
* @para  **filtered_img
*        The pointer pointing to filtered image
* @para  ROWS
*        the amount of rows of filtered image
*
* @para  COLS
*       the amount of columns of filtered image
*
* @para  **output_image
*        return the normalized output image
*/
void convert_Scale(int **filtered_img, int ROWS, int COLS, PIXEL **output_image)
{
    int r=0, c=0;
    int red=0, green=0, blue=0;
    for (r=0; r< ROWS; ++r) {
        for (c = 0; c < COLS; ++c) {
            red= 128+ filtered_img[r][2+3*c]/8;
            green=128+filtered_img[r][1+3*c]/8;
            blue=128+ filtered_img[r][3*c]/8;


            output_image[r][c].Red= (unsigned char) red;
            output_image[r][c].Green= (unsigned char) green;
            output_image[r][c].Blue= (unsigned char) blue;
        }
    }
}
