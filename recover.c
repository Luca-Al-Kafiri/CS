#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }
    // open the card.
    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Can not read the card");
        return 1;
    }
    
    // array of 512 bytes which I want to read from the card each time.
    unsigned char bytes[512];
    // counter to keep track of the numbr of images found.
    int counter = 0;
    // asign enough memory for the name of each image.
    char *found = malloc(10);
    // asign a FILE for each image.
    FILE *pic;

    // if fread < 512 then the card has no more memory.
    while (fread(&bytes, sizeof(unsigned char), 512, card) == 512)
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {   
            // we found image and it is not the first one so we need to close the opened one.
            if (counter > 0)
            {
                fclose(pic);
            }
            
            // create a name for the new image.
            sprintf(found, "%03i.jpg", counter);
            // open new file for the new image.
            pic = fopen(found, "w");
            counter++;

        }
        // no new image found so keep writing in the opend one.
        if (counter > 0)
        {
            fwrite(&bytes, sizeof(unsigned char), 512, pic);

        }
    }
    // free malloc.
    free(found);
    // close the card file.
    fclose(card);
    return 0;


}
