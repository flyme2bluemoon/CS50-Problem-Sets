#include "bmp.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

// RGBTRIPLE gx (int a, int b, RGBTRIPLE imgcpy[a + 1][b + 1]);

// RGBTRIPLE gy (int a, int b, RGBTRIPLE imgcpy[a + 1][b + 1]);