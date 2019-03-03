#include "lss_20_01.h"

/*1. Программа должна состоять из двух модулей 
		 - интерфейсного (обеспечивающего разбор командной строки, 
											файловый ввод - вывод, выделение памяти, обработку ошибок и т.д.) 
		и вычислительного (обеспечивающего непосредственное решение задачи).*/

size_t lss_memsize_20_01(int n) { return  (double*)malloc(n * sizeof(double)); }

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

double time_spent(clock_t start, clock_t end) { return (double)(end - start) / CLOCKS_PER_SEC; }

int main(int argc, char *argv[]) {

	FILE *file;

	int n;

	double *A;
	double *B;
	double *X;
	double *tmp;

	clock_t start, end;

	int print__time = 0;
	int print__help = 0;
	int print__matrix = 0;

	char path_in[256] = "lss_20_01_in.txt";
	char path_out[256] = "lss_20_01_out.txt";

	for (int i = 1; i < argc; i++) {

	 if ((argc > 1 || argc > 2) && check_name_txt(argv[i]) == 0) { set_name_file(i, argv[i], path_in, path_out); }
	 else if (check_str(argv[i], "-h") == 0 || check_str(argv[i], "-?") == 0) { print_help(); print__help = 1; }
	 else if (check_str(argv[i], "-d") == 0) { var_for_debug = 1; }
	 else if (check_str(argv[i], "-e") == 0) { var_for_errors = 1; }
	 else if (check_str(argv[i], "-p") == 0) { print__matrix = 1; }
	 else if (check_str(argv[i], "-t") == 0) { print__time = 1; }
	 else { printf("input error, enter for '-h' or '-?', to specify the input\n"); print__help = 1; break; }
	}

	if (print__help == 0) {

	 file = fopen(path_in, "r");
	 fscanf(file, "%d", &n);
	 A = (double*)malloc(n * n * sizeof(double));
	 B = (double*)malloc(n * sizeof(double));
	 X = (double*)malloc(n * sizeof(double));
	 tmp = lss_memsize_20_01(n);
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
	 } if(var_for_debug == 1 || print__matrix == 1)printf("\n\tdimension: %d\n\n", n);
	 fclose(file);

	 if (var_for_debug == 1 || print__matrix == 1) {
		for (int i = 0; i < n; i++) {
		 for (int j = 0; j < n; j++) {
			printf("%*lf", 13, A[i * n + j]);
		 }
		 printf("%*lf\n", 13, B[i]);
		}printf("\n");
	 }

	 start = clock();
	 lss_20_01(n, A, B, X, tmp);
	 end = clock();

	 if (print__matrix == 1) {
		for (int i = 0; i < n; i++) {
		 for (int j = 0; j < n; j++) {
			printf("%*lf", 13, A[i * n + j]);
		 }
		 printf("%*lf\n", 13, B[i]);
		}printf("\n");
	 }

	 if (print__time == 1) { printf("\nexecution time: %lf\n", time_spent(start, end)); }

	 file = fopen(path_out, "w");
	 fprintf(file, "%d\n", n);
	 for (int i = 0; i < n; i++) {
		fprintf(file, "%1.9lf\n", X[i]);
		 if(var_for_debug == 1) printf("x_%d = %lf\n", i + 1, X[i]);
	 } if (var_for_debug == 1) printf("\n");


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
