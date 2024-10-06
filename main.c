//To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
//To run (linux/mac): ./main.out example.bmp example_inv.bmp

//To compile (win): gcc cbmp.c main.c -o main.exe -std=c99
//To run (win): main.exe example.bmp example_inv.bmp

#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"
#include <unistd.h>

  //Declaring the array to store the image (unsigned char = unsigned 8 bit)
  unsigned char input_image_real[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
  unsigned char output_image_real[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
  unsigned char for_eroding[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

  void convertToGrey(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]){

    int thfb = 90;  // Sätt konstantvärden utanför loopen
    unsigned char r, g, b;  // Deklarera färgvariablerna utanför loopen
    unsigned char grey_value; 

      for (int x = 0; x < BMP_WIDTH; x++) { //go through each x then y
          for (int y = 0; y < BMP_HEIGTH; y++) {
            r = input_image[x][y][0]; //read each coulor value
            g = input_image[x][y][1];
            b = input_image[x][y][2];

            grey_value = (r + g + b) / 3; //calculate grey value
            for(int color=0; color<BMP_CHANNELS; color++){
              if (grey_value <= thfb) 
                output_image[x][y][color] = 0; //svart
              else
                output_image[x][y][color] = 255; //vit
            }
      }
    }
  }

void celldetection(unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int cellpositions[BMP_WIDTH][BMP_HEIGTH]);

void erode(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int cellpositions[BMP_WIDTH][BMP_HEIGTH]){
  for (int x = 1; x < BMP_WIDTH - 1; x++){
    for (int y = 1; y < BMP_HEIGTH - 1; y++) {
      if(input_image[x][y][0] == 255) {
        output_image[x][y][0] = 255;
        output_image[x][y][1] = 255;
        output_image[x][y][2] = 255;
        for (int i = -1; i <= 1; i++) { //look at 3x3 neighburs
            for (int j = -1; j <= 1; j++) {
                if(input_image[x+i][y+j][0] == 0 && i != 0 && j != 0 ) {
                  output_image[x][y][0] = 0;
                  output_image[x][y][1] = 0;
                  output_image[x][y][2] = 0;
                  //printf("x: %d, y: %d \n", x, y);
                }
            }
        }
      } else {
        output_image[x][y][0] = 0;
        output_image[x][y][1] = 0;
        output_image[x][y][2] = 0;
      }
    }
  }
      celldetection(output_image, cellpositions);
  }
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

short int cellcounter;

void drawredcrosses(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], 
int cellpositions[BMP_WIDTH][BMP_HEIGTH]){
  for (int i = 0; i < BMP_WIDTH; i++){
    for (int j = 0; j < BMP_HEIGTH; j++){
      if (cellpositions[i][j] == 1){
        cellcounter++;
        if (i < BMP_WIDTH - 9 && i > 9 && j < BMP_HEIGTH - 9 && j > 9){
          for (int m = -7; m < 7; m++) {
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

//Main function
int main(int argc, char** argv)
{
  //argc counts how may arguments are passed
  //argv[0] is a string with the name of the program
  //argv[1] is the first command line argument (input image)
  //argv[2] is the second command line argument (output image)

  //Checking that 2 arguments are passed
  if (argc != 3)
  {
      fprintf(stderr, "Usage: %s <output file path> <output file path>\n", argv[0]);
      exit(1);
  }

  printf("Example program - 02132 - A1\n");

  //Load image from file
  read_bitmap(argv[1], input_image_real);
  read_bitmap(argv[1], for_eroding);

  convertToGrey(input_image_real, output_image_real);
  int iterations = 15;

  int cellpositions[BMP_WIDTH][BMP_HEIGTH];

  for (int i = 0; i < iterations; i++) {
    printf("iterattions for loops \n");
    if (i%2 == 0) {
      erode(output_image_real, for_eroding, cellpositions);
      write_bitmap(for_eroding, argv[2]);
    } else {
      erode(for_eroding, output_image_real, cellpositions);
      write_bitmap(output_image_real, argv[2]);
    }
    sleep(1);
  }

  drawredcrosses(input_image_real, cellpositions);
  write_bitmap(input_image_real, argv[2]);
  printf("%d", cellcounter);
  printf("Done!\n");
  return 0;
};