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

 double *A_tmp;
 double **tem_vec;

 file = fopen("test.txt", "r");
 fscanf(file, "%d", &a);

 A = (double**)malloc(a * sizeof(double*));
 tem_vec = (double**)malloc(a * sizeof(double*));

 A_tmp = (double*)malloc(a * sizeof(double));



 for (int i = 0; i < a; i++) {
	A[i] = (double*)malloc(a * sizeof(double));
	tem_vec[i] = (double*)malloc(a * sizeof(double));

	for (int j = 0; j < a; j++) {
	 fscanf(file, "%lf", &A[i][j]);
	 tem_vec[i][j] = A[i][j];
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
	double now_el = A[i][i];

	for (int j = i; j < a; j++) {
	 A[i][j] = A[i][j] / now_el;

	}
	for (int j = i + 1; j < a; j++) {
	 B[j] = B[j] - B[i] * A[j][i];
	 now_el = A[j][i];

	 for (int k = i; k < a; k++) {

		A[j][k] = A[j][k] - now_el * A[i][k];
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
 printf("///////////////////////////////////////////////////\n");



 
 double some_tmp;

 for (int i = a - 1; i > -1; i--) {
	some_tmp = B[i];

	for (int j = a - 1 ; j > i; j--) {
	 some_tmp = some_tmp - A[i][j] * B[j];

	}
	A_tmp[i] = some_tmp;
 }



 for (int i = 0; i < a; i++) {
	printf("x_%d = %lf\n", i + 1, A_tmp[i]);
 }printf("\n");



 
 for (int i = 0; i < a; i++) {
	double check = 0;
	for (int j = 0; j < a; j++) {
	 check += A_tmp[j] * tem_vec[i][j];
	}
	printf("%lf\n", check);
	check = 0;
 }

 system("pause");
 return 0;
}
