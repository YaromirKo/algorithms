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

 double **A_tmp;


 file = fopen("test.txt", "r");
 fscanf(file, "%d", &a);

 A = (double**)malloc(a * sizeof(double*));
 A_tmp = (double**)malloc(a * sizeof(double*));


 for (int i = 0; i < a; i++) {
	A[i] = (double*)malloc(a * sizeof(double));
	A_tmp[i] = (double*)malloc(a * sizeof(double));
	for (int j = 0; j < a; j++) {
	 fscanf(file, "%lf", &A[i][j]);
	 A_tmp[i][j] = A[i][j];
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
	}  
	printf(" %lf\n", B[i]);
 }printf("\n");




 for (int i = 0; i < a; i++) {
	B[i] = B[i] / A[i][i];

	for (int j = i; j < a; j++) {

	 A[i][j] = A[i][j] / A[i][i];
	}

	for (int j = i + 1; j < a; j++) {
	 B[j] = B[j] - B[i] * A[j][i];

	 for (int k = i; k < a; k++) {
		printf("\n%lf %lf %lf %lf\n", A[j][k], " = ", A[j][k], " - ", A[j][i], " * ", A[i][k]);
		printf("\n");
		A[j][k] = A[j][k] - A[j][i] * A[i][k];
		for (int i = 0; i < a; i++) {
		 for (int j = 0; j < a; j++) {
			printf("%lf ", A[i][j]);
		 }
		 printf(" %lf\n", B[i]);
		}printf("\n");
	 }
	}
 }
 
 printf("///////////////////////////////////////////////////\n");
 for (int i = 0; i < a; i++) {
	for (int j = 0; j < a; j++) {
	 printf("%lf ", A[i][j]);
	}
	printf(" %lf\n", B[i]);
 }printf("\n");



 system("pause");
 return 0;
}
