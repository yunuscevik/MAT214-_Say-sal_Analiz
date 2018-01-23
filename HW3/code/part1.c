
/* 
 * File:   main.c
 * Author: Yunus CEVIK
 *
 * Created on 13 Mayıs 2017 Cumartesi, 18:25
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10
#define SIZE2 SIZE*2
#define SIZE3 SIZE*3
#define PIXEL 99

void randomMatrix(int matrix[][SIZE],int Size);
void nearstNeighborInterpolation(int matrix[][SIZE],int Size);
void bilinearInterpolation(int matrix[][SIZE],int Size);

int main(int argc, char** argv) {
    int arr[SIZE][SIZE];
    int size=SIZE;
    randomMatrix(arr,size);
    nearstNeighborInterpolation(arr,size);
    bilinearInterpolation(arr,size);
    
    return (EXIT_SUCCESS);
}
void randomMatrix(int matrix[][SIZE],int Size){
    int i,j,k;
    srand(time(NULL));
    for(i=0; i < Size ; i++){
        for(j=0 ; j < Size ; j++){
            matrix[i][j]= rand() % PIXEL;
        }
    }
    /************************print********************************************/
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("Random olusturulmus 10 x 10 luk bir matrix\n");
   printf("------------------------------------------------------------------------------------------------------\n");
    k=1;
    for(i=0; i < Size ; i++){
        for(j=0 ; j < Size ; j++){
            if(j==k){
                printf("\t");
                k += 1;
            }
            printf("%d",matrix[i][j]);
        }
        printf("\n");
        k=1;
    }
    printf("------------------------------------------------------------------------------------------------------\n");
}
void nearstNeighborInterpolation(int matrix[][SIZE],int Size){
    int nMatrix2[SIZE2][SIZE2];
    int nMatrix3[SIZE3][SIZE3];
    int i,j,k,l;
    for(i=0; i < Size ; i++){
        for(j=0 ; j < Size ; j++){
            for(k=0; k < 2 ; k++){
                for(l=0 ; l < 2 ; l++){
                    nMatrix2[(i*2)+k][(j*2)+l]=matrix[i][j];
                }
            }
            for(k=0; k < 3 ; k++){
                for(l=0 ; l < 3 ; l++){
                    nMatrix3[(i*3)+k][(j*3)+l]=matrix[i][j];
                }
            }   
        } 
    }
    /************************print********************************************/
    printf("Nearest Neighbor Interpolation z=2 zoom (20 x 20 matrix)\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    k=2;
    l=3;
    for(i=0; i < SIZE2 ; i++){
        for(j=0 ; j < SIZE2 ; j++){
            if(j==k){
                printf("\t");
                k += 2;
            }
            printf("%d",nMatrix2[i][j]);
        }
        printf("\n");
        k=2;
    }
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("Nearest Neighbor Interpolation z=3 zoom (30 x 30 matrix)\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    
    for(i=0; i < SIZE3 ; i++){
        for(j=0 ; j < SIZE3 ; j++){
            if(j==l){
                printf("\t");
                l += 3;
            }
            printf("%d",nMatrix3[i][j]);
        }
        printf("\n");
        l=3;
    }
    printf("------------------------------------------------------------------------------------------------------\n");
}
void bilinearInterpolation(int matrix[][SIZE],int Size){
    int nMatrix2[SIZE2][SIZE2];
    int nMatrix3[SIZE3][SIZE3];
    int i,j,k,l;
    for(i=0; i < Size ; i++){
        for(j=0 ; j < Size ; j++){
             nMatrix2[(i*2)][(j*2)]=matrix[i][j];
             nMatrix3[(i*3)][(j*3)]=matrix[i][j]; 
        }
        for(j=0 ; j < Size ; j++){
            nMatrix2[(i*2)][(j*2)+1] = nMatrix2[(i*2)][(j*2)] + ((nMatrix2[(i*2)][(j*2)+2] - nMatrix2[(i*2)][(j*2)]) / 2);
            nMatrix3[(i*3)][(j*3)+1] = nMatrix3[(i*3)][(j*3)] + ((nMatrix3[(i*3)][(j*3)+3] - nMatrix3[(i*3)][(j*3)]) / 3);
            nMatrix3[(i*3)][(j*3)+2] = nMatrix3[(i*3)][(j*3)] + (2 * (nMatrix3[(i*3)][(j*3)+3] - nMatrix3[(i*3)][(j*3)]) /3);
        }
    }
    for(i=0; i < Size ; i++){
        nMatrix2[(i*2)][SIZE2-1]= nMatrix2[(i*2)][SIZE2-2] + ((0-nMatrix2[(i*2)][SIZE2-2]) / 2);
        nMatrix3[(i*3)][SIZE3-2]= nMatrix3[(i*3)][SIZE3-3] + ((0-nMatrix3[(i*3)][SIZE3-3]) / 3);
        nMatrix3[(i*3)][SIZE3-1]= nMatrix3[(i*3)][SIZE3-3] + (2 * (0-nMatrix3[(i*3)][SIZE3-3]) / 3);
    }
    for(i=0; i < Size ; i++){
        for(j=0 ; j < Size ; j++){
            for(k=0; k < 2 ; k++)
                nMatrix2[(i*2)+1][(j*2)+k] = nMatrix2[(i*2)][(j*2)+k] + ((nMatrix2[(i*2)+2][(j*2)+k] - nMatrix2[(i*2)][(j*2)+k]) / 2); 
            for(k=0; k < 3 ; k++){
                nMatrix3[(i*3)+1][(j*3)+k] = nMatrix3[(i*3)][(j*3)+k] + ((nMatrix3[(i*3)+3][(j*3)+k] - nMatrix3[(i*3)][(j*3)+k]) / 3);
                nMatrix3[(i*3)+2][(j*3)+k] = nMatrix3[(i*3)][(j*3)+k] + (2 * (nMatrix3[(i*3)+3][(j*3)+k] - nMatrix3[(i*3)][(j*3)+k]) / 3);
            }
        }
    }
    for(i=0; i < Size ; i++){
        for(k=0; k < 2 ; k++)
            nMatrix2[SIZE2-1][(i*2)+k]= nMatrix2[SIZE2-2][(i*2)+k] + ((0-nMatrix2[SIZE2-2][(i*2)+k]) / 2);
        for(k=0; k < 3 ; k++){
            nMatrix3[SIZE3-2][(i*3)+k]= nMatrix3[SIZE3-3][(i*3)+k] + ((0-nMatrix3[SIZE3-3][(i*3)+k]) / 3);
            nMatrix3[SIZE3-1][(i*3)+k]= nMatrix3[SIZE3-3][(i*3)+k] + (2 * (0-nMatrix3[SIZE3-3][(i*3)+k]) / 3);
        }
    }
    
    /************************print********************************************/
    printf("Bilinear Interpolation z=2 zoom (20 x 20 matrix)\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    k=2;
    l=3;
    for(i=0; i < SIZE2 ; i++){
        for(j=0 ; j < SIZE2 ; j++){
            if(j==k){
                printf("\t");
                k += 2;
            }
            printf("%d",nMatrix2[i][j]);  
        }
        printf("\n");
        k=2;
    }
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("Bilinear Interpolation z=3 zoom (30 x 30 matrix)\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    for(i=0; i < SIZE3 ; i++){
        for(j=0 ; j < SIZE3 ; j++){
            if(j==l){
                printf("\t");
                l += 3;
            }
            printf("%d",nMatrix3[i][j]);
        }
        printf("\n");
        l=3;
    }
    printf("------------------------------------------------------------------------------------------------------\n");
    
}
