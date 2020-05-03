#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2) // command-line argument have to be 2
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < strlen(argv[1]); i++) // chech through each char in the string
        {
            if (!isdigit(argv[1][i])) // make sure the key is decimal digit
            {
                printf("Usage: ./caesar key\n");
                return 1;
                break;
            }
        }
        string p = get_string("plaintext: ");
        int key = atoi(argv[1]); // convert the key into int
        for (int x = 0; x < strlen(p); x++) // check through each char in the plaintext
        {
            if (isalpha(p[x])) // make sure to change only letters
            {
                if (p[x] < 91) // if the letter is < 91 that mesans it is capital letter
                {
                    p[x] = (((p[x] - 65) + key) % 26) + 65; // letter - 65 to create alphabetical index from capital letters
                }
                else
                {
                    p[x] = (((p[x] - 97) + key) % 26) + 97; // letter - 97 to create alphabetical index from small letters
                }

            }
        }
        printf("ciphertext: %s\n", p);
    }
}

