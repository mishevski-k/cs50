#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover infile\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Could not open file: %s\n", argv[1]);
        return 2;
    }

    FILE *output = NULL;

    uint8_t buffer[512];

    int countJpg = 0;

    char fileName[8] = {0};

    while (fread(buffer, sizeof(uint8_t) * 512, 1, input) == 1)
    {
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) &&
            ((buffer[3] & 0xf0) == 0xe0))
        {
            if (output != NULL)
            {
                fclose(output);
            }

            sprintf(fileName, "%03d.jpg", countJpg++);

            output = fopen(fileName, "w");
        }

        if (output != NULL)
        {
            fwrite(buffer, sizeof(uint8_t) * 512, 1, output);
        }
    }

    if (output != NULL)
    {
        fclose(output);
    }

    fclose(input);

    return 0;
}
