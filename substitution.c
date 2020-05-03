#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2) // command-line argument have to be 2
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) < 26) // key should contain 26 characters
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < strlen(argv[1]); i++) // Key musy only contain alphapetic characters
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Key musy only contain alphapetic characters\n");
                return 1;
                break;
            }
            for (int x = i + 1; x < strlen(argv[1]); x++) // Key must not contain repeated characters
            {
                if (argv[1][i] == argv[1][x])
                {
                    printf("Key must not contain repeated characters\n");
                    return 1;
                    break;
                }
            }
        }
    }
    string p = get_string("Plaintext: "); // get the plaintext from the user
    string a = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // alphabetical string to compare with the key
    for (int z = 0; z < strlen(p); z++) // check each letter in the plaintext
    {
        for (int w = 0; w < strlen(argv[1]); w++) // look for the same letter in the key
        {
            if (toupper(p[z]) == a[w])
            {
                if (isupper(p[z]))
                {
                    p[z] = toupper(argv[1][w]); // replace the letter in plaintext with the key ones
                    break;

                }
                else
                {
                    p[z] = tolower(argv[1][w]);
                    break;
                }
            }
        }
    }
    printf("ciphertext: %s\n", p);
}












