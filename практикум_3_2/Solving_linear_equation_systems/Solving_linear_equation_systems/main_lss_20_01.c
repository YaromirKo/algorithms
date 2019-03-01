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

 double *X;
 double *tmp;

 file = fopen("test.txt", "r");
 fscanf(file, "%d", &a);

 A = (double**)malloc(a * sizeof(double*));
 X = (double*)malloc(a * sizeof(double));
 tmp = (double*)malloc(a * sizeof(double));

 for (int i = 0; i < a; i++) {
	tmp[i] = i;
 }

 double **A_true;
 A_true = (double**)malloc(a * sizeof(double*));


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
 } printf("%d\n", a);


 for (int i = 0; i < a; i++) {
	for (int j = 0; j < a; j++) {
	 printf("%lf ", A[i][j]);
	}  
	printf(" %lf\n", B[i]);
 }printf("\n");
 ////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////
 for (int i = 0; i < a; i++) {

	double max = A[i][i];
	int column = 0;
	int blabla = 0;
	for (int j = i; j < a; j++) {
	 if (abs(max) < abs(A[i][j])) {
		column = j;
		max = A[i][j];
		blabla = 1;
	 }
	}
	if (blabla == 1) {
	 double change_column;
	 change_column = tmp[i];
	 tmp[i] = tmp[column];
	 tmp[column] = change_column;

	 for (int j = 0; j < a; j++) {
		change_column = A[j][i];
		A[j][i] = A[j][column];
		A[j][column] = change_column;
	 }
	 blabla = 0;
	}
	////////////////////////////////////////////////////////////////////////////////////
	//printf("start change column\n");
	//for (int i = 0; i < a; i++) {
	// for (int j = 0; j < a; j++) {
	//	printf("%lf ", A[i][j]);
	// }
	// printf(" %lf\n", B[i]);
	//}printf("\n");
	////////////////////////////////////////////////////////////////////////////////////
	double save_1 = A[i][i];
	double save_2;
	B[i] = B[i] / A[i][i];

	for (int j = 0; j < a; j++) {
	 A[i][j] = A[i][j] / save_1;
	}

	for (int j = i + 1; j < a; j++) {
	 save_2 = A[j][i];
	 B[j] = B[j] - B[i] * A[j][i];

	 for (int k = i; k < a; k++) {
		A[j][k] = A[j][k] - save_2 * A[i][k];
	 }
	}
	////////////////////////////////////////////////////////////////////////////////////
	//printf("start opiration\n");
	//for (int i = 0; i < a; i++) {
	// for (int j = 0; j < a; j++) {
	//	printf("%lf ", A[i][j]);
	// }
	// printf(" %lf\n", B[i]);
	//}printf("\n");
	////////////////////////////////////////////////////////////////////////////////////
 }
 ////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////
 	for (int i = 0; i < a; i++) {
	 for (int j = 0; j < a; j++) {
		printf("%lf ", A[i][j]);
	 }
	 printf(" %lf\n", B[i]);
	}printf("\n");

	double some_tmp;

	for (int i = a - 1; i > -1; i--) {
	 some_tmp = B[i];
	 

	 int abc = tmp[i];
	 for (int j = a - 1; j > i; j--) {
		some_tmp -= A[i][j] * X[(int)tmp[j]];
	 }
	 X[abc] = some_tmp;
	}

	for (int i = 0; i < a; i++) {
	 printf("x_%d = %lf\n", i + 1, X[i]);
	}printf("\n");


	for (int i = 0; i < a; i++) {
	 double abcd = 0;
	 for (int j = 0; j < a; j++) {
		abcd += A_true[i][j] * X[j];
	 }
	 printf("%lf\n", abcd);
	}


 system("pause");
 return 0;
}
