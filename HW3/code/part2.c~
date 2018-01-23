
/* 
 * File:   main.c
 * Author: asus-ubuntu
 *
 * Created on 15 Mayıs 2017 Pazartesi, 00:44
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int i,j,k,size,artSize;
    double x[5]={1.0, 1.3, 1.6, 1.9, 2.2};
    double b[5]={0.7651977, 0.6200860, 0.4554022, 0.2818186, 0.1103623};
    double fx[5][5];
    for(i=0; i<5;i++)
        fx[0][i]=b[i];
    size=4;
    for(i=0; i<4;i++){
        for(j=0; j<size;j++)
            fx[i+1][j]=((fx[i][j+1]-fx[i][j]) / (x[j+i+1]-x[j]));
        size--;
    }
    printf("i\tx[i]\tFirst\t\tSecond\t\tThird\t\tFourth\t\tFifth\n");
    printf("---------------------------------------------------------------------------------------------\n");
    size=5;
    artSize=5;
    for(i=0; i<artSize;i++){
        printf("%d\t%.1f  |\t",i,x[i]);
        for(j=0; j<size;j++)
            printf("%.7f\t",fx[j][i]);
        printf("\n");
        size--;
    }
    printf("\n----------------------------------------------------------------------------------------------\n");
    printf("Yukaridaki verilerin polinomu asagida yer almaktadir\n");
    printf("----------------------------------------------------------------------------------------------\n");  
    printf("P4(x) = ");
    size=5;
    artSize=1;
    
    for(j=0; j<size;j++){
        printf("%.7f",fx[j][0]);
        if(j!=0){
            for(k=0; k<artSize && artSize !=5 ;k++)
                printf("(x - %.1f)",x[k]); 
            artSize++;
        }
        if(j !=4)
            printf(" + ");
        if(j==2)
            printf("\n");
    }
    printf("\n");
    printf("----------------------------------------------------------------------------------------------\n");    

    return (EXIT_SUCCESS);
}

