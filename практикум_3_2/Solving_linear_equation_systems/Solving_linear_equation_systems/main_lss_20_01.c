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
	
	double save_1 = A[i][i];
	B[i] = B[i] / A[i][i];

	for (int j = 0; j < a; j++) {
	 A[i][j] = A[i][j] / save_1;
	}

	for (int j = i + 1; j < a; j++) {
	 save_1 = A[j][j - 1];
	 B[j] = B[j] - B[i] * A[j][j - 1];

	 for (int k = i; k < a; k++) {
		A[j][k] = A[j][k] - save_1 * A[i][k];
	 }
	}
 }

 	for (int i = 0; i < a; i++) {
	 for (int j = 0; j < a; j++) {
		printf("%lf ", A[i][j]);
	 }
	 printf(" %lf\n", B[i]);
	}printf("\n");

	double some_tmp;

	for (int i = a - 1; i > -1; i--) {
	 some_tmp = B[i];

	 for (int j = a - 1; j > i; j--) {
		int abc = 0;
		for (int k = 0; k < a; k++) {
		 if (tmp[k] == j) {
			abc = tmp[k];
			break;
		 }
		}
		some_tmp -= A[i][j] * X[abc];
	 }
	 X[i] = some_tmp;
	}

	for (int i = 0; i < a; i++)
	{
	 printf("%lf ", X[i]);
	}printf("\n");

	for (int i = 0; i < a; i++) {
	 printf("x_%d = %lf\n", i + 1, X[i]);
	}printf("\n");


	//for (int i = 0; i < a; i++) {
	// double abcd = 0;
	// for (int j = 0; j < a; j++) {
	//	abcd += A_true[i][j] * X[j];
	// }
	// printf("%lf\n", abcd);
	//}





 ////////////////////////////////////////////////////////////////////////////////////
 /*for (int i = 0; i < a; i++) {
	double max = A[i][i];
	int change = 0;
	int column;
	for (int j = 0; j < a; j++) {
	 if (abs(max) < abs(A[i][j])) {
		max = A[i][j];
		column = j;
		change = 1;
		printf("%d\n", j);
	 }
	}

	if (change == 1) {

	 for (int q = 0; q < a; q++) {
	 } printf("\n");
		printf("%lf ", tmp[q]);
	 printf("change\n");
	 double tr;
	 tmp[i] = column;
	 tmp[column] = i;
	 for (int k = i; k < a; k++) {
		tr = A[k][i];
		A[k][i] = A[k][column];
		A[k][column] = tr;
	 }
	 change = 0;
	 for (int q = 0; q < a; q++) {
		printf("%lf ", tmp[q]);
	 } printf("\n");
	 printf("use\n");
	}

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
		printf("\n%lf %lf %lf %lf\n", A[j][k], " = ", A[j][k], " - ", now_el, " * ", A[i][k]);
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
		if (tmp[w] == j) {
		 some_tmp = some_tmp - A[i][w] * B[j];
		}
	 }
	}
	X[i] = some_tmp;
 }



 for (int i = 0; i < a; i++) {
	printf("x_%d = %lf\n", i + 1, X[i]);
 }printf("\n");



 
 for (int i = 0; i < a; i++) {
	double check = 0;
	for (int j = 0; j < a; j++) {
	 check += X[j] * A_true[i][j];
	}
	printf("%lf\n", check);
	check = 0;
 }*/

 system("pause");
 return 0;
}
