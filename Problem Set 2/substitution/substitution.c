#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv[])
{
    //Checking to make sure there is only one command line argument of the key
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    //convert the second command line argument string into a char array of its own to cycle through
    string sub = argv[1];

    //Create the alphabet as a char array so that we can cycle through and convert the letters to the number 1
    //This is so that you have to enter each char of the alpha only once and use all of them
    //This works as if the sum of the array isn't 26 then not all characters have been used or some used twice
    char alpha[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int n = strlen(sub);
    int i, j, y;

    for (j = 0; j < n; j++)
    {
        y = toupper(sub[j]);
        for (i = 0; i < 26; i++)
        {
            if (y == (int) alpha[i])
            {
                alpha[i] = 1;
            }
        }
    }

    int sum = 0;
    int k;

    for (k = 0; k < 26; k++)
    {
        sum += alpha[k];
    }

    if (n != 26 || sum != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }


    //Input the plaintext which is stored in a char array (string) so that we can cycle through and convert these using the key
    //Output to the ciphertext array the converted letter
    string plaintext = get_string("plaintext: ");
    int N = strlen(plaintext);
    char ciphertext[N];
    ciphertext[N] = '\0';

    int x;

    for (i = 0; i < N; i++)
    {
        if (isupper(plaintext[i]) > 0)
        {
            x = (int) plaintext[i] - 65;
            ciphertext[i] = toupper(sub[x]);
        }
        else if (islower(plaintext[i]) > 0)
        {
            x = (int) plaintext[i] - 97;
            ciphertext[i] = tolower(sub[x]);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    //Finally print the full ciphertext array which is a string

    printf("ciphertext: %s\n", ciphertext);
    return 0;
}
