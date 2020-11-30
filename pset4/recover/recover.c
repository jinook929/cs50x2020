#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Open files
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) 
    { 
        printf("Could not open file %s\n", argv[1]); 
        return 1; 
    }
    FILE *img;
    FILE *img_a;
    
    // Set 512B buffer for reading
    BYTE buffer[512];
    
    // Set aside array for image file name
    char filename[8];
    
    // Count jpeg files
    int jpegCounter = -1;

    // Read byte from buffer
    int num;

    // Read the original file to the end
    while (!feof(file))
    {
        // Read the 512B buffer
        num = fread(buffer, 1, 512, file);

        // Check if reading is the beginning of jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            jpegCounter++;

            sprintf(filename, "%03i.jpg", jpegCounter);
            img = fopen(filename, "w");
            fwrite(buffer, 1, 512, img);
            fclose(img);
        }
        // If reading is not jpeg beginning...
        else
        {
            // Check if the block is after the first jpeg block
            if (jpegCounter != -1)
            {
                img_a = fopen(filename, "a");
                fwrite(buffer, 1, num, img_a);
                fclose(img_a);
            }
        }
    }
    
    fclose(file);
    
    return 0;
}