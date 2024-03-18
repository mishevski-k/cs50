#include "helpers.h"
#include <math.h>

RGBTRIPLE findAvarage(int height, int width, int row, int column, RGBTRIPLE image[height][width]);
RGBTRIPLE calculateEdge(int height, int width, int row, int column, RGBTRIPLE image[height][width]);

typedef struct
{
    int x;
    int y;
} G;

int GxWeight[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

int GyWeight[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            image[i][j] = calculateEdge(height, width, i, j, copyImage);
        }
    }

    return;
}

RGBTRIPLE calculateEdge(int height, int width, int row, int column, RGBTRIPLE image[height][width])
{
    G red;
    red.x = 0;
    red.y = 0;
    G green;
    green.x = 0;
    green.y = 0;
    G blue;
    blue.x = 0;
    blue.y = 0;

    int countX;
    int countY = 0;

    for (int i = row - 1, n = row + 1; i <= n; i++)
    {
        countX = -1;
        for (int j = column - 1, m = column + 1; j <= m; j++)
        {
            countX++;

            if (i < 0 || i > height - 1 || j < 0 || j > width - 1)
            {
                continue;
            }

            red.x += image[i][j].rgbtRed * GxWeight[countY][countX];
            red.y += image[i][j].rgbtRed * GyWeight[countY][countX];

            green.x += image[i][j].rgbtGreen * GxWeight[countY][countX];
            green.y += image[i][j].rgbtGreen * GyWeight[countY][countX];

            blue.x += image[i][j].rgbtBlue * GxWeight[countY][countX];
            blue.y += image[i][j].rgbtBlue * GyWeight[countY][countX];
        }

        countY++;
    }
    int redChannel = round(sqrt(red.x * red.x + red.y * red.y));
    int greenChannel = round(sqrt(green.x * green.x + green.y * green.y));
    int blueChannel = round(sqrt(blue.x * blue.x + blue.y * blue.y));

    RGBTRIPLE new;
    new.rgbtRed = (redChannel > 255) ? 255 : redChannel;
    new.rgbtGreen = (greenChannel > 255) ? 255 : greenChannel;
    new.rgbtBlue = (blueChannel > 255) ? 255 : blueChannel;

    return new;
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
