#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{

    string A = get_string("Text: ");

    int letters = count_letters(A);
    int words = count_words(A);
    int sentences = count_sentences(A);

    float L = ((float) letters / (float) words) * 100;
    float S = ((float) sentences / (float) words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);

    if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}


int count_letters(string text)
{
    int n = strlen(text);
    int i;
    int count = 0;

    for (i = 0; i < n; i++)
    {
        if (islower(text[i]) > 0 || isupper(text[i]) > 0)
        {
            count++;
        }
        else
        {
            count += 0;
        }
    }
    return count;
}


int count_words(string text)
{
    int n = strlen(text);
    int i;
    int count = 1;

    for (i = 0; i < n; i++)
    {
        if ((int) text[i] == 32)
        {
            count++;
        }
        else
        {
            count += 0;
        }
    }
    return count;
}


int count_sentences(string text)
{
    int n = strlen(text);
    int i;
    int count = 0;

    for (i = 0; i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
        else
        {
            count += 0;
        }
    }
    return count;
}