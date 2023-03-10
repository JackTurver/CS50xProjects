#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Open the file
    // Check for JPEG's which always have header of 0xff, 0xd8, 0xff, 0xeX where x is any value from 0-f
    // If this is at the start of any 512 byte block then its a JPEG
    // Each JPEG is stored back to back in the memory card
    // Open a new JPEG file and start writing the read bytes block by block until you see another 512 byte block with JPEG header
    // Now need to stop, open new JPEG file and follow same process

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *img = fopen(argv[1], "r");
    if (img == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    int BLOCK_SIZE = 512;
    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];
    int counter = -1;
    char *filename = malloc(8);
    FILE *jpg;

    // while the 512 byte blocks are still being read (not the end of the file, keep the loop going)
    while (fread(buffer, 1, BLOCK_SIZE, img) == BLOCK_SIZE)
    {
        // if you find the header of a JPG then we need to see if it is the first or not
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if this is the first jpg found then we need to
            if (counter < 0)
            {
                counter++;
                sprintf(filename, "%03i.jpg", counter);
                jpg = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, jpg);
            }
            else if (counter >= 0)
            {
                fclose(jpg);
                counter++;
                sprintf(filename, "%03i.jpg", counter);
                jpg = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, jpg);
            }
        }
        else if (counter >= 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, jpg);
        }
    }
    free(filename);
    fclose(jpg);
    fclose(img);
}