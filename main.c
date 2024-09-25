//To compile (linux/mac): gcc cbmp.c main.c -o main.out -std=c99
//To run (linux/mac): ./main.out example.bmp example_inv.bmp

//To compile (win): gcc cbmp.c main.c -o main.exe -std=c99
//To run (win): main.exe example.bmp example_inv.bmp

#include "cbmp.h"
#include <stdlib.h>
#include <stdio.h>


  //helper to visualize erosion
  unsigned char** forimagereader (unsigned char output[BMP_WIDTH][BMP_HEIGTH]){
    unsigned char*** array = malloc(BMP_WIDTH * sizeof(unsigned char**));
    for (int i = 0; i < BMP_WIDTH; i++) {
        array[i] = malloc(BMP_WIDTH * sizeof(unsigned char*));
        for (int j = 0; j < BMP_HEIGTH; j++) {
            array[i][j] = malloc(3 * sizeof(unsigned char));
        }
    }

    for (int i = 0; i < BMP_WIDTH; i++) {
      for (int j = 0; j < BMP_HEIGTH; j++){
        array[i][j][0]= output[i][j];
        array[i][j][1]= output[i][j];
        array[i][j][2]= output[i][j];
      }
    }
    return array;
  }


  //Declaring the array to store the image (unsigned char = unsigned 8 bit)
  unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
  unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

  unsigned char** convertToGrey(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]){
  unsigned char** output_image = (unsigned char**)malloc(BMP_WIDTH * sizeof(unsigned char*));
  for (int i = 0; i < BMP_WIDTH; i++) {
        output_image[i] = (unsigned char*)malloc(BMP_HEIGTH * sizeof(unsigned char));
    }

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
              output_image[x][y] = 0; //svart
            else
              output_image[x][y] = 255; //vit
          }
      }
      return output_image;
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

  //Load image from filey
  read_bitmap(argv[1], input_image);

  unsigned char** output_image = convertToGrey(input_image);


  unsigned char** outputparsed;
  int iterations = 5;
  for (int i = 0; i < iterations; i++) {
    if (i%2 == 0) {
      erode(input_image, output_image);
    } else {
      erode(output_image, input_image);
    }
  }
  if (iterations % 2 == 0) {
    outputparsed = forimagereader(output_image);
    write_bitmap(output_image, argv[2]);
  } else {
    write_bitmap(input_image, argv[2]);
  }

  //Save image to file
  write_bitmap(outputparsed, argv[2]);

  printf("Done!\n");
  return 0;

  
  
};
 