/// Метод Гаусса с выбором главного элемента по строке.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#pragma warning(disable : 4996)


int main() {

 FILE *file;
 int a;
 double **A;
 double *B;


 file = fopen("test.txt", "r");
 fscanf(file, "%d", &a);

 A = (double**)malloc(a * sizeof(double*));

 for (int i = 0; i < a; i++) {
	A[i] = (double*)malloc(a * sizeof(double));
	for (int j = 0; j < a; j++) {
	 fscanf(file, "%lf", &A[i][j]);
	}
 }

 B = (double*)malloc(a * sizeof(double));
 
 for (int i = 0; i < a; i++) {
	 fscanf(file, "%lf", &B[i]);
 }

 printf("%d\n", a);


 for (int i = 0; i < a; i++) {
	for (int j = 0; j < a; j++) {
	 printf("%lf ", A[i][j]);
	}  printf("\n");
 }
 for (int i = 0; i < a; i++) {
	 printf("%lf\n", B[i]);
 }



 system("pause");
 return 0;
}
