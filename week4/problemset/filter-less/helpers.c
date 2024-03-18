#include "helpers.h"
#include <math.h>

RGBTRIPLE findAvarage(int height, int width, int row, int column, RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avarage =
                round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);

            image[i][j].rgbtRed = avarage;
            image[i][j].rgbtBlue = avarage;
            image[i][j].rgbtGreen = avarage;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            int newRed = round((0.393 * red) + (0.769 * green) + (0.189 * blue));
            int newGreen = round((0.349 * red) + (0.686 * green) + (0.168 * blue));
            int newBlue = round((0.272 * red) + (0.534 * green) + (0.131 * blue));

            if (newRed > 255)
            {
                newRed = 255;
            }

            if (newGreen > 255)
            {
                newGreen = 255;
            }

            if (newBlue > 255)
            {
                newBlue = 255;
            }

            image[i][j].rgbtRed = newRed;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtBlue = newBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = round(width / 2); j < n; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE copyImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyImage[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = findAvarage(height, width, i, j, copyImage);
        }
    }

    return;
}

RGBTRIPLE findAvarage(int height, int width, int row, int column, RGBTRIPLE image[height][width])
{
    int red = 0;
    int green = 0;
    int blue = 0;
    int count = 0;

    for (int i = row - 1, n = row + 1; i <= n; i++)
    {
        if (i < 0 || i >= height)
        {
            continue;
        }

        for (int j = column - 1, m = column + 1; j <= m; j++)
        {
            if (j < 0 || j >= width)
            {
                continue;
            }

            count++;
            red += image[i][j].rgbtRed;
            green += image[i][j].rgbtGreen;
            blue += image[i][j].rgbtBlue;
        }
    }

    red = round((float) red / count);
    green = round((float) green / count);
    blue = round((float) blue / count);

    RGBTRIPLE temp;
    temp.rgbtRed = red;
    temp.rgbtGreen = green;
    temp.rgbtBlue = blue;

    return temp;
}
