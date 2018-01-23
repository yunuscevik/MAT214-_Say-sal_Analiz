
/* 
 * File:   main.c
 * Author: Yunus CEVIK
 *
 * Created on 15 Mayıs 2017 Pazartesi, 20:14
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>
#define ZERO 1.0E-20

void gaussianElimination(double **matrix,double *bMatrix,double *xMatrix,int n);
int main(int argc, char** argv) {
    double **aMatrix,*bMatrix,*cMatrix,*dMatrix,*xMatrix;
    int i,j,k,deg,item;
    printf("Polinomun derecesini giriniz : ");
    scanf("%d",&deg);
    printf("Polinom icin kac adet x ve y cifti gireceksiniz? : "); 
    scanf("%d",&item);
    while(deg>item){
        printf("lutfen dereceden buyuk bir adet deger giriniz\n");
        printf("Polinom icin kac adet x ve y cifti gireceksiniz? : "); 
        scanf("%d",&item);
    }
    
    cMatrix=(double*)malloc(((double)item)*sizeof(double));
    dMatrix=(double*)malloc(((double)item)*sizeof(double));
    bMatrix=(double*)malloc(((double)deg+1)*sizeof(double));
    xMatrix=(double*)malloc(((double)deg+1)*sizeof(double));
    aMatrix=(double **)malloc((item)*sizeof(double*));
    for(i=0;i<deg+2;i++)
        aMatrix[i]=(double*)malloc(((double)deg+2)*sizeof(double));
    
    printf("%d adet x ve y cifti giriniz\n",item);
    for(i=0;i<item;i++){
        printf("%d. cift x: y: ",i+1);
        scanf("%lf %lf",&cMatrix[i],&dMatrix[i]);
    }
    for(i=0; i<deg+1 ; i++){
        bMatrix[i]=0;
        for(j=0; j<deg+1 ; j++){
            aMatrix[i][j]=0;
        }
    }
    for(i=0; i<deg+1 ; i++){
        for(j=0; j<item ; j++){
            bMatrix[i] += (pow(cMatrix[j],i) * dMatrix[j]);
        }
    }
    for(i=0; i<deg+1 ; i++){
        for(j=0; j<deg+1 ; j++){
            for(k=0; k<item ; k++){
                aMatrix[i][j]+=pow(cMatrix[k],i+j);
            }
        }
    }
    for(i=0; i<deg+1 ; i++){
        aMatrix[i][deg+1]=bMatrix[i];
    }
    gaussianElimination(aMatrix,bMatrix,xMatrix,deg+2);
    
    
    
    for(i=0;i<deg+2;i++){
        free(aMatrix[i]);
    }
    free(aMatrix);
    free(bMatrix);
    free(cMatrix);
    free(xMatrix);
    
    
    return (EXIT_SUCCESS);
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

            printf("-------------------------------------------------------\n");
            printf("Polinomun katsayilari\n");
            for (i=1; i<=n-1; i++) 
               printf("a%d = %.9f\n",i-1, xMatrix[i-1]);
            
            printf("\nPolinom\n");
            printf("P%d(x) = ",n-2);
            for (i=0; i<n-1; i++){
               printf("%.5f*x^%d", xMatrix[i],i);
               if(i!=n-2)
                   printf(" + ");
            }
            printf("\n");
            printf("-------------------------------------------------------\n");
        }
    }
    free(s);
    free(nRow); 
}


