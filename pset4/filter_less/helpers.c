#include "helpers.h"
#include <math.h>

// typedef struct
// {
//     BYTE  rgbtBlue;
//     BYTE  rgbtGreen;
//     BYTE  rgbtRed;
// } __attribute__((__packed__))
// RGBTRIPLE;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
    	for (int b = 0; b < width; b++)
    	{
    		BYTE average = round((image[a][b].rgbtBlue + image[a][b].rgbtGreen + image[a][b].rgbtRed) / 3.0);
    		image[a][b].rgbtBlue = average;
    		image[a][b].rgbtGreen = average;
    		image[a][b].rgbtRed = average;
    		// TODO
    	}
    }
    return;
}

// Sepia (extra)
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
    	for (int b = 0; b < width; b++)
    	{
    		BYTE originalRed = image[a][b].rgbtRed;
    		BYTE originalGreen = image[a][b].rgbtGreen;
    		BYTE originalBlue = image[a][b].rgbtBlue;
    		if (round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue) < 256)
    		{
    		image[a][b].rgbtRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
    		}
    		else
    		{
    			image[a][b].rgbtRed = 255;
    		}
    		if (round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue) < 256)
    		{
    		image[a][b].rgbtGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
    		}
    		else
    		{
    			image[a][b].rgbtGreen = 255;
    		}
    		if (round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue) < 256)
    		{
    		image[a][b].rgbtBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);
    		}
    		else
    		{
    			image[a][b].rgbtBlue = 255;
    		}
    	}
    }
    return;
}

void swap(BYTE *a, BYTE *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	int half = floor(width / 2);
    for (int a = 0; a < height; a++)
    {
    	for (int b = 0; b < half; b++)
    	{
    		swap(&image[a][b].rgbtRed, &image[a][width-b-1].rgbtRed);
    		swap(&image[a][b].rgbtGreen, &image[a][width-b-1].rgbtGreen);
    		swap(&image[a][b].rgbtBlue, &image[a][width-b-1].rgbtBlue);
    	}
    }
    return;
}

typedef struct
{
    long int  rgbtBlue;
    long int  rgbtGreen;
    long int  rgbtRed;
} __attribute__((__packed__))
longRGBTRIPLE;

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imgcpy[height][width];
    for (int a = 0; a < height; a++)
    {
    	for (int b = 0; b < width; b++)
    	{
    		imgcpy[a][b].rgbtRed = image[a][b].rgbtRed;
    		imgcpy[a][b].rgbtBlue = image[a][b].rgbtBlue;
    		imgcpy[a][b].rgbtGreen = image[a][b].rgbtGreen;
    	}
    }
    
    for (int a = 0; a < height; a++)
    {
    	for (int b = 0; b < width; b++)
    	{
    		longRGBTRIPLE avg;
    		avg.rgbtRed = 0;
    		avg.rgbtGreen = 0;
    		avg.rgbtBlue = 0;
    		double count = 0;
    		
    		avg.rgbtRed += imgcpy[a][b].rgbtRed;
    		avg.rgbtGreen += imgcpy[a][b].rgbtGreen;
    		avg.rgbtBlue += imgcpy[a][b].rgbtBlue;
    		count++;
    		
    		if (a != 0)
    		{
    			avg.rgbtRed += imgcpy[a-1][b].rgbtRed;
    			avg.rgbtGreen += imgcpy[a-1][b].rgbtGreen;
    			avg.rgbtBlue += imgcpy[a-1][b].rgbtBlue;
    			count++;
    		}
    		if (a != height-1)
    		{
    			avg.rgbtRed += imgcpy[a+1][b].rgbtRed;
    			avg.rgbtGreen += imgcpy[a+1][b].rgbtGreen;
    			avg.rgbtBlue += imgcpy[a+1][b].rgbtBlue;
    			count++;
    		}
    		if (b != 0)
    		{
    			avg.rgbtRed += imgcpy[a][b-1].rgbtRed;
    			avg.rgbtGreen += imgcpy[a][b-1].rgbtGreen;
    			avg.rgbtBlue += imgcpy[a][b-1].rgbtBlue;
    			count++;
    		}
    		if (b != height-1)
    		{
    			avg.rgbtRed += imgcpy[a][b+1].rgbtRed;
    			avg.rgbtGreen += imgcpy[a][b+1].rgbtGreen;
    			avg.rgbtBlue += imgcpy[a][b+1].rgbtBlue;
    			count++;
    		}
    		if (a != 0 && b != 0)
    		{
    			avg.rgbtRed += imgcpy[a-1][b-1].rgbtRed;
    			avg.rgbtGreen += imgcpy[a-1][b-1].rgbtGreen;
    			avg.rgbtBlue += imgcpy[a-1][b-1].rgbtBlue;
    			count++;
    		}
    		if (a != height-1 && b != height-1)
    		{
    			avg.rgbtRed += imgcpy[a+1][b+1].rgbtRed;
    			avg.rgbtGreen += imgcpy[a+1][b+1].rgbtGreen;
    			avg.rgbtBlue += imgcpy[a+1][b+1].rgbtBlue;
    			count++;
    		}
    		if (a != 0 && b != height-1)
    		{
    			avg.rgbtRed += imgcpy[a-1][b+1].rgbtRed;
    			avg.rgbtGreen += imgcpy[a-1][b+1].rgbtGreen;
    			avg.rgbtBlue += imgcpy[a-1][b+1].rgbtBlue;
    			count++;
    		}
    		if (a != height-1 && b != 0)
    		{
    			avg.rgbtRed += imgcpy[a+1][b-1].rgbtRed;
    			avg.rgbtGreen += imgcpy[a+1][b-1].rgbtGreen;
    			avg.rgbtBlue += imgcpy[a+1][b-1].rgbtBlue;
    			count++;
    		}
    		avg.rgbtRed = round(avg.rgbtRed / count);
    		avg.rgbtGreen = round(avg.rgbtGreen / count);
    		avg.rgbtBlue = round(avg.rgbtBlue / count);
    		
    		image[a][b].rgbtRed = avg.rgbtRed;
    		image[a][b].rgbtBlue = avg.rgbtBlue;
    		image[a][b].rgbtGreen = avg.rgbtGreen;
    	}
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
    	for (int b = 0; b < width; b++)
    	{
    		// TODO
    	}
    }
    return;
}
