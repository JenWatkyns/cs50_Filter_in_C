#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each column and row of pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get value of each colour in 2D array
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            // calculate average of each pixel and round off
            int ave = round((red + green + blue) / 3.0);

            //set the calculated value to be the new value of each pixel
            image[i][j].rgbtRed = ave;
            image[i][j].rgbtGreen = ave;
            image[i][j].rgbtBlue = ave;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each column and row of pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Calculate sepia value
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Rules for if the sepia value produced is greater than 255
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }

            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }

            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }

            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each column and row of pixels until a midpoint is reached
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            // Swap pixels
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float aveRed, aveGreen, aveBlue;
    int counter;
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            aveRed = aveGreen = aveBlue = 0;
            counter = 0;

            // Pixel
            aveRed += image[i][j].rgbtRed;
            aveGreen += image[i][j].rgbtGreen;
            aveBlue += image[i][j].rgbtBlue;
            counter++;

            // Left pixel
            if (j - 1 >= 0)
            {
                aveRed += image[i][j - 1].rgbtRed;
                aveGreen += image[i][j - 1].rgbtGreen;
                aveBlue += image[i][j - 1].rgbtBlue;
                counter++;
            }

            // Upper pixel
            if (i - 1 >= 0)
            {
                aveRed += image[i - 1][j].rgbtRed;
                aveGreen += image[i - 1][j].rgbtGreen;
                aveBlue += image[i - 1][j].rgbtBlue;
                counter++;
            }

            // Right pixel
            if (j + 1 < width)
            {
                aveRed += image[i][j + 1].rgbtRed;
                aveGreen += image[i][j + 1].rgbtGreen;
                aveBlue += image[i][j + 1].rgbtBlue;
                counter++;
            }

            // Lower pixel
            if (i + 1 < height)
            {
                aveRed += image[i + 1][j].rgbtRed;
                aveGreen += image[i + 1][j].rgbtGreen;
                aveBlue += image[i + 1][j].rgbtBlue;
                counter++;
            }

            // Upper left pixel
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                aveRed += image[i - 1][j - 1].rgbtRed;
                aveGreen += image[i - 1][j - 1].rgbtGreen;
                aveBlue += image[i - 1][j - 1].rgbtBlue;
                counter++;
            }

            // Upper right pixel
            if (i - 1 >= 0 && j + 1 < width)
            {
                aveRed += image[i - 1][j + 1].rgbtRed;
                aveGreen += image[i - 1][j + 1].rgbtGreen;
                aveBlue += image[i - 1][j + 1].rgbtBlue;
                counter++;
            }

            // Lower right pixel
            if (i + 1 < height && j + 1 < width)
            {
                aveRed += image[i + 1][j + 1].rgbtRed;
                aveGreen += image[i + 1][j + 1].rgbtGreen;
                aveBlue += image[i + 1][j + 1].rgbtBlue;
                counter++;
            }

            // Lower left pixel
            if (i + 1 < height && j - 1 >= 0)
            {
                aveRed += image[i + 1][j - 1].rgbtRed;
                aveGreen += image[i + 1][j - 1].rgbtGreen;
                aveBlue += image[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            
            // Pass values through to the temp array
            temp[i][j].rgbtRed = round(aveRed / counter);
            temp[i][j].rgbtGreen = round(aveGreen / counter);
            temp[i][j].rgbtBlue = round(aveBlue / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Convert temp array to image
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
