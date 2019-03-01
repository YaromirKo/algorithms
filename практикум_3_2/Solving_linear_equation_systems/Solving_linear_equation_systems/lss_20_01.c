#include "lss_20_01.h"
#define ELEM(Matrix,RowLen,row,col) (Matrix+RowLen*row)[col]
/*Подпрограмма решения системы должна возвращать следующие значения:

   0 - работа завершена успешно, решение построено
   1 - работа завершена успешно, решения системы не существует
   -1 - метод решения не применим к данной системе 
   
Метод решения может быть не применим к системе, например, в силу вырожденности матрицы системы для метода решения через построение LU разложения. */

int lss_20_01(int n, double * A, double * B, double * X, double * tmp) {

 printf("\n%lf\n", (&A)[0][5]);

 for (int i = 0; i < n; i++) {
	double max = (&A)[i][i];
	int column;
	int swap_сolumns = 0;
	for (int j = i; j < n; j++) {
	 if (abs(max) < abs((&A)[i][j])) {
		column = j;
		max = (&A)[i][j];
		swap_сolumns = 1;
	 }
	}
	if (swap_сolumns == 1) {
	 double change_column;
	 change_column = tmp[i];
	 tmp[i] = tmp[column];
	 tmp[column] = change_column;

	 for (int j = 0; j < n; j++) {
		change_column = (&A)[j][i];
		(&A)[j][i] = (&A)[j][column];
		(&A)[j][column] = change_column;
	 }
	 swap_сolumns = 0;
	}
	/*printf("start change column\n");
	for (int i = 0; i < a; i++) {
	for (int j = 0; j < a; j++) {
	printf("%lf ", (&A)[i][j]);
	}
	printf(" %lf\n", B[i]);
	}printf("\n");*/
	double save_1 = (&A)[i][i];
	double save_2;
	B[i] = B[i] / (&A)[i][i];

	for (int j = 0; j < n; j++) {
	 (&A)[i][j] = (&A)[i][j] / save_1;
	}

	for (int j = i + 1; j < n; j++) {
	 save_2 = (&A)[j][i];
	 B[j] = B[j] - B[i] * (&A)[j][i];

	 for (int k = i; k < n; k++) {
		(&A)[j][k] = (&A)[j][k] - save_2 * (&A)[i][k];
	 }
	}
	/*printf("start opiration\n");
	for (int i = 0; i < a; i++) {
	for (int j = 0; j < a; j++) {
	printf("%lf ", (&A)[i][j]);
	}
	printf(" %lf\n", B[i]);
	}printf("\n");*/
 }
 ////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////
 for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
	 printf("%lf ", (&A)[i][j]);
	}
	printf(" %lf\n", B[i]);
 }printf("\n");

 double some_tmp;

 for (int i = n - 1; i > -1; i--) {
	some_tmp = B[i];
	int abc = tmp[i];
	for (int j = n - 1; j > i; j--) {
	 some_tmp -= (&A)[i][j] * X[(int)tmp[j]];
	}
	X[abc] = some_tmp;
 }


 return 0;
}
