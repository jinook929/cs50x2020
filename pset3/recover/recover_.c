#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure correct usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // open image file
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // find beginning of JPEG
    int *buffer;
    buffer = (int *) malloc(513);

    if (!buffer)
    {
        fprintf(stderr, "Memory Error\n");
        return 2;
    }

    fseek(file, 0, SEEK_SET);
    fread(&buffer[0], 512, 1, file);

    for (int i = 0; i < 50; i++)
    {
        printf("buffer[%i] = %i\n", i, buffer[i]);
    }

    free(buffer);

    // if (buffer[0] == 0xff &&
    //     buffer[1] == 0xd8 &&
    //     buffer[2] == 0xff &&
    //     (buffer[3] & 0xf0) == 0xe0)
    // {

    // // open new JPEG
    // sprintf(filename, "%03i.jpg", #);
    // FILE *img = fopen(filename, "w");

    // // write in JPEG
    // fwrite(*buffer[i], 1, 512, img)

    // // detect end of file
    // if
}

