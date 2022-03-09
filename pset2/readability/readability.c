#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

int main(void)
{   
    char *text = get_string("what is your string?: ");
    float letter = 0;
    float words = 1;//word quantity increases with space. It starts with " 1" for the first word
    float sentence = 0;
    
    for (int i = 0 ; text[i] ; i++)
        //this loop will count every letters, words and sentences
    {
        if (isalpha(text[i]))
        {
            letter++;
        }
        if (text[i] == ' ')
        {
            words++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence++;
        }
            
    }

    double L = (letter * 100) / words; //L is the average number of letters per 100 words in the text
    double S = (sentence * 100) / words; //S is the average number of sentences per 100 words in the text.


    int index = round(0.0588 * L - 0.296 * S - 15.8);//this formula is given before




    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    if (index > 1 && index <= 16)
    {
        printf("Grade %i\n", index);
    }


}