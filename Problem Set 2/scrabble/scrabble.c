#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner

    // Need to just use an if function to print Player X wins! or Tie!
    if (score1 > score2)
    {
        printf("Player 1 wins!\n!");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string

    // Need to calculate the length of the word
    int n = strlen(word);
    // Turn the string word into an array of stored characters
    int i, alphabet, x;
    int calc = 0;
    // Need to cycle through the letters of the word and work out the score of that letter using the POINTS[] array
    for (i = 0; i < n ; i++)
    {
        // Need to remember to force all upper or lower case to have same value from the word before computing
        // Char's that are not letters should be given a value of 0 so if function needed there
        // For this use the isupper() and is islower() functions. isupper() 0 if not uppercase alphabet. islower() 0 if not lowercase alphabet
        if (islower(word[i]) > 0)
        {
            alphabet = (int) word[i] - 97;
            x = POINTS[alphabet];
        }
        else if (isupper(word[i]) > 0)
        {
            alphabet = (int) word[i] - 65;
            x = POINTS[alphabet];
        }
        else
        {
            x = 0;
        }
        // Need to keep a count of the sum of the score of that word through the loop
        calc += x;
    }
    return calc;
}
