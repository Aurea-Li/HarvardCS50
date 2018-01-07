#include <stdio.h>
#include <stdint.h>


typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }


    // initialize variables
    int jpeg = 0;
    char outfile[8];
    BYTE buffer[512];
    FILE *outptr;




    // iterate loop until less than 512 bytes left
    while (fread(&buffer, 512, 1, inptr) == 1)
    {


        // if header is JPEG header
        if(buffer[0] == 0xff
        && buffer[1] == 0xd8
        && buffer[2] == 0xff
        && (buffer[3] & 0xf0) == 0xe0)
        {

            // if a JPEG has already been found
            if(jpeg != 0)
            {
                // end of previous jpeg, close it and create new file
                fclose(outptr);
            }

            // initialize and start writing to output file
            sprintf(outfile, "%03i.jpg", jpeg);
            outptr = fopen(outfile, "w");
            fwrite(&buffer, 512, 1, outptr);
            jpeg++;
        }
        // if not jpeg header
        else
        {
            // check if we have found a jpeg
            if(jpeg != 0)
            {
                // continue writing to file
                fwrite(&buffer, 512, 1, outptr);
            }
        }
    }


    fclose(inptr);
    fclose(outptr);
}