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
  unsigned char for_eroding[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

void celldetection(unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int cellpositions[BMP_WIDTH][BMP_HEIGTH]);

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
void celldetection(unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], int cellpositions[BMP_WIDTH][BMP_HEIGTH]) {
    // Iterera över alla pixlar i bilden
    for (int x = 7; x < BMP_WIDTH - 7; x++) {  // Startar på 7 och slutar på WIDTH-7 för att undvika utanför gränser
        for (int y = 7; y < BMP_HEIGTH - 7; y++) {

            // Kontrollera exklusionsram (14x14) runt capturing area
            int exclusion_frame_black = 1;
            for (int i = -7; i <= 7; i++) {
                for (int j = -7; j <= 7; j++) {
                    // Exklusionsramen ligger utanför capturing area (12x12)
                    if ((i == -7 || i == 7 || j == -7 || j == 7) && output_image[x + i][y + j][0] != 0) {
                        exclusion_frame_black = 0;
                        break;
                    }
                }
                if (!exclusion_frame_black) break;
            }

            // Om exklusionsramen inte är helt svart, hoppa över
            if (!exclusion_frame_black) continue;

            // Kontrollera capturing area (12x12) för att hitta vita pixlar
            int white_pixel_found = 0;
            for (int i = -6; i <= 6; i++) {
                for (int j = -6; j <= 6; j++) {
                  for (int k = 0; k < BMP_CHANNELS; k++)
                  {
                    if (output_image[x + i][y + j][k] == 255) { // Vita pixlar är 255
                        white_pixel_found = 1;
                        cellpositions[x + i][y + i] = 1;
                        printf("pixel found");
                    }
                  }
                }
                if (white_pixel_found) break;
            }

            // Om minst en vit pixel finns och exklusionsramen är svart
            if (white_pixel_found) {
                // Svärta hela capturing area (12x12) för att undvika dubbelräkning
                for (int i = -6; i <= 6; i++) {
                    for (int j = -6; j <= 6; j++) {
                      for (int k=0; k < BMP_CHANNELS; k++){
                        output_image[x + i][y + j][k] = 0;  // Svärta capturing area
                      }
                    }
                }
            }
        }
    }
}

void drawredcrosses(unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], 
int cellpositions[BMP_WIDTH][BMP_HEIGTH]){
  for (int i = 0; i < BMP_WIDTH; i++){
    for (int j = 0; j < BMP_HEIGTH; j++){
      if (cellpositions[i][j] == 1){
        if (i < BMP_WIDTH - 9 && i > 9 && j < BMP_HEIGTH - 9 && j > 9){
          for (int m = -7; m < 7; m++) {
          input_image[i + m][j][0] = 255;
          input_image[i + m][j][1] = 0;
          input_image[i + m][j][2] = 0;
          input_image[i][j + m][0] = 255;
          input_image[i][j + m][1] = 0;
          input_image[i][j + m][2] = 0;
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

  printf("Done!\n");
  return 0;
};