#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Take each pixel one by one and work out the average hexadecimal value
    // Then make all following RBG values in the struct equal to this
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            float x = image[i][j].rgbtBlue;
            float y = image[i][j].rgbtGreen;
            float z = image[i][j].rgbtRed;
            int a = round((x + y + z) / 3);
            image[i][j].rgbtBlue = a;
            image[i][j].rgbtGreen = a;
            image[i][j].rgbtRed = a;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    // if larger than 255 then cap at this value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float r = image[i][j].rgbtRed;
            float b = image[i][j].rgbtBlue;
            float g = image[i][j].rgbtGreen;

            image[i][j].rgbtRed = fmin(round(.393 * r + .769 * g + .189 * b), 255);
            image[i][j].rgbtGreen = fmin(round(.349 * r + .686 * g + .168 * b), 255);
            image[i][j].rgbtBlue = fmin(round(.272 * r + .534 * g + .131 * b), 255);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // This needs to be an exact mirror version of the original image, left side on right and visa versa
    // Horizontally stays the same
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE x = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = x;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Need to average the values of all pixels that are within 1 row and column of the original pixel.
    // Use the idea that code runs downwards so scan to see if each position around the pixel is in the array and so add values to the red/blue/green int and 1 to counter.
    // Need to use a temp array for the new image so all the values from original are not altered till the very end.
    RGBTRIPLE **output_image = (RGBTRIPLE **) malloc(sizeof(RGBTRIPLE *) *height);
    for (int i = 0; i < height; i++)
    {
        output_image[i] = (RGBTRIPLE *) malloc(sizeof(RGBTRIPLE) * width);
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            output_image[i][j] = image[i][j];
        }
    }

    float avgred, avgblue, avggreen, counter;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            counter = 1;
            avgred = output_image[i][j].rgbtRed;
            avgblue = output_image[i][j].rgbtBlue;
            avggreen = output_image[i][j].rgbtGreen;
            // bottom left
            if (i + 1 < height && j - 1 >= 0)
            {
                avgred += output_image[i + 1][j - 1].rgbtRed;
                avgblue += output_image[i + 1][j - 1].rgbtBlue;
                avggreen += output_image[i + 1][j - 1].rgbtGreen;
                counter++;
            }
            // bottom centre
            if (i + 1 < height)
            {
                avgred += output_image[i + 1][j].rgbtRed;
                avgblue += output_image[i + 1][j].rgbtBlue;
                avggreen += output_image[i + 1][j].rgbtGreen;
                counter++;
            }
            // bottom right
            if (i + 1 < height && j + 1 < width)
            {
                avgred += output_image[i + 1][j + 1].rgbtRed;
                avgblue += output_image[i + 1][j + 1].rgbtBlue;
                avggreen += output_image[i + 1][j + 1].rgbtGreen;
                counter++;
            }
            // top left
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                avgred += output_image[i - 1][j - 1].rgbtRed;
                avgblue += output_image[i - 1][j - 1].rgbtBlue;
                avggreen += output_image[i - 1][j - 1].rgbtGreen;
                counter++;
            }
            // top centre
            if (i - 1 >= 0)
            {
                avgred += output_image[i - 1][j].rgbtRed;
                avgblue += output_image[i - 1][j].rgbtBlue;
                avggreen += output_image[i - 1][j].rgbtGreen;
                counter++;
            }
            // top right
            if (i - 1 >= 0 && j + 1 < width)
            {
                avgred += output_image[i - 1][j + 1].rgbtRed;
                avgblue += output_image[i - 1][j + 1].rgbtBlue;
                avggreen += output_image[i - 1][j + 1].rgbtGreen;
                counter++;
            }
            // left
            if (j - 1 >= 0)
            {
                avgred += output_image[i][j - 1].rgbtRed;
                avgblue += output_image[i][j - 1].rgbtBlue;
                avggreen += output_image[i][j - 1].rgbtGreen;
                counter++;
            }
            // right
            if (j + 1 < width)
            {
                avgred += output_image[i][j + 1].rgbtRed;
                avgblue += output_image[i][j + 1].rgbtBlue;
                avggreen += output_image[i][j + 1].rgbtGreen;
                counter++;
            }
            image[i][j].rgbtRed = round(avgred / counter);
            image[i][j].rgbtBlue = round(avgblue / counter);
            image[i][j].rgbtGreen = round(avggreen / counter);
        }
    }
}
