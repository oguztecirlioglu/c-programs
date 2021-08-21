#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue = image[i][j].rgbtBlue;
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;

            int average = round((blue + green + red) / 3);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width / 2; column++)
        {
            RGBTRIPLE tmp = image[row][column];
            image[row][column] = image[row][width - (column + 1)];
            image[row][width - (column + 1)] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            tmp[row][column] = image[row][column];
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            float sumBlue, sumGreen, sumRed;
            int counter;
            tmp[row][column] = image[row][column];
            sumBlue = sumGreen = sumRed = counter = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j<=1; j++)
                {
                    if ((row+i < 0) || (row+i >= height)) //check if rows are out of bounds
                    {
                        continue;
                    }

                    if ((column+j < 0) || (column+j >= width)) //check if columns are out of bounds
                    {
                        continue;
                    }

                    sumBlue += tmp[row + i][column + j].rgbtBlue;
                    sumGreen += tmp[row + i][column + j].rgbtGreen;
                    sumRed += tmp[row + i][column + j].rgbtRed;
                    counter++;
                }
            }
            image[row][column].rgbtBlue = round(sumBlue / counter);
            image[row][column].rgbtGreen = round(sumGreen / counter);
            image[row][column].rgbtRed = round(sumRed / counter);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            tmp[row][column] = image[row][column];
        }
    }

    int gX[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int gY[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};



    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            float gXSumBlue, gYSumBlue, gXSumGreen, gYSumGreen, gXSumRed, gYSumRed;
            gXSumBlue = gYSumBlue = gXSumGreen =  gYSumGreen = gXSumRed = gYSumRed = 0;

            for(int i = -1; i < 2; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    if((row + i < 0) || (row + i >= height) || (column + j < 0) || (column + j >= width)) //check if rows are out of bounds
                    {
                        continue;
                    }
                    gXSumBlue += tmp[row + i][column + j].rgbtBlue*gX[i+1][j+1];
                    gYSumBlue += tmp[row + i][column + j].rgbtBlue*gY[i+1][j+1];
                    gXSumGreen += tmp[row + i][column + j].rgbtGreen*gX[i+1][j+1];
                    gYSumGreen += tmp[row + i][column + j].rgbtGreen*gY[i+1][j+1];
                    gXSumRed += tmp[row + i][column + j].rgbtRed*gX[i+1][j+1];
                    gYSumRed += tmp[row + i][column + j].rgbtRed*gY[i+1][j+1];
                }
            }
            image[row][column].rgbtBlue = round(sqrt(pow(gXSumBlue,2) + pow(gYSumBlue,2))) > 255 ? 255 : round(sqrt(pow(gXSumBlue,2) + pow(gYSumBlue,2)));
            image[row][column].rgbtRed = round(sqrt(pow(gXSumRed,2) + pow(gYSumRed,2))) > 255 ? 255 : round(sqrt(pow(gXSumRed,2) + pow(gYSumRed,2)));
            image[row][column].rgbtGreen = round(sqrt(pow(gXSumGreen,2) + pow(gYSumGreen,2))) > 255 ? 255 : round(sqrt(pow(gXSumGreen,2) + pow(gYSumGreen,2)));
        }

    }


    return;
}
