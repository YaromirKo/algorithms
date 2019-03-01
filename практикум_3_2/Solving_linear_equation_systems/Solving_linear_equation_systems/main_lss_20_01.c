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

 double *answer;
 double **A_true;
 double *index_vector;

 file = fopen("test.txt", "r");
 fscanf(file, "%d", &a);

 A = (double**)malloc(a * sizeof(double*));
 A_true = (double**)malloc(a * sizeof(double*));
 answer = (double*)malloc(a * sizeof(double));
 index_vector = (double*)malloc(a * sizeof(double));
 for (int i = 0; i < a; i++) {
	index_vector[i] = i;
 }


 for (int i = 0; i < a; i++) {
	A[i] = (double*)malloc(a * sizeof(double));
	A_true[i] = (double*)malloc(a * sizeof(double));

	for (int j = 0; j < a; j++) {
	 fscanf(file, "%lf", &A[i][j]);
	 A_true[i][j] = A[i][j];
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



 ////////////////////////////////////////////////////////////////////////////////////
 for (int i = 0; i < a; i++) {
	double max = A[i][i];
	int change = 0;
	int column;
	for (int j = 0; j < a; j++) {
	 if (abs(max) < abs(A[i][j])) {
		max = A[i][j];
		column = j;
		change = 1;
	 }
	}
	

	if (change == 1) {
	 double tr;
	 index_vector[i] = column;
	 index_vector[column] = i;
	 for (int k = i; k < a; k++) {
		tr = A[i][k];
		A[k][i] = A[k][column];
		A[k][column] = tr;
		for (int i = 0; i < a; i++) {
		 for (int j = 0; j < a; j++) {
			printf("%lf ", A[i][j]);
		 }
		 printf(" %lf\n", B[i]);
		}printf("\n");
	 }
	 change = 0;
	}
	printf("use");
	for (int i = 0; i < a; i++) {
	 for (int j = 0; j < a; j++) {
		printf("%lf ", A[i][j]);
	 }
	 printf(" %lf\n", B[i]);
	}printf("\n");
	B[i] = B[i] / max;
	double now_el = max;

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
	for (int i = 0; i < a; i++) {
	 for (int j = 0; j < a; j++) {
		printf("%lf ", A[i][j]);
	 }
	 printf(" %lf\n", B[i]);
	}printf("\n");
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
	 for (int w = 0; w < a; w++)
	 {
		if (index_vector[w] == j) {
		 some_tmp = some_tmp - A[i][w] * B[j];
		}
	 }
	}
	answer[i] = some_tmp;
 }



 for (int i = 0; i < a; i++) {
	printf("x_%d = %lf\n", i + 1, answer[i]);
 }printf("\n");



 
 for (int i = 0; i < a; i++) {
	double check = 0;
	for (int j = 0; j < a; j++) {
	 check += answer[j] * A_true[i][j];
	}
	printf("%lf\n", check);
	check = 0;
 }

 system("pause");
 return 0;
}
