#include "lss_20_01.h"
#define ELEM(Matrix,RowLen,row,col) (Matrix + RowLen * row)[col]
/*Подпрограмма решения системы должна возвращать следующие значения:

   0 - работа завершена успешно, решение построено
   1 - работа завершена успешно, решения системы не существует
   -1 - метод решения не применим к данной системе 
   
Метод решения может быть не применим к системе, например, в силу вырожденности матрицы системы для метода решения через построение LU разложения. */

int lss_20_01(int n, double * A, double * B, double * X, double * tmp) {

 

 //printf("\n%lf\n", ELEM(ELEM(A, n, i, j)A, 4, 1, 2));

 for (int i = 0; i < n; i++) {
	double max = ELEM(A, n, i, i);
	int column;
	int swap_сolumns = 0;
	for (int j = i; j < n; j++) {
	 if (abs(max) < abs(ELEM(A, n, i, j))) {
		column = j;
		max = ELEM(A, n, i, j);
		swap_сolumns = 1;
	 }
	}
	if (swap_сolumns == 1) {
	 double change_column;
	 change_column = tmp[i];
	 tmp[i] = tmp[column];
	 tmp[column] = change_column;

	 for (int j = 0; j < n; j++) {
		change_column = ELEM(A, n, j, i);
		ELEM(A, n, j, i) = ELEM(A, n, j, column);
		ELEM(A, n, j, column) = change_column;
	 }
	 swap_сolumns = 0;
	}
	/*printf("start change column\n");
	for (int i = 0; i < a; i++) {
	for (int j = 0; j < a; j++) {
	printf("%lf ", ELEM(A, n, i, j)A[i][j]);
	}
	printf(" %lf\n", B[i]);
	}printf("\n");*/
	double save_1 = ELEM(A, n, i, i);
	double save_2;
	B[i] = B[i] / ELEM(A, n, i, i);

	for (int j = 0; j < n; j++) {
	 ELEM(A, n, i, j) = ELEM(A, n, i, j) / save_1;
	}

	for (int j = i + 1; j < n; j++) {
	 save_2 = ELEM(A, n, j, i);
	 B[j] = B[j] - B[i] * ELEM(A, n, j, i);

	 for (int k = i; k < n; k++) {
		ELEM(A, n, j, k) = ELEM(A, n, j, k) - save_2 * ELEM(A, n, i, k);
	 }
	}
	/*printf("start opiration\n");
	for (int i = 0; i < a; i++) {
	for (int j = 0; j < a; j++) {
	printf("%lf ", ELEM(A, n, i, j)A[i][j]);
	}
	printf(" %lf\n", B[i]);
	}printf("\n");*/
 }
 ////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////
 for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
	 printf("%lf ", ELEM(A, n, i, j));
	}
	printf(" %lf\n", B[i]);
 }printf("\n");

 double some_tmp;

 for (int i = n - 1; i > -1; i--) {
	some_tmp = B[i];
	int abc = tmp[i];
	for (int j = n - 1; j > i; j--) {
	 some_tmp -= ELEM(A, n, i, j) * X[(int)tmp[j]];
	}
	X[abc] = some_tmp;
 }


 return 0;
}
