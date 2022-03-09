#include <stdio.h>
# include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;  
int main(int argc, char *argv[])
{
    FILE *sdcard = fopen("card.raw", "r");  // Open raw file with card pointer
    if (sdcard == NULL) //if there is no address for card programm fails
    {
        return 1;
    }
    
    if (argc != 2)  // Check usage
    {
        return 1;
    }
    
    unsigned char buffer[512 * sizeof(BYTE)];//CREATE BUFFER 
    FILE *pic = NULL;   // Define pointer for jpeg files to be created
    int counter = 0;    //Jpeg counter
    int isjpeg = 0; //JPEG FOUND
    char jpegname[8]; //Array for jpeg name
    
    while ((fread(buffer, 512 * sizeof(BYTE), 1, sdcard) == 1)) //read until the end of the file in 512 bytes chunks
    {   
        //if first four bytes confirms it is a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (isjpeg == 1) //if a new jpeg is found, then the old jpeg file should be closed
            {
                fclose(pic);
            }
            else
            {
                isjpeg = 1; //if a new jpeg is found, isjpeg should be always 1.
            }
            sprintf(jpegname, "%03d.jpg", counter);//writes counter to the jpegname array with formatted .jpeg prefix
            pic = fopen(jpegname, "a"); //open jpegname which was edited above with append mode, because this loop can be sequel of previous jpegs.
            counter++; //counter up, so it can be used for next jpegfile.
        }
        if (isjpeg == 1) //this will be executed until the end of file. after the first discovery of a jpeg file.
        {
            fwrite(buffer, 512 * sizeof(BYTE), 1, pic); //goes to buffer which stores datas, and writes it to the address of pic pointer.
        }
    }
    fclose(pic);    //cleaning time
    fclose(sdcard); //cleaning time

}
