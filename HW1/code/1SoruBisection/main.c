/* 
 * File:   main.c
 * Author: YUNUS CEVIK 141044080
 *
 * Created on 11 Mart 2017 Cumartesi, 15:06
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define RESULTS "results1.txt"
void biSection(double a,double b,char *typeOfStopCriterion,double epsilon);
double f(double x);

int main(int argc, char** argv) {
    if (argc !=5){
        fprintf(stderr,"Usage: a b TypeOfStopCritetion Epsilon\n");
        exit(EXIT_FAILURE);
    }
    biSection(atof(argv[1]),atof(argv[2]),argv[3],atof(argv[4]));
    return (EXIT_SUCCESS);
}
void biSection(double a,double b,char *typeOfStopCriterion,double epsilon)
{
    FILE *fPtr;
    fPtr= fopen(RESULTS,"a");
    int i=1;
    double p=0.0,fA=0.0, fP=0.0,tempA=0.0,tempB=0.0;
    tempA=a;
    tempB=b;
    fA=f(a);
    if ((strcmp(typeOfStopCriterion,"DISTANCE_TO_ROOT")==0) 
            || (strcmp(typeOfStopCriterion,"ABSOLUTE_ERROR")==0) 
            || (strcmp(typeOfStopCriterion,"RELATIVE_ERROR")==0) ){
        fprintf(fPtr,"-------------------------------------------------------------------------------\n");
        printf("\n\n%s   %s         %s\n","NO","ABSOLUTE_ERROR","RELATIVE_ERROR");
        fprintf(fPtr,"interval : [%.2f,%.2f]\nthe type Of Stop Criterion : %s\ntolerans : %f\n",a,b,typeOfStopCriterion,epsilon);
        fprintf(fPtr,"\n\n%s\t%s\t%s\n","NO","ABSOLUTE_ERROR","RELATIVE_ERROR");
        while(i<=100){
            p=(a+b)/2.0;
            fP=f(p);
            if((fP==0.0 || fabs(fP)< epsilon) && (strcmp(typeOfStopCriterion,"DISTANCE_TO_ROOT")==0)){
                printf("%d\t%.6f\t\t%.5f\n",i,fabs(p-a),fabs(p-a)/fabs(p));
                printf("\nThe approximate root: %.6f\nThe number of iterations: %d\nThe theoretically "
                    "required number of iterations: %.0f\n",p,i,(ceil(log(epsilon/(tempB-tempA))/-log(2))));
                fprintf(fPtr,"\nThe approximate root: %.6f\nThe number of iterations: %d\nThe theoretically "
                    "required number of iterations: %.0f\n",p,i,(ceil(log(epsilon/(tempB-tempA))/-log(2))));
                fprintf(fPtr,"-------------------------------------------------------------------------------\n");
                exit(EXIT_SUCCESS);
            }
            if((fP==0.0 || fabs(p-a)< epsilon)&& (strcmp(typeOfStopCriterion,"ABSOLUTE_ERROR")==0)){
                printf("%d\t%.6f\t\t%.5f\n",i,fabs(p-a),fabs(p-a)/fabs(p));
                printf("\nThe approximate root: %.6f\nThe number of iterations: %d\nThe theoretically "
                    "required number of iterations: %.0f\n",p,i,(ceil(log(epsilon/(tempB-tempA))/-log(2))));
                fprintf(fPtr,"\nThe approximate root: %.6f\nThe number of iterations: %d\nThe theoretically "
                    "required number of iterations: %.0f\n",p,i,(ceil(log(epsilon/(tempB-tempA))/-log(2))));
                fprintf(fPtr,"-------------------------------------------------------------------------------\n");
                exit(EXIT_SUCCESS);
            }
            if((fP==0.0 || fabs(p-a)/fabs(p)< epsilon) && (strcmp(typeOfStopCriterion,"RELATIVE_ERROR")==0)){
                printf("%d\t%.6f\t\t%.5f\n",i,fabs(p-a),fabs(p-a)/fabs(p));
                printf("\nThe approximate root: %.6f\nThe number of iterations: %d\nThe theoretically "
                    "required number of iterations: %.0f\n",p,i,(ceil(log(epsilon/(tempB-tempA))/-log(2))));
                fprintf(fPtr,"\nThe approximate root: %.6f\nThe number of iterations: %d\nThe theoretically "
                    "required number of iterations: %.0f\n",p,i,(ceil(log(epsilon/(tempB-tempA))/-log(2))));
                fprintf(fPtr,"-------------------------------------------------------------------------------\n");
                exit(EXIT_SUCCESS);
            }

            printf("%d\t%.6f\t\t%.5f\n",i,fabs(p-a),fabs(p-a)/fabs(p));
            fprintf(fPtr,"%d\t\t%.6f\t\t%.5f\n",i,fabs(p-a),fabs(p-a)/fabs(p));

            i++;
            if((fA*fP)>0){
                a=p;
                fA=fP;
            }
            else
                b=p;
        }
        if(i > 100){
               fprintf(stderr,"Root is not found in iteration interval\n");
               exit(EXIT_FAILURE);
        }
    }
    else{
        fprintf(stderr," You have entered the stop criterion incorrectly \n ");
        exit(EXIT_FAILURE);
    }
    fclose(fPtr);  
}
double f(double x){
    double fonk=0.0;
    fonk= (3*x -(exp(x))); // a
    //fonk= (2*x+(3*cos(x))-(exp(x))); // b
    //fonk= (pow(x,2)-(4*x)+4-(log(x))); //c 
    //fonk= (x+1-(2*sin(M_PI*x))); //d
    return fonk;
}
