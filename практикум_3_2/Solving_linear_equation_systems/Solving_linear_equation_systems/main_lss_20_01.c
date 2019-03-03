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

size_t lss_memsize_20_01(int n) { return  n * sizeof(double); }


int check_str(char * first, char * last) {

 int i = 0;
 for (; first[i] != '\0' && last[i] != '\0'; i++) {
	if (first[i] != last[i]) { return 1; }
 }
 if (i < 2) { return 1; }
 else { return 0; }
}

int check_name_txt(char * first) {

 int i = 0;
 int check_index = 0;
	for (i; first[i] != '\0' && first[0] != '-'; i++) {
	 if (first[i] == '.') {
		check_index++;
		if (check_index != 0) {
		 if (first[i + 1] == 't' && first[i + 2] == 'x' && first[i + 3] == 't') {
			check_index = 0;
			return 0;
		 }
		 else {
			check_index = 0;
			i++;
		 }
		}
	 }
	}
	return 1;
}

void set_name_file(int num, char * str, char * path_in, char * path_out) {

 for (int i = 0; path_in[i] != '\0' || path_out[i] != '\0'; i++) {
	if (num == 1) path_in[i] = '\0';
	if (num == 2) path_out[i] = '\0';
 }
 for (int i = 0; str[i] != '\0'; i++) {
	if (num == 1) { path_in[i] = str[i]; }
	if (num == 2) { path_out[i] = str[i]; }
 }
}

void print_help() { printf("\nUsage: lss [input_file_name] [output_file_name] [options]\nWhere options include :\n -d    print debug messages[default OFF]\n -e    print errors[default OFF]\n -p    print matrix[default OFF]\n -t    print execution time[default OFF]\n -h, -? print this and exit\nDefault input_file_name value is lss_00_00_in.txt, default output_file_name value is lss_00_00_out.txt.\n");}

int main(int argc, char *argv[]) {

	FILE *file;

	int n;

	double *A;
	double *B;
	double *X;
	double *tmp;

	int print__help = 0;

	char path_in[256] = "lss_20_01_in.txt";
	char path_out[256] = "lss_20_01_out.txt";

	for (int i = 1; i < argc; i++) {

	 if ((argc > 1 || argc > 2) && check_name_txt(argv[i]) == 0) { set_name_file(i, argv[i], path_in, path_out); }
	 else if (check_str(argv[i], "-h") == 0 || check_str(argv[i], "-?") == 0) { print_help(); print__help = 1; }
	 else if (check_str(argv[i], "-d") == 0) { printf("1\n"); }
	 else if (check_str(argv[i], "-e") == 0) { printf("2\n"); }
	 else if (check_str(argv[i], "-p") == 0) { printf("3\n"); }
	 else if (check_str(argv[i], "-t") == 0) { printf("4\n"); }
	 else { printf("input error, enter for '-h' or '-?', to specify the input\n"); print__help = 1; }
	}

	if (print__help == 0) {

	 file = fopen(path_in, "r");
	 fscanf(file, "%d", &n);

	 A = (double*)malloc(n * n * sizeof(double));
	 B = (double*)malloc(n * sizeof(double));
	 X = (double*)malloc(n * sizeof(double));
	 tmp = (double*)malloc(lss_memsize_20_01(n));

	 for (int i = 0; i < n; i++) {
		tmp[i] = i;
	 }

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


	 printf("\n%d\n", lss_20_01(n, A, B, X, tmp));

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
		printf("%5.9lf\n", fabs(abcd) - fabs(B_tmp[i]));
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
	}
	system("pause");
	return 0;
}
