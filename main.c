//To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
//To run (linux/mac): ./main.out example.bmp example_inv.bmp

//To compile (win): gcc cbmp.c main.c -o main.exe -std=c99
//To run (win): main.exe example.bmp example_inv.bmp

#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"

//Function to invert pixels of an image (negative)
void invert(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]){
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

  //Declaring the array to store the image (unsigned char = unsigned 8 bit)
  unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
  unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

  void convertToGrey(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]){

    int thfb = 90;  // Sätt konstantvärden utanför loopen
    unsigned char r, g, b;  // Deklarera färgvariablerna utanför loopen
    unsigned char grey_value; 

      for (int x = 0; x < BMP_WIDTH; x++) { //go through each x then y
          for (int y = 0; y < BMP_HEIGTH; y++) {
            r = input_image[x][y][0]; //read each coulor value
            g = input_image[x][y][1];
            b = input_image[x][y][2];

            grey_value = (r + g + b) / 3; //calculate grey value

            if (grey_value <= thfb) 
              *output_image[x][y] = 0; //svart
            else
              *output_image[x][y] = 255; //vit
          }
      }
    }
  
void erode(unsigned char* input[BMP_WIDTH][BMP_HEIGTH], unsigned char* output[BMP_WIDTH][BMP_HEIGTH]){
  for (int x = 0; x < BMP_WIDTH; x++){
    for (int y = 0; y < BMP_HEIGTH; y++) {

      *output[x][y] = *input[x][y];

      if (*input[x][y] == 255) {

        for (int i = -1; i <= 1; i++) { //look at 3x3 neighburs
          for (int j = -1; j <= 1; j++) {

            if (*input[x+i][y+j] == 0) {
              *input[x][y] = 0;
              break;
            }
        }
      }
    }
     else {
       break; //keep black and move on to next cell
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
  read_bitmap(argv[1], input_image);

  int iterations = 5;
  for (int i = 0; i < iterations; i++) {
    if (i%2 == 0) {
      erode(input_image, output_image);
    } else {
      erode(output_image, input_image);
    }
  }
  if (iterations % 2 == 0) {
    write_bitmap(output_image, argv[2]);
  } else {
    write_bitmap(input_image, argv[2]);
  }
  //Run inversion
  invert(input_image,output_image);

  //Save image to file
  //write_bitmap(output_image, argv[2]);

  printf("Done!\n");
  return 0;
};
 