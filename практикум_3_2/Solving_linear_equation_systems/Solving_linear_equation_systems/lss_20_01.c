#include "lss_20_01.h"
#define ELEM(Matrix,RowLen,row,col) (Matrix + RowLen * row)[col]
/*Подпрограмма решения системы должна возвращать следующие значения:

   0 - работа завершена успешно, решение построено
   1 - работа завершена успешно, решения системы не существует
   -1 - метод решения не применим к данной системе 
   
Метод решения может быть не применим к системе, например, в силу вырожденности матрицы системы для метода решения через построение LU разложения. */

void print_matrix_a_b(int n, double * A, double * B, char * string) {

 printf("\t%s\n\n", string);
 for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
	 printf("%*lf", 13, ELEM(A, n, i, j));
	}
	printf("%*lf\n", 13, B[i]);
 }printf("\n");
}

int lss_20_01(int n, double * A, double * B, double * X, double * tmp) {

 int this_is_null = 0;
 int column;
 int swap_сolumns = 0;
 
 double max;
 double save_1;

 for (int i = 0; i < n; i++) {

	if (var_for_debug == 1) { printf("\n\t%s %d\n", "Iteration number: ", i + 1); }

	max = ELEM(A, n, i, i);

	for (int j = i; j < n; j++) {
	 if (fabs(ELEM(A, n, i, j)) <= 1e-6) {
		this_is_null++;
	 }
	 if (fabs(max) < fabs(ELEM(A, n, i, j))) {
		column = j;
		max = ELEM(A, n, i, j);
		swap_сolumns = 1;
	 }
	}
	if (n - i == this_is_null) {
	 if (fabs(B[i]) <= 1e-6) {
		X[(int)tmp[i]] = 0;
		this_is_null = 0;
		continue;
	 }
	 else { return 1; }
	}
	else { this_is_null = 0; }

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

	 if (var_for_debug == 1) { print_matrix_a_b(n, A, B, "changing columns"); }
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
	if (var_for_debug == 1) { print_matrix_a_b(n, A, B, "transform the inner part of the matrix");	}
 }

 for (int i = n - 1; i > -1; i--) {
	save_1 = B[i];
	int abc = tmp[i];
	for (int j = n - 1; j > i; j--) {
	 save_1 -= ELEM(A, n, i, j) * X[(int)tmp[j]];
	}
	X[abc] = save_1;
 }

 return 0;
}
