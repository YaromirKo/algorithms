#include "lss_20_01.h"


/*1. Программа должна состоять из двух модулей 
		 - интерфейсного (обеспечивающего разбор командной строки, 
											файловый ввод - вывод, выделение памяти, обработку ошибок и т.д.) 
		и вычислительного (обеспечивающего непосредственное решение задачи).*/

/*Печать общего времени выполнения программы - строго обязательная опция.
tmp - массив дополнительной памяти (если она требуется методу). Размер массива дополнительной памяти должен определяться функцией
size_t lss_memsize_SS_NN(int n)
Получать в этой подпрограмме дополнительную информацию извне через глобальные переменные 
(за исключением двух глобальных переменных, контролирующих режимы работы "-d" и "-e"), 
общие блоки, включаемые файлы и т. п. запрещается. Выделение памяти в подпрограмме также запрещается; 
вся дополнительная память должна передаваться через вектор tmp. */

size_t lss_memsize_20_01(int n) { (double*)malloc(n * sizeof(double)); }

int main() {

	FILE *file;

	int n;

	double *A;
	double *B;
	double *X;
	double *tmp;

	char path_in[256] = "lss_20_01_in.txt";
	char path_out[256] = "lss_20_01_out.txt";

	file = fopen(path_in, "r");
	fscanf(file, "%d", &n);

	A = (double*)malloc(n * n * sizeof(double));
	B = (double*)malloc(n * sizeof(double));
	X = (double*)malloc(n * sizeof(double));
	tmp = lss_memsize_20_01(n);

	for (int i = 0; i < n; i++) { tmp[i] = i; }

	double **A_true;
	double *B_tmp;
	A_true = (double**)malloc(n * sizeof(double*));
	B_tmp = (double*)malloc(n * sizeof(double));

	for (int i = 0; i < n; i++) {
	 A_true[i] = (double*)malloc(n * sizeof(double));
	 for (int j = 0; j < n; j++) {
		fscanf(file, "%lf", &A[i * n + j]);
		A_true[i][j] = A[i * n + j];
	 }
	}
 
	for (int i = 0; i < n; i++) {
		fscanf(file, "%lf", &B[i]);
		B_tmp[i] = B[i];
	} printf("%d\n", n);
	fclose(file);

	for (int i = 0; i < n; i++) {
	 for (int j = 0; j < n; j++) {
		printf("%*lf", 13, A[i * n + j]);
	 }  
	 printf("%*lf\n", 13, B[i]);
	}printf("\n");


  lss_20_01(n, A, B, X, tmp);

	file = fopen(path_out, "w");
	fprintf(file, "%d\n", n);
	for (int i = 0; i < n; i++) {
	 fprintf(file, "%1.9lf\n", X[i]);
	 printf("x_%d = %lf\n", i + 1, X[i]);
	}printf("\n");


	for (int i = 0; i < n; i++) {
	 double abcd = 0;
	 for (int j = 0; j < n; j++) {
		abcd += A_true[i][j] * X[j];
	 }
	 printf("%5.9lf\n", abs(abcd) - abs(B_tmp[i]));
	}printf("\n");

	for (int i = 0; i < n; i++) {
	 double abcd = 0;
	 for (int j = 0; j < n; j++) {
		abcd += A_true[i][j] * X[j];
	 }
	 printf("%5.5lf=%5.5lf\n", abcd, B_tmp[i]);
	}




	free(A);
	free(B);
	free(X);
	free(tmp);


	fclose(file);
	system("pause");
	return 0;
}
