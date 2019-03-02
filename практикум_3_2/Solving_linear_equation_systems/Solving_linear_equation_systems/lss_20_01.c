#include "lss_20_01.h"
#define ELEM(Matrix,RowLen,row,col) (Matrix + RowLen * row)[col]
/*Подпрограмма решения системы должна возвращать следующие значения:

   0 - работа завершена успешно, решение построено
   1 - работа завершена успешно, решения системы не существует
   -1 - метод решения не применим к данной системе 
   
Метод решения может быть не применим к системе, например, в силу вырожденности матрицы системы для метода решения через построение LU разложения. */

int lss_20_01(int n, double * A, double * B, double * X, double * tmp) {
 int p = 1;
 int this_is_null = 0;
 int column;
 int swap_сolumns = 0;
 
 double max;
 double save_1;

 for (int i = 0; i < n; i++) {

	max = ELEM(A, n, i, i);

	for (int j = i; j < n; j++) {
	 printf("%5.9lf ", ELEM(A, n, i, j));
	 if (fabs(fabs(ELEM(A, n, i, j)) - 1e-6) <= 1e-6) {
		this_is_null++;
	 }
	 if (fabs(max) < fabs(ELEM(A, n, i, j))) {
		column = j;
		max = ELEM(A, n, i, j);
		swap_сolumns = 1;
	 }
	}
	printf("\n%d %d\n", this_is_null, n - i);
	if (n - i == this_is_null) {
	 if (fabs(B[i] - 1e-6) <= 1e-6) {
		X[(int)tmp[i]] = 0;
		this_is_null = 0;
		continue;
	 }
	 else {
		return 1;
	 }
	 this_is_null = 0;
	 continue;
	}
	else {
	 this_is_null = 0;
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
	if (1 == p) {
	 printf("start change column\n");
	 for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
		 printf("%*lf", 13, ELEM(A, n, i, j));
		}
		printf("%*lf\n", 13, B[i]);
	 }printf("\n");
	}
	save_1 = ELEM(A, n, i, i);
	B[i] = B[i] / ELEM(A, n, i, i);

	for (int j = i; j < n; j++) {
	 ELEM(A, n, i, j) = ELEM(A, n, i, j) / save_1;
	}

	for (int j = i + 1; j < n; j++) {
	 save_1 = ELEM(A, n, j, i);
	 B[j] = B[j] - B[i] * ELEM(A, n, j, i);

	 for (int k = i; k < n; k++) {
		ELEM(A, n, j, k) = ELEM(A, n, j, k) - save_1 * ELEM(A, n, i, k);
	 }
	 this_is_null = 0;
	}
	if (1 == p) {
	 printf("algoritm\n");
	 for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
		 printf("%*lf", 13, ELEM(A, n, i, j));
		}
		printf("%*lf\n", 13, B[i]);
	 }printf("\n");
	}
 }
 ////////////////////////////////////////////////////////////////////////////////////
 for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
	 printf("%*lf", 13, ELEM(A, n, i, j));
	}
	printf("%*lf\n", 13, B[i]);
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
