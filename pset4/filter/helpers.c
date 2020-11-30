#include <stdio.h>
#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int grayscaleNum;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            grayscaleNum = round((double)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtRed = grayscaleNum;
            image[i][j].rgbtGreen = grayscaleNum;
            image[i][j].rgbtBlue = grayscaleNum;
        }
    }
    
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaGreen = 255;
            }
            
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy [height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j].rgbtRed = image[i][j].rgbtRed;
            imageCopy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imageCopy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    
    int blurRed, blurGreen, blurBlue;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                blurRed = round(((double)(imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + 
                                          imageCopy[i + 1][j].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed) / 4));
                blurGreen = round(((double)(imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen +
                                            imageCopy[i + 1][j].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen) / 4));
                blurBlue = round(((double)(imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + 
                                           imageCopy[i + 1][j].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue) / 4));
                
                image[i][j].rgbtRed = blurRed;
                image[i][j].rgbtGreen = blurGreen;
                image[i][j].rgbtBlue = blurBlue;
            }
            else if (i == 0 && j == width - 1)
            {
                blurRed = round(((double)(imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed + 
                                          imageCopy[i + 1][j - 1].rgbtRed + imageCopy[i + 1][j].rgbtRed) / 4));
                blurGreen = round(((double)(imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen + 
                                            imageCopy[i + 1][j - 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen) / 4));
                blurBlue = round(((double)(imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue + 
                                           imageCopy[i + 1][j - 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue) / 4));
                
                image[i][j].rgbtRed = blurRed;
                image[i][j].rgbtGreen = blurGreen;
                image[i][j].rgbtBlue = blurBlue;
            }
            else if (i == height - 1 && j == 0)
            {
                blurRed = round(((double)(imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j + 1].rgbtRed + 
                                          imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed) / 4));
                blurGreen = round(((double)(imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j + 1].rgbtGreen + 
                                            imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen) / 4));
                blurBlue = round(((double)(imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j + 1].rgbtBlue + 
                                           imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue) / 4));
                
                image[i][j].rgbtRed = blurRed;
                image[i][j].rgbtGreen = blurGreen;
                image[i][j].rgbtBlue = blurBlue;
            }
            else if (i == height - 1 && j == width - 1)
            {
                blurRed = round(((double)(imageCopy[i - 1][j - 1].rgbtRed + imageCopy[i - 1][j].rgbtRed + 
                                          imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed) / 4));
                blurGreen = round(((double)(imageCopy[i - 1][j - 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + 
                                            imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen) / 4));
                blurBlue = round(((double)(imageCopy[i - 1][j - 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + 
                                           imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue) / 4));
                
                image[i][j].rgbtRed = blurRed;
                image[i][j].rgbtGreen = blurGreen;
                image[i][j].rgbtBlue = blurBlue;
            }
            else if (i == 0)
            {
                blurRed = round(((double)(imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + 
                                          imageCopy[i + 1][j - 1].rgbtRed + imageCopy[i + 1][j].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed) / 6));
                blurGreen = round(((double)(imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen + 
                                            imageCopy[i + 1][j - 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen) / 6));
                blurBlue = round(((double)(imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + 
                                           imageCopy[i + 1][j - 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue) / 6));
                
                image[i][j].rgbtRed = blurRed;
                image[i][j].rgbtGreen = blurGreen;
                image[i][j].rgbtBlue = blurBlue;
            }
            else if (i == height - 1)
            {
                blurRed = round(((double)(imageCopy[i - 1][j - 1].rgbtRed + imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j + 1].rgbtRed + 
                                          imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed) / 6));
                blurGreen = round(((double)(imageCopy[i - 1][j - 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j + 1].rgbtGreen + 
                                            imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen) / 6));
                blurBlue = round(((double)(imageCopy[i - 1][j - 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j + 1].rgbtBlue + 
                                           imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue) / 6));
                
                image[i][j].rgbtRed = blurRed;
                image[i][j].rgbtGreen = blurGreen;
                image[i][j].rgbtBlue = blurBlue;
            }
            else if (j == 0)
            {
                blurRed = round(((double)(imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j + 1].rgbtRed + 
                                          imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + 
                                          imageCopy[i + 1][j].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed) / 6));
                blurGreen = round(((double)(imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j + 1].rgbtGreen + 
                                            imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen + 
                                            imageCopy[i + 1][j].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen) / 6));
                blurBlue = round(((double)(imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j + 1].rgbtBlue + 
                                           imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + 
                                           imageCopy[i + 1][j].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue) / 6));
                
                image[i][j].rgbtRed = blurRed;
                image[i][j].rgbtGreen = blurGreen;
                image[i][j].rgbtBlue = blurBlue;
            }
            else if (j == width - 1)
            {
                blurRed = round(((double)(imageCopy[i - 1][j - 1].rgbtRed + imageCopy[i - 1][j].rgbtRed + 
                                          imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed + 
                                          imageCopy[i + 1][j - 1].rgbtRed + imageCopy[i + 1][j].rgbtRed) / 6));
                blurGreen = round(((double)(imageCopy[i - 1][j - 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + 
                                            imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen + 
                                            imageCopy[i + 1][j - 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen) / 6));
                blurBlue = round(((double)(imageCopy[i - 1][j - 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + 
                                           imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue + 
                                           imageCopy[i + 1][j - 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue) / 6));
                
                image[i][j].rgbtRed = blurRed;
                image[i][j].rgbtGreen = blurGreen;
                image[i][j].rgbtBlue = blurBlue;
            }
            else
            {
                blurRed = round(((double)(imageCopy[i - 1][j - 1].rgbtRed + imageCopy[i - 1][j].rgbtRed + imageCopy[i - 1][j + 1].rgbtRed + 
                                          imageCopy[i][j - 1].rgbtRed + imageCopy[i][j].rgbtRed + imageCopy[i][j + 1].rgbtRed + 
                                          imageCopy[i + 1][j - 1].rgbtRed + imageCopy[i + 1][j].rgbtRed + imageCopy[i + 1][j + 1].rgbtRed) / 9));
                blurGreen = round(((double)(imageCopy[i - 1][j - 1].rgbtGreen + imageCopy[i - 1][j].rgbtGreen + imageCopy[i - 1][j + 1].rgbtGreen + 
                                            imageCopy[i][j - 1].rgbtGreen + imageCopy[i][j].rgbtGreen + imageCopy[i][j + 1].rgbtGreen + 
                                            imageCopy[i + 1][j - 1].rgbtGreen + imageCopy[i + 1][j].rgbtGreen + imageCopy[i + 1][j + 1].rgbtGreen) / 9));
                blurBlue = round(((double)(imageCopy[i - 1][j - 1].rgbtBlue + imageCopy[i - 1][j].rgbtBlue + imageCopy[i - 1][j + 1].rgbtBlue + 
                                           imageCopy[i][j - 1].rgbtBlue + imageCopy[i][j].rgbtBlue + imageCopy[i][j + 1].rgbtBlue + 
                                           imageCopy[i + 1][j - 1].rgbtBlue + imageCopy[i + 1][j].rgbtBlue + imageCopy[i + 1][j + 1].rgbtBlue) / 9));
                
                image[i][j].rgbtRed = blurRed;
                image[i][j].rgbtGreen = blurGreen;
                image[i][j].rgbtBlue = blurBlue;
            }
        }
    }
    return;
}
