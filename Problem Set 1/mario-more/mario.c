//Both needed to make sure we have all the libraries we need
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //this integer is to get the height of the pyramids
    //integer needs to be between 1 and 8 so need a do while loop
    //the while loop needs an or conitional ||
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while ((h < 1) || (h > 8));

    //initializing n to be h so that we can hold the value of h
    //n will be reduced by one each time a new row is created, this is when i increases by 1
    int n = h;

    //for loop going up to the h value chosen
    for (int i = 0; i < h; i++)
    {
        //initializing w so that we can set it to 0 in the inner loop once it has been used to output the right number of spaces before the first #
        //setting w = 0 means we can exit this part of the loop until we move onto the new row where we can reset the value of w
        //basically an exit value or stop this function
        int w = (n - 1);
        //second for loop to draw the correct number of # per row
        for (int j = 0; j < (i + 1); j++)
        {
            //inner loop to draw correct number of spaces before the first #
            for (int k = w; k > 0; k--)
            {
                printf(" ");
            }
            w = 0;
            printf("#");
        }
        //print the 2 spaces in the middle of the blocks
        printf("  ");
        //last loop copy so that it will print the correct number of # after the 2 spaces
        for (int j = 0; j < (i + 1); j++)
        {
            printf("#");
        }
        //create new line after we have printed the correct number of # and spaces
        printf("\n");
        //reduce n by one within the loop so that we can correctly reset w
        n--;
    }
}












