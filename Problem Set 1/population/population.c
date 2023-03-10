#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size

    int i;
    do
    {
        i = get_int("Start size: ");
    }
    while (i < 9);


    // TODO: Prompt for end size

    int j;
    do
    {
        j = get_int("End size: ");
    }
    while (j < i);


    // TODO: Calculate number of years until we reach threshold
    // n is the overall calculation value
    // y is tracking how many years have passed

    int n;
    int y = 0;

    for (n = i; n < j; n = n + n / 3 - n / 4)
    {
        y++;
    }


    // TODO: Print number of years

    printf("Years: %i\n", y);
}