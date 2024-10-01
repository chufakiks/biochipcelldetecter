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
  struct vector {
    unsigned char x;
    unsigned char y;
  };
  struct vector cellDetected[(BMP_HEIGTH*4) - 4];
  struct vector cellCenters[((1/2) * BMP_HEIGTH) * ((1/2) * BMP_HEIGTH)];
  short int ite = 0;
  int a = 0; //kom
  int* n = &a;
  void erosionOtp (unsigned char* input[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char* output[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]) {
       for (int i = 0; i < ((BMP_HEIGTH-0)/2); i++){
        for(int x = ite; x < BMP_WIDTH - ite; x++){
          if(*input[x][ite][0] == 255){
            cellDetected[*n].x = x;
            cellDetected[*n].y = ite;
            (*n)++;
          }
        }
        for(int y = ite; y < BMP_HEIGTH - ite; y++){
          if(*input[BMP_WIDTH - ite][y][0] == 255){
            cellDetected[*n].x = BMP_WIDTH - ite;
            cellDetected[*n].y = y;
            (*n)++;
          }
        }
        for(int x = (BMP_WIDTH - 1) - ite; x >= 0 + ite; x--){
          if(*input[x][BMP_HEIGTH - ite][0] == 255){
            cellDetected[*n].x = x;
            cellDetected[*n].y = BMP_HEIGTH - ite;
            (*n)++;
          }
        }
         for(int y = (BMP_HEIGTH - 1)- i; y >= 0 + i; y--){
          if(*input[ite][y][0] == 255){
            cellDetected[*n].x = ite;
            cellDetected[*n].y = y;
            (*n)++;
          }
         }
         ite++;
          cellDetectionOpt(input, output, &n);
        }
  }
 struct vector temp;
 short int ds[4];
  void cellDetectionOpt(unsigned char* input[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], unsigned char* output[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int* n){
    if (*n > 0){
      for (; *n >= 0; *n--){
        if (*input[cellDetected[*n].x][cellDetected[*n].y][0] == 255){
          temp.x = cellDetected[*n].x;
          temp.y = cellDetected[*n].y;
          findGridSize(input, temp);
          erodeBox(ds);
        } 
     } 
    } 
    erosionOtp(&output, &input);
    
  }
  char done = 1;
  char* tempDone = &done;
  short int minx, maxx, miny, maxy;
void findGridSize(unsigned char* input[BMP_HEIGTH][BMP_WIDTH][BMP_CHANNELS],struct vector start){
  while (*tempDone){
    if (input_image[start.x-1][start.y][0] == 255){

    }
    else if (input_image[start.x][start.y-1][0] == 255){

    }
    else if (input_image[start.x+1][start.y][0] == 255){

    } 
    else if (input_image[start.x][start.y+1][0] == 255){

    }
    /* if (queue.notempty()) {

    } else {
      *tempDone = 0;
      ds[0] = minx;
      ds[1] = maxx;
      ds[2] = miny;
      ds[3] = maxy;
    }*/
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
  
  printf("Done!\n");
  return 0;
}
