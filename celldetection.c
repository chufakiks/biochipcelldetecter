#include <stdlib.h>
#include <stdio.h>
#include "cbmp.h"


int blackexclusionarea(int x, int y, unsigned char imagearray[BMP_WIDTH][BMP_HEIGTH]) {
    if (x >= 11) { // up
        for (int i = -6; i < 8; i++) {
            if (y + i >= 0 && y <= BMP_HEIGTH){
                if(imagearray[x][y + i] == 255) return 0;
            }      
        }
    }

    if (x < BMP_WIDTH - 13){ // down
        for (int i = -6; i < 8; i++) {
            if (y - i >= 0){
                if(imagearray[x][y - i] == 255) return 0;
            }      
        }
    }

    if (y >= 11) { // left
        for (int i = -6; i < 8; i++){
            if (x + i >= 0){
                if(imagearray[x + 1][y] == 255) return 0;
            }
        }
    }

    if (y < BMP_HEIGTH - 13){ //right
        for (int i = -6; i < 8; i++){
            if (x - i >= 0){
                if(imagearray[x - 1][y] == 255) return 0;
            }
        }
    }

    return 1; 
}

int whiteincapturearea(int x, int y, unsigned char imagearray[BMP_WIDTH][BMP_HEIGTH]) {
    for (int i = -5; i < 7; i++){
        if (x + i >= 0 && x + i <= BMP_WIDTH){
            for (int j = -5; j < 7; j++){
                if (y + i >= 0 && y + i <= BMP_HEIGTH) {
                    if (imagearray[x + i][y + j] == 255) return 1; 
                }
            }
        }
    }
    return 0;
}

void settoblack(int x, int y, unsigned char imagearray[BMP_WIDTH][BMP_HEIGTH]){
    for (int i = -5; i < 7; i++){
        if (x + i >= 0 && x + i < BMP_WIDTH){
            for (int j = -5; j < 7; j++){
                if (y + i >= 0 && y + i < BMP_HEIGTH) {
                    imagearray[x + i][y + j] = 0; 
                }
            }
        }
    }
}

int celldetection (unsigned char imagearray[BMP_WIDTH][BMP_HEIGTH]){
    for (int x = 0; x < BMP_WIDTH; x++){
        for (int y = 0; y < BMP_HEIGTH; y++) {
            if (blackexclusionarea(x,y,imagearray) == 1 && whiteincapturearea(x,y,imagearray) == 1) {settoblack(x,y,imagearray);}
        }
    }
}