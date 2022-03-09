
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int brick;//integers named as words instead of chars to be understood well
    int bos;
    int tum;
    int kare;
    do
    {
        brick = get_int("Height:\n");//height will be considered as 8 for explanation
    }
    while (1 > brick || brick > 8);
    
    
    for (tum = 0 ; tum < brick ; tum++)//prints line as quantity as "height". There will be 8 line with hash.
    {
        for (bos = 0 ; bos < (brick - tum - 1) ; bos++)
            //this loop ensures hashes to be right aligned by spaces. Number of spaces is calculated as height minus number of the line. there will be 7 space for the first line.
        {
            printf(" ");
        }
        for (kare = 0 ; kare < (brick - bos); kare++)
            //this loop stars after space writing work is done. Number of hashes is calculated by height minus number of spaces. For first line there will be 8-7=1 hash.
        {
            printf("#");
        }
        printf("\n");//after spacing and hashing is completed for a line next line will be checked.
    }

}