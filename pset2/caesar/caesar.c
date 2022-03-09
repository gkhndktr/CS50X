#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <stdlib.h>
//OK//Recall that the string.h header file contains a number of useful functions that work with strings.
//OK//Recall that we can use a loop to iterate over each character of a string if we know its length.
//OK//Recall that the ctype.h header file contains a number of useful functions that tell us things about characters.
//OK//Recall that we can return nonzero values from main to indicate that our program did not finish successfully.
//OK//Recall that with printf we can print an integer using %i as the placeholder.
//OK//Recall that the atoi function converts a string that looks like a number into that number.

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int key_lenght = strlen(argv[1]);

        for (int i = 0 ; i < key_lenght; i++)
        {
            if (isdigit(argv[1][i]))
            {
                //printf("%c is a digit\n",argv[1][i]);
            }
            else
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        int key = atoi(argv[1]);
        //printf(" %i this is the int VALUE of the argv \n", key );
    }
    string plaintext = get_string("plaintext: ");
//printf("%c is the first char of the plaintext\n",plaintext[0] );
//printf("%i is the ascii value of the first char of the plaintext\n",plaintext[0] );

//65 A
//90 Z
//97 a
//122 z

    int text_lenght = strlen(plaintext);
    int change_quantity = atoi(argv[1]) % 26;
    for (int i = 0 ; i < text_lenght ; i++)
    {
        int check_number = 0;
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                if ((plaintext[i] + change_quantity) > 90)
                {
                    plaintext[i] = change_quantity + plaintext[i] - 26 ;
                }
                else
                {
                    plaintext[i] = plaintext[i] + change_quantity;
                }
            }
            else
            {
                if ((plaintext[i] + change_quantity) > 122)
                {
                    plaintext[i] = change_quantity + plaintext[i] - 26;
                }
                else
                {
                    plaintext[i] = plaintext[i] + change_quantity;
                }
            }
        }
    }
    printf("ciphertext:%s\n", plaintext);
}
