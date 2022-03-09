#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //below loop will scan every pixel in the image and after calculating average value, it will pass it to the needed pixel.
    for (int j = 0 ; j < width ; j++)
    {
        for (int i = 0; i < height ; i++)
        {
            float org_red = image[i][j].rgbtRed;
            float org_blue = image[i][j].rgbtBlue;
            float org_green = image[i][j].rgbtGreen;
            image[i][j].rgbtRed = round((org_red + org_blue + org_green) / 3);
            image[i][j].rgbtBlue = image[i][j].rgbtRed;
            image[i][j].rgbtGreen = image[i][j].rgbtBlue;
        }
    }
    return;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0 ; j < width ; j++)
    {
        for (int i = 0 ; i < height ; i++)
        {
            int org_red = image[i][j].rgbtRed;
            int org_blue = image[i][j].rgbtBlue;
            int org_green = image[i][j].rgbtGreen;
            int sepiaRed = round(.393 * org_red + .189 * org_blue + .769 * org_green);//formula is given in the problem.
            int sepiaBlue = round(.272 * org_red + .131 * org_blue + .534 * org_green);
            int sepiaGreen = round(.349 * org_red + .168 * org_blue + .686 * org_green);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            //above loop is used to get datas from temporary variables to original place.
        }
    }
    return;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mir_tempRed = 0;
    int mir_tempBlue = 0;
    int mir_tempGreen = 0;
    //temp variables for changing values of the variables.
    if ((width % 2) == 0)
    {
        for (int j = 0 ; j < height ; j++)
        {
            for (int i = 0 ; i < (width / 2) ; i++)
            {
                mir_tempRed = image[j][width - 1 - i].rgbtRed;
                mir_tempBlue = image[j][width - 1 - i].rgbtBlue;
                mir_tempGreen = image[j][width - 1 - i].rgbtGreen;
                image[j][width - 1 - i].rgbtRed = image[j][i].rgbtRed;
                image[j][width - 1 - i].rgbtBlue = image[j][i].rgbtBlue;
                image[j][width - 1 - i].rgbtGreen = image[j][i].rgbtGreen;
                image[j][i].rgbtRed = mir_tempRed;
                image[j][i].rgbtBlue = mir_tempBlue;
                image[j][i].rgbtGreen = mir_tempGreen;
                //image is divided in to 2 parts horizontally left side values will be taken to a temp variable. so changing values
                //will be possible.
            }
        }
    }
    else
    {
        for (int j = 0 ; j < height ; j++)
        {
            for (int i = 0 ; i < ((width  -  1) / 2) ; i++)
            {
                mir_tempRed = image[j][width - 1 - i].rgbtRed;
                mir_tempBlue = image[j][width - 1 - i].rgbtBlue;
                mir_tempGreen = image[j][width - 1 - i].rgbtGreen;
                image[j][width - 1 - i].rgbtRed = image[j][i].rgbtRed;
                image[j][width - 1 - i].rgbtBlue = image[j][i].rgbtBlue;
                image[j][width - 1 - i].rgbtGreen = image[j][i].rgbtGreen;
                image[j][i].rgbtRed = mir_tempRed;
                image[j][i].rgbtBlue = mir_tempBlue;
                image[j][i].rgbtGreen = mir_tempGreen;
            }
        }
    }
    return;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
//calculation with loops will be made in different parts of the image.
//4 corners, 4 edges-excluding corners, and the body(rest)
    float red;
    float left_upper_red;
    float upper_red;
    float right_upper_red;
    float right_red;
    float right_down_red;
    float down_red;
    float left_down_red;
    float left_red;
    float Blur_Red;
    float Blue;
    float left_upper_Blue;
    float upper_Blue;
    float right_upper_Blue;
    float right_Blue;
    float right_down_Blue;
    float down_Blue;
    float left_down_Blue;
    float left_Blue;
    float Blur_Blue;
    float Green;
    float left_upper_Green;
    float upper_Green;
    float right_upper_Green;
    float right_Green;
    float right_down_Green;
    float down_Green;
    float left_down_Green;
    float left_Green;
    float Blur_Green;
    float image_cpy_red[height][width];
    float image_cpy_blue[height][width];
    float image_cpy_green[height][width];
    //float type for division transactions
    //left_upper corner
    red = image[0][0].rgbtRed;
    right_red = image[0][1].rgbtRed;
    right_down_red = image[1][1].rgbtRed;
    down_red = image[1][0].rgbtRed;
    Blur_Red = round((red + right_red + right_down_red + down_red) / 4);
    image_cpy_red[0][0] = Blur_Red;
    Blue = image[0][0].rgbtBlue;
    right_Blue = image[0][1].rgbtBlue;
    right_down_Blue = image[1][1].rgbtBlue;
    down_Blue = image[1][0].rgbtBlue;
    Blur_Blue = round((Blue + right_Blue + right_down_Blue + down_Blue) / 4);
    image_cpy_blue[0][0] = Blur_Blue;
    Green = image[0][0].rgbtGreen;
    right_Green = image[0][1].rgbtGreen;
    right_down_Green = image[1][1].rgbtGreen;
    down_Green = image[1][0].rgbtGreen;
    Blur_Green = round((Green + right_Green + right_down_Green + down_Green) / 4);
    image_cpy_green[0][0] = Blur_Green;
    //right upper corner
    red = image[0][width - 1].rgbtRed;
    down_red = image[1][width - 1].rgbtRed;
    left_down_red = image[1][width - 1 - 1].rgbtRed;
    left_red = image[0][width - 1 - 1].rgbtRed;
    Blur_Red = round((red + down_red + left_down_red + left_red) / 4);
    image_cpy_red[0][width - 1] = Blur_Red;
    Blue = image[0][width - 1].rgbtBlue;
    down_Blue = image[1][width - 1].rgbtBlue;
    left_down_Blue = image[1][width - 1 - 1].rgbtBlue;
    left_Blue = image[0][width - 1 - 1].rgbtBlue;
    Blur_Blue = round((Blue + down_Blue + left_down_Blue + left_Blue) / 4);
    image_cpy_blue[0][width - 1] = Blur_Blue;
    Green = image[0][width - 1].rgbtGreen;
    down_Green = image[1][width - 1].rgbtGreen;
    left_down_Green = image[1][width - 1 - 1].rgbtGreen;
    left_Green = image[0][width - 1 - 1].rgbtGreen;
    Blur_Green = round((Green + down_Green + left_down_Green + left_Green) / 4);
    image_cpy_green[0][width - 1] = Blur_Green;
    //left down corner
    red = image[height - 1][0].rgbtRed;
    upper_red = image[height - 1 - 1][0].rgbtRed;
    right_upper_red = image[height - 1 - 1][1].rgbtRed;
    right_red = image[height - 1][1].rgbtRed;
    Blur_Red = round((red + upper_red + right_upper_red + right_red) / 4);
    image_cpy_red[height - 1][0] = Blur_Red;
    Blue = image[height - 1][0].rgbtBlue;
    upper_Blue = image[height - 1 - 1][0].rgbtBlue;
    right_upper_Blue = image[height - 1 - 1][1].rgbtBlue;
    right_Blue = image[height - 1][1].rgbtBlue;
    Blur_Blue = round((Blue + upper_Blue + right_upper_Blue + right_Blue) / 4);
    image_cpy_blue[height - 1][0] = Blur_Blue;
    Green = image[height - 1][0].rgbtGreen;
    upper_Green = image[height - 1 - 1][0].rgbtGreen;
    right_upper_Green = image[height - 1 - 1][1].rgbtGreen;
    right_Green = image[height - 1][1].rgbtGreen;
    Blur_Green = round((Green + upper_Green + right_upper_Green + right_Green) / 4);
    image_cpy_green[height - 1][0] = Blur_Green;
    //right down corner
    red = image[height - 1][width - 1].rgbtRed;
    left_upper_red = image[height - 1 - 1][width - 1 - 1].rgbtRed;
    upper_red = image[height - 1 - 1][width - 1].rgbtRed;
    left_red = image[height - 1][width - 1 - 1].rgbtRed;
    Blur_Red = round((red + left_upper_red + upper_red + left_red) / 4);
    image_cpy_red[height - 1][width - 1] = Blur_Red;
    Blue = image[height - 1][width - 1].rgbtBlue;
    left_upper_Blue = image[height - 1 - 1][width - 1 - 1].rgbtBlue;
    upper_Blue = image[height - 1 - 1][width - 1].rgbtBlue;
    left_Blue = image[height - 1][width - 1 - 1].rgbtBlue;
    Blur_Blue = round((Blue + left_upper_Blue + upper_Blue + left_Blue) / 4);
    image_cpy_blue[height - 1][width - 1] = Blur_Blue;
    Green = image[height - 1][width - 1].rgbtGreen;
    left_upper_Green = image[height - 1 - 1][width - 1 - 1].rgbtGreen;
    upper_Green = image[height - 1 - 1][width - 1].rgbtGreen;
    left_Green = image[height - 1][width - 1 - 1].rgbtGreen;
    Blur_Green = round((Green + left_upper_Green + upper_Green + left_Green) / 4);
    image_cpy_green[height - 1][width - 1] = Blur_Green;

    //left middle column, excluding two left corners.
    int w = 0;
    int h;
    for (h = 1 ; h < height  -  1 ; h++)
    {
        red = image[h][w].rgbtRed;
        upper_red = image[h - 1][w].rgbtRed;
        right_upper_red = image[h - 1][w + 1].rgbtRed;
        right_red = image[h][w + 1].rgbtRed;
        right_down_red = image[h + 1][w + 1].rgbtRed;
        down_red = image[h + 1][w].rgbtRed;
        Blur_Red = round((red + upper_red + right_upper_red + right_red + right_down_red + down_red) / 6);
        image_cpy_red[h][w] = Blur_Red;
        Blue = image[h][w].rgbtBlue;
        upper_Blue = image[h - 1][w].rgbtBlue;
        right_upper_Blue = image[h - 1][w + 1].rgbtBlue;
        right_Blue = image[h][w + 1].rgbtBlue;
        right_down_Blue = image[h + 1][w + 1].rgbtBlue;
        down_Blue = image[h + 1][w].rgbtBlue;
        Blur_Blue = round((Blue + upper_Blue + right_upper_Blue + right_Blue + right_down_Blue + down_Blue) / 6);
        image_cpy_blue[h][w] = Blur_Blue;
        Green = image[h][w].rgbtGreen;
        upper_Green = image[h - 1][w].rgbtGreen;
        right_upper_Green = image[h - 1][w + 1].rgbtGreen;
        right_Green = image[h][w + 1].rgbtGreen;
        right_down_Green = image[h + 1][w + 1].rgbtGreen;
        down_Green = image[h + 1][w].rgbtGreen;
        Blur_Green = round((Green + upper_Green + right_upper_Green + right_Green + right_down_Green + down_Green) / 6);
        image_cpy_green[h][w] = Blur_Green;
    }

    //right middle coumnn, excluding two rights corners.
    w = width;
    for (h = 1 ; h < height  -  1 ; h++)
    {
        red = image[h][w - 1].rgbtRed;
        left_upper_red = image[h - 1][w - 1 - 1].rgbtRed;
        upper_red = image[h - 1][w - 1].rgbtRed;
        down_red = image[h + 1][w - 1].rgbtRed;
        left_down_red = image[h + 1][w - 1 - 1].rgbtRed;
        left_red = image[h][w - 1 - 1].rgbtRed;
        Blur_Red = round((red + left_upper_red + upper_red + down_red + left_down_red + left_red) / 6);
        image_cpy_red[h][w - 1] = Blur_Red;
        Blue = image[h][w - 1].rgbtBlue;
        left_upper_Blue = image[h - 1][w - 1 - 1].rgbtBlue;
        upper_Blue = image[h - 1][w - 1].rgbtBlue;
        down_Blue = image[h + 1][w - 1].rgbtBlue;
        left_down_Blue = image[h + 1][w - 1 - 1].rgbtBlue;
        left_Blue = image[h][w - 1 - 1].rgbtBlue;
        Blur_Blue = round((Blue + left_upper_Blue + upper_Blue + down_Blue + left_down_Blue + left_Blue) / 6);
        image_cpy_blue[h][w - 1] = Blur_Blue;
        Green = image[h][w - 1].rgbtGreen;
        left_upper_Green = image[h - 1][w - 1 - 1].rgbtGreen;
        upper_Green = image[h - 1][w - 1].rgbtGreen;
        down_Green = image[h + 1][w - 1].rgbtGreen;
        left_down_Green = image[h + 1][w - 1 - 1].rgbtGreen;
        left_Green = image[h][w - 1 - 1].rgbtGreen;
        Blur_Green = round((Green + left_upper_Green + upper_Green + down_Green + left_down_Green + left_Green) / 6);
        image_cpy_green[h][w - 1] = Blur_Green;
    }

    //down middle rows, excluding two bottom corners.
    h = height;
    for (w = 1 ; w < width  -  1 ; w++)
    {
        red = image[h - 1][w].rgbtRed;
        left_upper_red = image[h - 1 - 1][w - 1].rgbtRed;
        upper_red = image[h - 1 - 1][w].rgbtRed;
        right_upper_red = image[h - 1 - 1][w + 1].rgbtRed;
        right_red = image[h - 1][w + 1].rgbtRed;
        left_red = image[h - 1][w - 1].rgbtRed;
        Blur_Red = round((red + left_upper_red + upper_red + right_upper_red + right_red + left_red) / 6);
        image_cpy_red[h - 1][w] = Blur_Red;
        Blue = image[h - 1][w].rgbtBlue;
        left_upper_Blue = image[h - 1 - 1][w - 1].rgbtBlue;
        upper_Blue = image[h - 1 - 1][w].rgbtBlue;
        right_upper_Blue = image[h - 1 - 1][w + 1].rgbtBlue;
        right_Blue = image[h - 1][w + 1].rgbtBlue;
        left_Blue = image[h - 1][w - 1].rgbtBlue;
        Blur_Blue = round((Blue + left_upper_Blue + upper_Blue + right_upper_Blue + right_Blue + left_Blue) / 6);
        image_cpy_blue[h - 1][w] = Blur_Blue;
        Green = image[h - 1][w].rgbtGreen;
        left_upper_Green = image[h - 1 - 1][w - 1].rgbtGreen;
        upper_Green = image[h - 1 - 1][w].rgbtGreen;
        right_upper_Green = image[h - 1 - 1][w + 1].rgbtGreen;
        right_Green = image[h - 1][w + 1].rgbtGreen;
        left_Green = image[h - 1][w - 1].rgbtGreen;
        Blur_Green = round((Green + left_upper_Green + upper_Green + right_upper_Green + right_Green + left_Green) / 6);
        image_cpy_green[h - 1][w] = Blur_Green;
    }

    //top middle row, excluding two top corners.

    h = 0;
    for (w = 1 ; w < width  -  1 ; w++)
    {
        red = image[h][w].rgbtRed;
        right_red = image[h][w + 1].rgbtRed;
        right_down_red = image[h + 1][w + 1].rgbtRed;
        down_red = image[h + 1][w].rgbtRed;
        left_down_red = image[h + 1][w - 1].rgbtRed;
        left_red = image[h][w - 1].rgbtRed;
        Blur_Red = round((red + right_red + right_down_red + down_red + left_down_red + left_red) / 6);
        image_cpy_red[h][w] = Blur_Red;
        Blue = image[h][w].rgbtBlue;
        right_Blue = image[h][w + 1].rgbtBlue;
        right_down_Blue = image[h + 1][w + 1].rgbtBlue;
        down_Blue = image[h + 1][w].rgbtBlue;
        left_down_Blue = image[h + 1][w - 1].rgbtBlue;
        left_Blue = image[h][w - 1].rgbtBlue;
        Blur_Blue = round((Blue + right_Blue + right_down_Blue + down_Blue + left_down_Blue + left_Blue) / 6);
        image_cpy_blue[h][w] = Blur_Blue;
        Green = image[h][w].rgbtGreen;
        right_Green = image[h][w + 1].rgbtGreen;
        right_down_Green = image[h + 1][w + 1].rgbtGreen;
        down_Green = image[h + 1][w].rgbtGreen;
        left_down_Green = image[h + 1][w - 1].rgbtGreen;
        left_Green = image[h][w - 1].rgbtGreen;
        Blur_Green = round((Green + right_Green + right_down_Green + down_Green + left_down_Green + left_Green) / 6);
        image_cpy_green[h][w] = Blur_Green;
    }

    //loop for the pixels in the middle of the image. calculation excludes corners and edges.

    for (h = 1 ; h < height  -  1 ; h++)
    {
        for (w = 1 ; w < width  -  1 ; w++)
        {
            red = image[h][w].rgbtRed;
            left_upper_red = image[h - 1][w - 1].rgbtRed;
            upper_red = image[h - 1][w].rgbtRed;
            right_upper_red = image[h - 1][w + 1].rgbtRed;
            right_red = image[h][w + 1].rgbtRed;
            right_down_red = image[h + 1][w + 1].rgbtRed;
            down_red = image[h + 1][w].rgbtRed;
            left_down_red = image[h + 1][w - 1].rgbtRed;
            left_red = image[h][w - 1].rgbtRed;
            Blur_Red = round((red + left_upper_red + upper_red + right_upper_red + right_red + right_down_red + down_red +
                              left_down_red + left_red) / 9);
            image_cpy_red[h][w] = Blur_Red;
            Blue = image[h][w].rgbtBlue;
            left_upper_Blue = image[h - 1][w - 1].rgbtBlue;
            upper_Blue = image[h - 1][w].rgbtBlue;
            right_upper_Blue = image[h - 1][w + 1].rgbtBlue;
            right_Blue = image[h][w + 1].rgbtBlue;
            right_down_Blue = image[h + 1][w + 1].rgbtBlue;
            down_Blue = image[h + 1][w].rgbtBlue;
            left_down_Blue = image[h + 1][w - 1].rgbtBlue;
            left_Blue = image[h][w - 1].rgbtBlue;
            Blur_Blue = round((Blue + left_upper_Blue + upper_Blue + right_upper_Blue + right_Blue + right_down_Blue + down_Blue +
                               left_down_Blue + left_Blue) / 9);
            image_cpy_blue[h][w] = Blur_Blue;
            Green = image[h][w].rgbtGreen;
            left_upper_Green = image[h - 1][w - 1].rgbtGreen;
            upper_Green = image[h - 1][w].rgbtGreen;
            right_upper_Green = image[h - 1][w + 1].rgbtGreen;
            right_Green = image[h][w + 1].rgbtGreen;
            right_down_Green = image[h + 1][w + 1].rgbtGreen;
            down_Green = image[h + 1][w].rgbtGreen;
            left_down_Green = image[h + 1][w - 1].rgbtGreen;
            left_Green = image[h][w - 1].rgbtGreen;
            Blur_Green = round((Green + left_upper_Green + upper_Green + right_upper_Green + right_Green + right_down_Green + down_Green +
                                left_down_Green + left_Green) / 9);
            image_cpy_green[h][w] = Blur_Green;
        }
    }

    for (h = 0 ; h < height ; h++)
    {
        for (w = 0; w < width ; w++)
        {
            image[h][w].rgbtRed = image_cpy_red[h][w];
            image[h][w].rgbtBlue = image_cpy_blue[h][w];
            image[h][w].rgbtGreen = image_cpy_green[h][w];
            //The last loop is for taking values from temporary variables. This made programe to calculate original values
        }
    }
    return;
}
