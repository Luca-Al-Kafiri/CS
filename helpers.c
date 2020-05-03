#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int x = 0; x < width; x++)
        {
            //calculating the average of RGB to get a matching grey color
            int avrg = round((image[i][x].rgbtBlue + image[i][x].rgbtGreen + image[i][x].rgbtRed) / 3.0);
            image[i][x].rgbtRed = avrg;
            image[i][x].rgbtGreen = avrg;
            image[i][x].rgbtBlue = avrg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // temporary copy of the image
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        // iterate through half of the pixels only
        for (int x = 0; x < width / 2; x++)
        {
            tmp = image[i][x];
            image[i][x] = image[i][width - (x + 1)];
            image[i][width - (x + 1)] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int x = 0; x < width; x++)
        {
            int r = 0;
            int g = 0;
            int b = 0;
            int red = 0;
            int green = 0;
            int blue = 0;
            float pix = 0;
            for (int z = -1; z < 2; z++)
            {
                for (int w = -1; w < 2; w++)
                {
                    if (i + z > -1 && i + z < height && x + w > -1 && x + w < width)
                    {
                        r += image[i + z][x + w].rgbtRed;
                        g += image[i + z][x + w].rgbtGreen;
                        b += image[i + z][x + w].rgbtBlue;
                        pix++;
                    }
                }
            }
            red = round(r / pix);
            green = round(g / pix);
            blue = round(b / pix);
            tmp[i][x].rgbtRed = red;
            tmp[i][x].rgbtGreen = green;
            tmp[i][x].rgbtBlue = blue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int x = 0; x < width; x++)
        {
            image[i][x] = tmp[i][x];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int x = 0; x < width; x++)
        {
            int Gxr = 0;
            int Gxg = 0;
            int Gxb = 0;
            int Gyr = 0;
            int Gyg = 0;
            int Gyb = 0;
            int red = 0;
            int green = 0;
            int blue = 0;
            double sumr = 0;
            double sumg = 0;
            double sumb = 0;
            for (int z = -1; z < 2; z++)
            {
                for (int w = -1; w < 2; w++)
                {
                    if (i + z > -1 && i + z < height && x + w > -1 && x + w < width)
                    {
                        if (((i + z) == (i - 1) && ((x + w) == (x - 1))) || ((i + z) == (i + 1) && ((x + w) == (x - 1))))
                        {
                            Gxr = Gxr + (image[i + z][x + w].rgbtRed * -1);
                            Gxg = Gxg + (image[i + z][x + w].rgbtGreen * -1);
                            Gxb = Gxb + (image[i + z][x + w].rgbtBlue * -1);
                        }
                        if (((i + z) == (i - 1) && ((x + w) == (x + 1))) || ((i + z) == (i + 1) && ((x + w) == (x + 1))))
                        {
                            Gxr = Gxr + image[i + z][x + w].rgbtRed;
                            Gxg = Gxg + image[i + z][x + w].rgbtGreen;
                            Gxb = Gxb + image[i + z][x + w].rgbtBlue;
                        }
                        if ((i + z) == i && ((x + w) == (x - 1)))
                        {
                            Gxr = Gxr + (image[i + z][x + w].rgbtRed * -2);
                            Gxg = Gxg + (image[i + z][x + w].rgbtGreen * -2);
                            Gxb = Gxb + (image[i + z][x + w].rgbtBlue * -2);
                        }
                        if ((i + z) == i && ((x + w) == (x + 1)))
                        {
                            Gxr = Gxr + (image[i + z][x + w].rgbtRed * 2);
                            Gxg = Gxg + (image[i + z][x + w].rgbtGreen * 2);
                            Gxb = Gxb + (image[i + z][x + w].rgbtBlue * 2);
                        }
                        if (((i + z) == (i - 1) && ((x + w) == (x - 1))) || ((i + z) == (i - 1) && ((x + w) == (x + 1))))
                        {
                            Gyr = Gyr + (image[i + z][x + w].rgbtRed * -1);
                            Gyg = Gyg + (image[i + z][x + w].rgbtGreen * -1);
                            Gyb = Gyb + (image[i + z][x + w].rgbtBlue * -1);
                        }
                        if (((i + z) == (i + 1) && ((x + w) == (x - 1))) || ((i + z) == (i + 1) && ((x + w) == (x + 1))))
                        {
                            Gyr = Gyr + image[i + z][x + w].rgbtRed;
                            Gyg = Gyg + image[i + z][x + w].rgbtGreen;
                            Gyb = Gyb + image[i + z][x + w].rgbtBlue;
                        }
                        if ((i + z) == (i - 1) && ((x + w) == x))
                        {
                            Gyr = Gyr + (image[i + z][x + w].rgbtRed * -2);
                            Gyg = Gyg + (image[i + z][x + w].rgbtGreen * -2);
                            Gyb = Gyb + (image[i + z][x + w].rgbtBlue * -2);
                        }
                        if ((i + z) == (i + 1) && ((x + w) == x))
                        {
                            Gyr = Gyr + (image[i + z][x + w].rgbtRed * 2);
                            Gyg = Gyg + (image[i + z][x + w].rgbtGreen * 2);
                            Gyb = Gyb + (image[i + z][x + w].rgbtBlue * 2);
                        }

                    }
                }
            }
            sumr = sqrt(pow(Gxr, 2) + pow(Gyr, 2));
            red = round(sumr);
            if (red > 255)
            {
                red = 255;
            }
            sumg = sqrt(pow(Gxg, 2) + pow(Gyg, 2));
            green = round(sumg);
            if (green > 255)
            {
                green = 255;
            }
            sumb = sqrt(pow(Gxb, 2) + pow(Gyb, 2));
            blue = round(sumb);
            if (blue > 255)
            {
                blue = 255;
            }
            tmp[i][x].rgbtRed = red;
            tmp[i][x].rgbtGreen = green;
            tmp[i][x].rgbtBlue = blue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int x = 0; x < width; x++)
        {
            image[i][x] = tmp[i][x];
        }
    }
    return;
}
