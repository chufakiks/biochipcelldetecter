//To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
//To run (linux/mac): ./main.out example.bmp example_inv.bmp

//To compile (win): gcc cbmp.c main.c -o main.exe -std=c99
//To run (win): main.exe example.bmp example_inv.bmp

#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"
#include <unistd.h>

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
  unsigned char input_image_real[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
  unsigned char output_image_real[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

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


void erode(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]){
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
  }
void celldetection(output_image){
  for (int x = 0; x < BMP_WIDTH; x++) {
    for (int y = 0; y < BMP_HEIGTH; y++) {
      for (int i = 0; i < x+4; i++){
      }    
      for (int j = 0; j < y+4; j++){
      }
      for (int k = 0; k < x-4; k++){
      }
      for (int n = 0; n < y-4; n++){
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

  convertToGrey(input_image_real, output_image_real);
  int iterations = 15;
  // erode(output_image_real, input_image_real);
  // write_bitmap(input_image_real, argv[2]);
  // sleep(1);
  // erode(input_image_real, output_image_real);
  // write_bitmap(output_image_real, argv[2]);

  for (int i = 0; i < iterations; i++) {
    printf("iterattions for loops \n");
    if (i%2 == 0) {
      erode(output_image_real, input_image_real);
      write_bitmap(input_image_real, argv[2]);
    } else {
      erode(input_image_real, output_image_real);
      write_bitmap(output_image_real, argv[2]);
    }
    sleep(1);
  }
  // if (iterations % 2 == 0) {
  //   write_bitmap(input_image, argv[2]);
  // } else {
  //   write_bitmap(output_image, argv[2]);
  // }
  //Run inversion
  //invert(input_image,output_image);
  //Save image to file

  printf("Done!\n");
  return 0;
};