#include "helpers.h"
#include <math.h>

void swap(BYTE *a, BYTE *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

typedef struct
{
    long int  rgbtBlue;
    long int  rgbtGreen;
    long int  rgbtRed;
} __attribute__((__packed__))
longRGBTRIPLE;

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

// RGBTRIPLE gofx (int a, int b, RGBTRIPLE imgcpy[a + 1][b + 1])
// {
//     RGBTRIPLE target;
//     target.rgbtRed = imgcpy[a - 1][b + 1].rgbtRed + imgcpy[a][b + 1].rgbtRed + imgcpy[a + 1][b - 1].rgbtRed - imgcpy[a - 1][b - 1].rgbtRed - imgcpy[a][b - 1].rgbtRed - imgcpy[a + 1][b - 1].rgbtRed;
//     target.rgbtGreen = imgcpy[a - 1][b + 1].rgbtGreen + imgcpy[a][b + 1].rgbtGreen + imgcpy[a + 1][b + 1].rgbtGreen - imgcpy[a - 1][b - 1].rgbtGreen - imgcpy[a][b - 1].rgbtGreen - imgcpy[a + 1][b - 1].rgbtGreen;
//     target.rgbtBlue = imgcpy[a - 1][b + 1].rgbtBlue + imgcpy[a][b + 1].rgbtBlue + imgcpy[a + 1][b + 1].rgbtBlue - imgcpy[a - 1][b - 1].rgbtBlue - imgcpy[a][b - 1].rgbtBlue - imgcpy[a + 1][b - 1].rgbtBlue;
//     return target;
// }

// RGBTRIPLE gofy (int a, int b, RGBTRIPLE imgcpy[a + 1][b + 1])
// {
//     RGBTRIPLE target;
//     target.rgbtRed = imgcpy[a + 1][b - 1].rgbtRed + imgcpy[a + 1][b].rgbtRed + imgcpy[a + 1][b + 1].rgbtRed - imgcpy[a - 1][b - 1].rgbtRed - imgcpy[a - 1][b].rgbtRed - imgcpy[a - 1][b + 1].rgbtRed;
//     target.rgbtGreen = imgcpy[a + 1][b - 1].rgbtGreen + imgcpy[a + 1][b].rgbtGreen + imgcpy[a + 1][b + 1].rgbtGreen - imgcpy[a - 1][b - 1].rgbtGreen - imgcpy[a - 1][b].rgbtGreen - imgcpy[a - 1][b + 1].rgbtGreen;
//     target.rgbtBlue = imgcpy[a + 1][b - 1].rgbtBlue + imgcpy[a + 1][b].rgbtBlue + imgcpy[a + 1][b + 1].rgbtBlue - imgcpy[a - 1][b - 1].rgbtBlue - imgcpy[a - 1][b].rgbtBlue - imgcpy[a - 1][b + 1].rgbtBlue;
//     return target;
// }

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imgcpy[height][width];
    for (int a = 0; a < height; a++) {
    	for (int b = 0; b < width; b++) {
    		imgcpy[a][b].rgbtRed = image[a][b].rgbtRed;
    		imgcpy[a][b].rgbtBlue = image[a][b].rgbtBlue;
    		imgcpy[a][b].rgbtGreen = image[a][b].rgbtGreen;
    	}
    }
    
    for (int a = 0; a < height; a++) {
    	for (int b = 0; b < width; b++) {
    		RGBTRIPLE gx, gy;
            gx.rgbtRed = 0;
            gx.rgbtGreen = 0;
            gx.rgbtBlue = 0;
            gy.rgbtRed = 0;
            gy.rgbtGreen = 0;
            gy.rgbtBlue = 0;
    		if (a != 0)
    		{
    			gx.rgbtRed += imgcpy[a-1][b].rgbtRed * 0;
    			gx.rgbtGreen += imgcpy[a-1][b].rgbtGreen * 0;
    			gx.rgbtBlue += imgcpy[a-1][b].rgbtBlue * 0;
                gy.rgbtRed += imgcpy[a-1][b].rgbtRed * -2;
    			gy.rgbtGreen += imgcpy[a-1][b].rgbtGreen * -2;
    			gy.rgbtBlue += imgcpy[a-1][b].rgbtBlue * -2;
    		}
    		if (a != height-1)
    		{
    			gx.rgbtRed += imgcpy[a+1][b].rgbtRed * 0;
    			gx.rgbtGreen += imgcpy[a+1][b].rgbtGreen * 0;
    			gx.rgbtBlue += imgcpy[a+1][b].rgbtBlue * 0;
                gy.rgbtRed += imgcpy[a+1][b].rgbtRed * 2;
    			gy.rgbtGreen += imgcpy[a+1][b].rgbtGreen * 2;
    			gy.rgbtBlue += imgcpy[a+1][b].rgbtBlue * 2;
    		}
    		if (b != 0)
    		{
    			gx.rgbtRed += imgcpy[a][b-1].rgbtRed * -2;
    			gx.rgbtGreen += imgcpy[a][b-1].rgbtGreen * -2;
    			gx.rgbtBlue += imgcpy[a][b-1].rgbtBlue * -2;
                gy.rgbtRed += imgcpy[a][b-1].rgbtRed * 0;
    			gy.rgbtGreen += imgcpy[a][b-1].rgbtGreen * 0;
    			gy.rgbtBlue += imgcpy[a][b-1].rgbtBlue * 0;
    		}
    		if (b != height-1)
    		{
    			gx.rgbtRed += imgcpy[a][b+1].rgbtRed * 2;
    			gx.rgbtGreen += imgcpy[a][b+1].rgbtGreen * 2;
    			gx.rgbtBlue += imgcpy[a][b+1].rgbtBlue * 2;
                gy.rgbtRed += imgcpy[a][b+1].rgbtRed * 0;
    			gy.rgbtGreen += imgcpy[a][b+1].rgbtGreen * 0;
    			gy.rgbtBlue += imgcpy[a][b+1].rgbtBlue * 0;
    		}
    		if (a != 0 && b != 0)
    		{
    			gx.rgbtRed += imgcpy[a-1][b-1].rgbtRed * -1;
    			gx.rgbtGreen += imgcpy[a-1][b-1].rgbtGreen * -1;
    			gx.rgbtBlue += imgcpy[a-1][b-1].rgbtBlue * -1;
                gy.rgbtRed += imgcpy[a-1][b-1].rgbtRed * -1;
    			gy.rgbtGreen += imgcpy[a-1][b-1].rgbtGreen * -1;
    			gy.rgbtBlue += imgcpy[a-1][b-1].rgbtBlue * -1;
    		}
    		if (a != height-1 && b != height-1)
    		{
    			gx.rgbtRed += imgcpy[a+1][b+1].rgbtRed * 1;
    			gx.rgbtGreen += imgcpy[a+1][b+1].rgbtGreen * 1;
    			gx.rgbtBlue += imgcpy[a+1][b+1].rgbtBlue * 1;
                gy.rgbtRed += imgcpy[a+1][b+1].rgbtRed * 1;
    			gy.rgbtGreen += imgcpy[a+1][b+1].rgbtGreen * 1;
    			gy.rgbtBlue += imgcpy[a+1][b+1].rgbtBlue * 1;
    		}
    		if (a != 0 && b != height-1)
    		{
    			gx.rgbtRed += imgcpy[a-1][b+1].rgbtRed * -1;
    			gx.rgbtGreen += imgcpy[a-1][b+1].rgbtGreen * -1;
    			gx.rgbtBlue += imgcpy[a-1][b+1].rgbtBlue * -1;
                gy.rgbtRed += imgcpy[a-1][b+1].rgbtRed * 1;
    			gy.rgbtGreen += imgcpy[a-1][b+1].rgbtGreen * 1;
    			gy.rgbtBlue += imgcpy[a-1][b+1].rgbtBlue * 1;
    		}
    		if (a != height-1 && b != 0)
    		{
    			gx.rgbtRed += imgcpy[a+1][b-1].rgbtRed * 1;
    			gx.rgbtGreen += imgcpy[a+1][b-1].rgbtGreen * 1;
    			gx.rgbtBlue += imgcpy[a+1][b-1].rgbtBlue * 1;
                gy.rgbtRed += imgcpy[a+1][b-1].rgbtRed * -1;
    			gy.rgbtGreen += imgcpy[a+1][b-1].rgbtGreen * -1;
    			gy.rgbtBlue += imgcpy[a+1][b-1].rgbtBlue * -1;
    		}
    		RGBTRIPLE combined;
			combined.rgbtRed = round(sqrt(pow(gx.rgbtRed, 2) + pow(gy.rgbtRed, 2)));
			combined.rgbtGreen = round(sqrt(pow(gx.rgbtGreen, 2) + pow(gy.rgbtGreen, 2)));
			combined.rgbtBlue = round(sqrt(pow(gx.rgbtBlue, 2) + pow(gy.rgbtBlue, 2)));
    		
    		image[a][b].rgbtRed = combined.rgbtRed;
    		image[a][b].rgbtBlue = combined.rgbtBlue;
    		image[a][b].rgbtGreen = combined.rgbtGreen;
    	}
    }
    return;
}
