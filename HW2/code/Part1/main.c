
/* 
 * File:   main.c
 * Author: 141044080 Yunus Cevik
 *
 * Created on 04 Nisan 2017 Salı, 16:52
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define ZERO 1.0E-20
#define N 100
#define TOL 0.001
/*
 * 
 */
int ReadMatrixFile(char *matrixFile);
void ReadMatrixFileAndFill(char **arguman);
void jacobiIterative(double **matrix,double *bMatrix,double *xMatrix,int n);
void gaussianElimination(double **matrix,double *bMatrix,double *xMatrix,int n);

int main(int argc, char** argv) {
    if(argc != 5){
        printf("usage: ./solver <-i> <filename> <-m> <Condution= GESP or JCB>\n");
        printf("\t\t\tor\n");
        printf("usage: ./solver <-m> <Condution= GESP or JCB> <-i> <filename> \n");
        exit(EXIT_FAILURE);
    }
    ReadMatrixFileAndFill(argv);
    return (EXIT_SUCCESS);
}
int ReadMatrixFile(char *matrixFile){
    char ch;
    double num=0.0;
    int count=0;
    FILE *filePointer;
    filePointer=fopen(matrixFile,"r");
    if(filePointer==NULL){
        fprintf(stderr, " UNABLE TO OPEN FILE!!! \n" );
        exit(EXIT_FAILURE);
    }
    else{
        while( ch != '\n'){
            fscanf(filePointer,"%lf%c",&num,&ch);
            count++;
        }
    }
    fclose(filePointer);
    return count;
}
void ReadMatrixFileAndFill(char **arguman){
    char ch;
    double num=0.0,**aMatrix,*bMatrix,*xMatrix,**a2Matrix;
    int count=0,i,j,flag=1,fileNum=0,conditionNum=0;
    FILE *filePointer;
    for(i=0;i<5;i++){
        if(strcmp(arguman[i],"-i")==0)
            fileNum=i+1;
        if(strcmp(arguman[i],"-m")==0)
            conditionNum=i+1;   
    }
    
    
    filePointer=fopen(arguman[fileNum],"r");
    if(filePointer==NULL){
        fprintf(stderr, " UNABLE TO OPEN FILE!!! \n" );
        exit(EXIT_FAILURE);
    }
    else{
        count=ReadMatrixFile(arguman[fileNum]);
        
        bMatrix=(double*)malloc((count-1)*sizeof(double));
        xMatrix=(double*)malloc((count-1)*sizeof(double));
        aMatrix=(double **)malloc((count-1)*sizeof(double*));
        for(i=0;i<count-1;i++)
            aMatrix[i]=(double*)malloc((count-1)*sizeof(double));
        
        a2Matrix=(double **)malloc((count-1)*sizeof(double*));
        for(i=0;i<count;i++)
            a2Matrix[i]=(double*)malloc((count)*sizeof(double));
        
        for(i=0;i<count-1;i++){
            for(j=0;j<count && flag==1;j++){
                fscanf(filePointer,"%lf%c",&num,&ch);
                if(ch == EOF)
                    flag=0;
                if(j==count-1){
                    bMatrix[i]=num;
                    a2Matrix[i][j]=num;
                }
                else{
                    aMatrix[i][j]=num;
                    a2Matrix[i][j]=num;
                }

            }
        }
                
        if(strcmp(arguman[conditionNum],"JCB")==0)
            jacobiIterative(aMatrix,bMatrix,xMatrix,count);
        else if(strcmp(arguman[conditionNum],"GESP")==0)
            gaussianElimination(a2Matrix,bMatrix,xMatrix,count);
        else
            printf("<Condution= GESP or JCB>\n");
    }
    
    for(i=0;i<count-1;i++){
        free(aMatrix[i]);
    }
    free(aMatrix);
    free(bMatrix);
    free(xMatrix);
    fclose(filePointer);
}
void jacobiIterative(double **matrix,double *bMatrix,double *xMatrix,int n){
    int k=0,i,j;
    double result=0.0,*xResult,norm=0.0,normA=0.0,normB=0.0;
    xResult=(double*)malloc((n-1)*sizeof(double));
    for(i=0;i < n-1;i++){
        xMatrix[i]=0;
        xResult[i]=0;
    }
    printf("\n\t\tJacobi’s method \n\n");
    printf("A matrix = Orjinal Matrix\n");
    for (i=1; i<=n-1; i++) {
        for (j=1; j<=n-1; j++) printf(" %11.6f", matrix[i-1][j-1]);
        printf("\n");
    }
    printf("\nB vector\n");
    for(i=0;i<n-1;i++)
        printf("   %f ",bMatrix[i]);
    printf("\n");
    printf("\nFound Roots: \n");
    
    while(k<=N){
        if(k==N){
            fprintf(stderr,"\n\nRoot is not found in iteration interval\n");
            exit(EXIT_FAILURE);
        } 
        printf("%d. iteration values of X vector:\t:",k);
        for(i=0;i < n-1;i++){
            printf(" %.4f ",xResult[i]);
        }
        printf("\n");
        for(i=0;i < n-1;i++){
            for(j=0;j < n-1;j++){    
                if(j!=i)
                    result += matrix[i][j]*xMatrix[j]; 
            }
            xResult[i]=(-result+bMatrix[i]) / matrix[i][i];
            result=0.0;
        }
        for(i=0;i < n-1;i++){
            normA += sqrt(pow(fabs(xMatrix[i]-xResult[i]),2));
            normB += sqrt(pow(fabs(xMatrix[i]),2));
        }
        norm = normA / normB;
        if(norm < TOL){
            exit(EXIT_SUCCESS);
        }
        norm=0.0;
        normA=0.0;
        normB=0.0;
        k++;
        for(i=0;i < n-1;i++){
            xMatrix[i]=xResult[i];
        }
    }
    free(xResult);
    
}
void gaussianElimination(double **matrix,double *bMatrix,double *xMatrix,int n){
    int i,j,k,flag=1,iMax,temp=0;
    double *s,maxVal=0.0,aMax,sum=0.0,val;
    int *nRow;
    nRow=(int *)malloc((n-1)*sizeof(int));
    s=(double*)malloc((n-1)*sizeof(double));
    for(i=0;i<n-1;i++){
        maxVal=fabs(matrix[i][0]);
        for(j=0;j<n-1;j++){
            if(j==n-1)
                bMatrix[i]=matrix[i][j];
            else{
                if(maxVal < fabs(matrix[i][j]))
                    maxVal = fabs(matrix[i][j]); 
            }
        }
        s[i]=maxVal;
        if(s[i]==0){
            printf("No enique solution exists !!!\n");
            exit(EXIT_FAILURE);
        }
        nRow[i]=i+1;
    }
    printf("\n\tGaussian elimination with scaled partial pivoting\n\n");
    printf("A matrix = Orjinal Matrix\n");
    for (i=1; i<=n-1; i++) {
        for (j=1; j<=n-1; j++) printf(" %11.6f", matrix[i-1][j-1]);
        printf("\n");
    }
    i=1;
    while(flag==1 && i<=n-2){
        iMax=nRow[i-1];
        aMax=fabs(matrix[iMax-1][i-1]) / s[iMax-1];
        iMax=i;
        for(j=i+1;j<=n-1;j++){
            if(fabs(matrix[nRow[j-1]-1][i-1]) / s[nRow[j-1]-1] > aMax){
                aMax=fabs(matrix[nRow[j-1]-1][i-1]) / s[nRow[j-1]-1];
                iMax=j;  
            }
        }
        if(aMax<=ZERO){
            printf("No enique solution exists !!!\n");
            flag=0;
        }
        else{
            if(nRow[i-1] != nRow[iMax-1]){
                temp= nRow[i-1];
                nRow[i-1]=nRow[iMax-1];
                nRow[iMax-1]=temp; 
            }
            for(j= i+1;j<=n-1;j++){
                val = matrix[nRow[j-1]-1][i-1] / matrix[nRow[i-1]-1][i-1];
                for(k=i+1;k<=n;k++){   
                    matrix[nRow[j-1]-1][k-1] = matrix[nRow[j-1]-1][k-1] - val * matrix[nRow[i-1]-1][k-1];  
                }
                matrix[nRow[j-1]-1][i-1] = 0.0;
            }
        }
        i++;
    }
    if(flag == 1){
        if(fabs(matrix[nRow[n-2]-1][n-2])<=ZERO){
            printf("No enique solution exists !!!");
            flag=0;
        }
        else{
            xMatrix[n-2] = matrix[nRow[n-2]-1][n-1] / matrix[nRow[n-2]-1][n-2];
            for(k=1;k<=n-2;k++){
                i=n-2-k+1;
                sum=0.0;
                for(j=i+1;j<=n-1;j++)
                   sum = sum - matrix[nRow[i-1]-1][j-1] * xMatrix[j-1];
                xMatrix[i-1] = (matrix[nRow[i-1]-1][n-1] + sum) / matrix[nRow[i-1]-1][i-1];
                
            }
			printf("\nB vector\n");
			for(i=0;i<n-1;i++)
                printf("   %f ",bMatrix[i]);
            printf("\n");
            printf("\nThe reduced system - output by rows\n");
            for (i=1; i<=n-1; i++) {
                for (j=1; j<=n-1; j++) printf(" %11.6f", matrix[i-1][j-1]);
                printf("\n");
            }
            printf("-------------------------------------------------------\n");
            printf("X Vector = Found Roots\n");
            for (i=1; i<=n-1; i++) 
               printf(" %12.6f", xMatrix[i-1]);
            
            
            printf("\nThe rows have been logically re-ordered to:\n");
                for (i=1; i<=n-1; i++) 
                    printf(" %2d", nRow[i-1]);            
            printf("\n");
        }
    }
    free(s);
    free(nRow); 
}
