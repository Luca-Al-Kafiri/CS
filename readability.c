#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");

    float letters = 0; // letters total
    float words = 1; // words total
    float sentences = 0; // sentences total
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters++;
        }
        if (text[i] == ' ')
        {
            words++;
        }
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }
    float l = 100 * letters / words; // average number of letters per 100 words
    float s = 100 * sentences / words; // average number of sentences per 100 words
    int index = round(0.0588 * l - 0.296 * s - 15.8); // Coleman-Liau index's formula

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.i\n", index);
    }

}





