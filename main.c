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
  unsigned char dualIm[BMP_WIDTH][BMP_HEIGTH];
  unsigned char erode[BMP_WIDTH][BMP_HEIGTH];

  void convertToGrey(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]){

    int thfb = 90;  // Sätt konstantvärden utanför loopen
    unsigned char r, g, b;  // Deklarera färgvariablerna utanför loopen
    unsigned char grey_value; 

      for (int x = 0; x < BMP_WIDTH; x++) { //go through each x then y
          for (int y = 0; y < BMP_HEIGTH; y++) {
            r = input_image[x][y][0]; //read each coulor value
            g = input_image[x][y][1];
            b = input_image[x][y][2];

            grey_value = (r + g + b) / 3; //calculate grey value #2

            if (grey_value <= thfb)  //  #3
              *output_image[x][y] = 0; //black
            else
              *output_image[x][y] = 255; //white
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

  //Run inversion
  invert(input_image,output_image);

  //Save image to file
  write_bitmap(output_image, argv[2]);

  void erosionOtp (unsigned char* input[BMP_WIDTH][BMP_HEIGTH], unsigned char* output[BMP_WIDTH][BMP_HEIGTH]) {
       for (int i = 0; i < ((BMP_HEIGTH-0)/2); i++){
        for(int j = i; j < BMP_WIDTH - i; j++){
          if(*input[j][0] == 255){
            // add to cellDetected
          }
        }
        for(int j = i; j < BMP_HEIGTH - i; j++){
          if(*input[j][0] == 255){
            // add to cellDetected
          }
        }
        for(int j = (BMP_WIDTH - 1) - i; j >= 0 + i; j--){
          if(*input[j][0] == 255){
            // add to cellDetected
          }
        }
         for(int j = (BMP_HEIGTH - 1)- i; j >= 0 + i; j--){
          if(*input[j][0] == 255){
            // add to cellDetected
          }
         }
          cellDetectionOpt(input, output, foundCell);
        }
  }
  void cellDetectionOpt(unsigned char* input[BMP_WIDTH][BMP_HEIGTH], unsigned char* output[BMP_WIDTH][BMP_HEIGTH],
                        unsigned char* foundCell){
    if (foundCell.lenght() > 0){
      for (int i = 0; i < foundCell.lenght(); i++){
        if (*input[x][y] == 255){
          findGrindSize()
        }
      foundCell = 0;
     } 
    } 
    
    erosionOtp(output, input);
    
  }
  short int[] findGridSize(unsigned char* input[BMP_HEIGTH][BMP_WIDTH]){

    // Return er et char array, hvor index 0 er min_x, index 1 er max_x, index 2 er min_y og index 3 er max_y
  }
  printf("Done!\n");
  return 0;
}
