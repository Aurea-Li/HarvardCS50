// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize f infile outfile\n");
        return 1;
    }

    // remember filenames
    float factor;
    factor = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);



    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine old padding
    int padding_old = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // save height and width
    int Height = bi.biHeight;
    int Width = bi.biWidth;

    // scale width and height for new image
    bi.biWidth *= factor;
    bi.biHeight *= factor;


    // determine new padding
    int padding_new = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // calculate new bitmap size image
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding_new) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // stretching
    if (factor >= 1)
    {
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(Height); i < biHeight; i++)
        {
            // save curser position to repeat iteration
            long cursor = ftell(inptr);
            printf("Curser saved at %lu\n",cursor);


            printf("Iterating over row %i\n",i+1);
            for (int row = 0; row < factor; row++)
            {
                 // iterate over pixels in scanline
                for (int j = 0; j < Width; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);


                    for (int col = 0; col < factor; col++)
                    {
                        // write RGB triple to outfile
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }

                // skip over old padding, if any
                fseek(inptr, padding_old, SEEK_CUR);

                // add in new padding
                for (int m = 0; m < padding_new; m++)
                {
                    fputc(0x00, outptr);
                }

                // reposition curser for row iteration if we want to repeat row
                if ((row + 1) < factor)
                {
                    fseek(inptr,cursor,SEEK_SET);
                }
            }
        }
    }
    // shrink
    else
    {
        int inverse = 1 / factor;
        printf("Inverse = %i\n",inverse);
        printf("Height = %i\n", abs(Height));
        printf("Width = %i\n", abs(Width));

        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(Height); i < biHeight; i++)
        {
             // iterate over pixels in scanline
            for (int j = 0; j < Width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                printf("READ: i = %i, j = %i, Red = %02X, Blue = %02X, Green = %02X\n",i,j,triple.rgbtRed,triple.rgbtBlue, triple.rgbtGreen);

                if (i % inverse == 0 && j % inverse == 0)
                {

                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    printf("i = %i, j = %i\n",i,j);
                    printf("WRITTEN: i = %i, j = %i, Red = %02X, Blue = %02X, Green = %02X\n" ,i, j,triple.rgbtRed,triple.rgbtBlue, triple.rgbtGreen);

                }
            }
            // skip over old padding, if any
            fseek(inptr, padding_old, SEEK_CUR);

            // put padding if we're adding row
            if (i % inverse == 0)
            {
                // add in new padding
                for (int m = 0; m < padding_new; m++)
                {
                    fputc(0x00, outptr);
                }
            }

        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

