// To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
// To run (linux/mac): ./main.out example.bmp example_inv.bmp

// To compile (win): gcc main.c cbmp.c -o main.exe -std=c99 -Wl,--stack,16777216
// To run (win): main.exe example.bmp example_inv.bmp

#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"
#include "stack.h"
#include <unistd.h>

// #include<windows.h>

// Function to invert pixels of an image (negative)
void invert(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS])
{
  for (int x = 0; x < BMP_WIDTH; x++)
  {
    for (int y = 0; y < BMP_HEIGTH; y++)
    {
      for (int c = 0; c < BMP_CHANNELS; c++)
      {
        output_image[x][y][c] = 255 - input_image[x][y][c];
      }
    }
  }
}
// Declaring the array to store the image (unsigned char = unsigned 8 bit)

unsigned char input_image_real[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char output_image_real[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char for_eroding[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char for_opt[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

void celldetection(unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int cellpositions[BMP_WIDTH][BMP_HEIGTH]);
void cellDetectionOpt(unsigned char input[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int *n);
void findGridSize(unsigned char input[BMP_HEIGTH][BMP_WIDTH][BMP_CHANNELS]);
void erodeBox(unsigned char input[BMP_HEIGTH][BMP_WIDTH][BMP_CHANNELS]);
void convertToGrey(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS])
{

  int thfb = 90;
  unsigned char r, g, b;
  unsigned char grey_value;

  for (int x = 0; x < BMP_WIDTH; x++)
  { // go through each x then y
    for (int y = 0; y < BMP_HEIGTH; y++)
    {
      r = input_image[x][y][0]; // read each coulor value
      g = input_image[x][y][1];
      b = input_image[x][y][2];

      grey_value = (r + g + b) / 3; // grey value
      for (int color = 0; color < BMP_CHANNELS; color++)
      {
        if (grey_value <= thfb)
          output_image[x][y][color] = 0;
        else
          output_image[x][y][color] = 255;
      }
    }
  }
}
void setBlack(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS])
{
  for (int x = 0; x < BMP_WIDTH; x++)
  { // go through each x then y
    for (int y = 0; y < BMP_HEIGTH; y++)
    {
      input_image[x][y][0] = 0;
    }
  }
}

vector cellDetected[(BMP_HEIGTH * 4) - 4];
vector cellCenters[((1 / 2) * BMP_HEIGTH) * ((1 / 2) * BMP_HEIGTH)];
Stack stack;
short int ite = 0;
int a = -1;
int *n = &a;
void erosionOtp(unsigned char input[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS])
{

  printf("%d \n", ite);
  for (int x = ite; x < BMP_WIDTH - ite; x++)
  {
    if (input[x][ite][0] == 255)
    {
      (*n)++;
      cellDetected[*n].x = x;
      cellDetected[*n].y = ite;
    }
  }
  for (int y = ite + 1; y < BMP_HEIGTH - ite; y++)
  {
    if (input[BMP_WIDTH - 1 - ite][y][0] == 255)
     {
      (*n)++;
      cellDetected[*n].x = BMP_WIDTH - 1 - ite;
      cellDetected[*n].y = y;
    }
  }
  for (int x = (BMP_WIDTH - 2) - ite; x >= 0 + ite; x--)
  {
    if (input[x][BMP_HEIGTH - 1 - ite][0] == 255)
    {
      (*n)++;
      cellDetected[*n].x = x;
      cellDetected[*n].y = BMP_HEIGTH - 1 - ite;
    }
  }
  for (int y = (BMP_HEIGTH - 2) - ite; y >= 1 + ite; y--)
  {
    if (input[ite][y][0] == 255)
    {
      (*n)++;
      cellDetected[*n].x = ite;
      cellDetected[*n].y = y;
    }
  }
  ite++;
  if (ite < BMP_WIDTH / 2 + 1)
  {
    cellDetectionOpt(input, n);
  }
}
 
vector temp;
short int ds[4];
void cellDetectionOpt(unsigned char input[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int *k)
{
  if (*k > 0)
  {
    for (; *k > 0; (*k)--)
    {
      if (input[cellDetected[*k].x][cellDetected[*k].y][0] == 255)
      {
        temp.x = cellDetected[*k].x;
        temp.y = cellDetected[*k].y;
        findGridSize(input);
        erodeBox(input);
      }
    }
    //write_bitmap(input, "example_inv.bmp");
  }
  erosionOtp(input);
}
char done = 1;
char *tempDone = &done;
short int minx, maxx, miny, maxy;
void findGridSize(unsigned char input[BMP_HEIGTH][BMP_WIDTH][BMP_CHANNELS])
{
  *tempDone = 1;
  minx, maxx = temp.x;
  miny, maxy = temp.y;
  while (*tempDone)
  {
    if (input[temp.x - 1][temp.y][0] == 255 && temp.x > 0 && for_opt[temp.x - 1][temp.y][0] != 255)
    {
      push(&stack, temp.x);
      push(&stack, temp.y);
      for_opt[temp.x - 1][temp.y][0] = 255;
      temp.x--;
      if (temp.x < minx)
      {
        minx = temp.x;
      }
    }
    else if (input[temp.x][temp.y - 1][0] == 255 && temp.y > 0 && for_opt[temp.x][temp.y - 1][0] != 255)
    {
      push(&stack, temp.x);
      push(&stack, temp.y);
      for_opt[temp.x][temp.y - 1][0] = 255;
      temp.y--;
      if (temp.y < miny)
      {
        miny = temp.y;
      }
    }
    else if (input[temp.x + 1][temp.y][0] == 255 && temp.x < BMP_WIDTH - 1 && for_opt[temp.x + 1][temp.y][0] != 255)
    {
      push(&stack, temp.x);
      push(&stack, temp.y);
      for_opt[temp.x + 1][temp.y][0] = 255;
      temp.x++;
      if (temp.x > maxx)
      {
        maxx = temp.x;
      }
    }
    else if (input[temp.x][temp.y + 1][0] == 255 && temp.y < BMP_HEIGTH - 1 && for_opt[temp.x][temp.y + 1][0] != 255)
    {
      push(&stack, temp.x);
      push(&stack, temp.y);
      for_opt[temp.x][temp.y + 1][0] = 255;
      temp.y++;
      if (temp.y > maxy)
      {
        maxy = temp.y;
      }
    }
    else if (!isEmpty(&stack))
    {
      temp.y = pop(&stack);
      temp.x = pop(&stack);
    }
    else
    {
      *tempDone = 0;
      ds[0] = minx;
      ds[1] = maxx;
      ds[2] = miny;
      ds[3] = maxy;
    }
  }
}
void erodeBox(unsigned char input[BMP_HEIGTH][BMP_WIDTH][BMP_CHANNELS])
{
  for (int mix = ds[0]; mix <= ds[1]; mix++)
  {
    for (int miy = ds[2]; miy <= ds[3]; miy++)
    {
      if (for_opt[mix][miy][0] == 255)
      {
        for (int i = -1; i <= 1; i++)
        { // look at 3x3 neighburs
          for (int j = -1; j <= 1; j++)
          {
            if (mix + i >= ds[1] || mix + i < ds[0] || miy + j >= ds[3] || miy + j < ds[2])
            {
              continue;
            }
            else if (for_opt[mix + i][miy + j][0] != 255 && i != 0 && j != 0)
            {
              for_opt[mix][miy][0] = 0;
              input[mix][miy][0] = 0;
              input[mix][miy][1] = 0;
              input[mix][miy][2] = 0;
            }
          }
        }
      }
    }
  }
}
void erode(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int cellpositions[BMP_WIDTH][BMP_HEIGTH])
{
  for (int x = 0; x < BMP_WIDTH; x++)
  {
    for (int y = 0; y < BMP_HEIGTH; y++)
    {
      if (input_image[x][y][0] == 255)
      {
        output_image[x][y][0] = 255;
        output_image[x][y][1] = 255;
        output_image[x][y][2] = 255;
        for (int i = -1; i <= 1; i++)
        { // look at 3x3 neighburs
          for (int j = -1; j <= 1; j++)
          {
            if (x + i >= BMP_HEIGTH || x + i < 0 || y + j >= BMP_HEIGTH || y + j < 0)
            {
              continue;
            }
            else if (input_image[x + i][y + j][0] == 0 && i != 0 && j != 0)
            {
              output_image[x][y][0] = 0;
              output_image[x][y][1] = 0;
              output_image[x][y][2] = 0;
              // printf("x: %d, y: %d \n", x, y);
            }
          }
        }
      }
      else
      {
        output_image[x][y][0] = 0;
        output_image[x][y][1] = 0;
        output_image[x][y][2] = 0;
      }
    }
  }
  celldetection(output_image, cellpositions);
}
int countCell;
int count;
void celldetection(unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int cellpositions[BMP_WIDTH][BMP_HEIGTH])
{
  int count = 0;
  for (int x = 4; x < BMP_WIDTH - 4; x++)
  { // Starts at 7, ends at WIDTH-7
    for (int y = 4; y < BMP_HEIGTH - 4; y++)
    {

      // check around (14x14) capturing area
      int exclusion_frame_black = 1;
      for (int i = -4; i <= 4; i++)
      {
        for (int j = -4; j <= 4; j++)
        {
          // Exclusion frame outside capturing area (12x12)
          if ((i == -4 || i == 4 || j == -4 || j == 4) && output_image[x + i][y + j][0] != 0)
          {
            exclusion_frame_black = 0;
            break;
          }
        }
        if (!exclusion_frame_black)
          break;
      }

      // Om exklusionsramen inte är helt svart, hoppa över
      if (!exclusion_frame_black)
        continue;

      // Kontrollera capturing area (12x12) för att hitta vita pixlar
      int white_pixel_found = 0;
      for (int i = -3; i <= 3; i++)
      {
        for (int j = -3; j <= 3; j++)
        {
          for (int k = 0; k < BMP_CHANNELS; k++)
          {
            if (output_image[x + i][y + j][k] == 255)
            {

              white_pixel_found = 1;
              cellpositions[x + i][y + i] = 1;
            }
          }
        }
        if (white_pixel_found)
          count++;
        break;
      }
      // one white, frame black
      if (white_pixel_found)
      {
        // try to avoid double count
        for (int i = -3; i <= 3; i++)
        {
          for (int j = -3; j <= 3; j++)
          {
            for (int k = 0; k < BMP_CHANNELS; k++)
            {
              output_image[x + i][y + j][k] = 0; // capturing area -> black
            }
          }
        }
      }
    }
  }
  printf("Cells found during erode: %d\n", count);
}

void drawredcrosses(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
                    int cellpositions[BMP_WIDTH][BMP_HEIGTH])
{
  for (int i = 0; i < BMP_WIDTH; i++)
  {
    for (int j = 0; j < BMP_HEIGTH; j++)
    {
      if (cellpositions[i][j] == 1)
      {
        if (i < BMP_WIDTH - 3 && i > 3 && j < BMP_HEIGTH - 3 && j > 3)
        {
          for (int m = -3; m < 3; m++)
          {
            input_image[i + m + 5][j + 5][0] = 255;
            input_image[i + m + 5][j + 5][1] = 0;
            input_image[i + m + 5][j + 5][2] = 0;
            input_image[i + 5][j + m + 5][0] = 255;
            input_image[i + 5][j + m + 5][1] = 0;
            input_image[i + 5][j + m + 5][2] = 0;
          }
        }
      }
    }
  }
}

int main(int argc, char **argv)
{
  // argc counts how may arguments are passed
  // argv[0] is a string with the name of the program
  // argv[1] is the first command line argument (input image)
  // argv[2] is the second command line argument (output image)

  // Checking that 2 arguments are passed
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <output file path> <output file path>\n", argv[0]);
    exit(1);
  }
  printf("Example program - 02132 - A1\n");

  initialize(&stack);

  // Load image from file
  read_bitmap(argv[1], input_image_real);
  read_bitmap(argv[1], for_eroding);
  read_bitmap(argv[1], for_opt);

  convertToGrey(input_image_real, output_image_real);
  setBlack(for_opt);
  int iterations = 15;

  int cellpositions[BMP_WIDTH][BMP_HEIGTH];
  /*
   for (int i = 0; i < iterations; i++)
   {
     if (i % 2 == 0)
     {
       erode(output_image_real, for_eroding, cellpositions);
       write_bitmap(for_eroding, argv[2]);
     }
     else
     {
       erode(for_eroding, output_image_real, cellpositions);
       write_bitmap(output_image_real, argv[2]);
     }
     sleep(1); //  for linux
     // Sleep(10); // for windows
   }
 */
  erosionOtp(output_image_real);
  write_bitmap(output_image_real, argv[2]);
  /*
   drawredcrosses(input_image_real, cellpositions);
   write_bitmap(input_image_real, argv[2]);
 */
  printf("Done!\n");
  return 0;
};