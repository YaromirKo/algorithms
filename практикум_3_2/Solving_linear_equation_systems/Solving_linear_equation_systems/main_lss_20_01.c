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

size_t lss_memsize_SS_NN(int n) {

}

int main() {

 FILE *file;
 int a;
 double **A;
 double *B;

 double *X;
 double *tmp;
 char path_in[256] = "lss_20_01_in.txt";
 char path_out[256] = "lss_20_01_out.txt";


 file = fopen(path_in, "r");
 fscanf(file, "%d", &a);

 A = (double**)malloc(a * sizeof(double*));
 X = (double*)malloc(a * sizeof(double));
 tmp = (double*)malloc(a * sizeof(double));

 for (int i = 0; i < a; i++) {
	tmp[i] = i;
 }

 double **A_true;
 double *B_tmp;
 A_true = (double**)malloc(a * sizeof(double*));
 B_tmp = (double*)malloc(a * sizeof(double));



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
	 B_tmp[i] = B[i];
 } printf("%d\n", a);
 fclose(file);

 for (int i = 0; i < a; i++) {
	for (int j = 0; j < a; j++) {
	 printf("%lf ", A[i][j]);
	}  
	printf(" %lf\n", B[i]);
 }printf("\n");
 ////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////
 lss_20_01(a, A, B, X, tmp);

	file = fopen(path_out, "w");
	fprintf(file, "%d\n", a);
	for (int i = 0; i < a; i++) {
	 fprintf(file, "%1.9lf\n", X[i]);
	 printf("x_%d = %lf\n", i + 1, X[i]);

	}printf("\n");


	for (int i = 0; i < a; i++) {
	 double abcd = 0;
	 for (int j = 0; j < a; j++) {
		abcd += A_true[i][j] * X[j];
	 }
	 printf("%5.5lf=%5.5lf\n", abcd, B_tmp[i]);
	}


	fclose(file);
 system("pause");
 return 0;
}
