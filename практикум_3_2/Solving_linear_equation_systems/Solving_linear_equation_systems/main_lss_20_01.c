#include "lss_20_01.h"

#define ERROR_OPEN_FILE_IN 404
#define ERROR_OPEN_FILE_OUT 406
#define ERROR_DIMENSION 68
#define ERROR_DIMENSION_MATRIX_A 65
#define ERROR_DIMENSION_MATRIX_B 66
#define ERROR_INPUT 400
#define PRINT_INFO 200
#define ERROR_EMPTY 500

/*1. Программа должна состоять из двух модулей 
		 - интерфейсного (обеспечивающего разбор командной строки, 
											файловый ввод - вывод, выделение памяти, обработку ошибок и т.д.) 
		и вычислительного (обеспечивающего непосредственное решение задачи).*/

size_t lss_memsize_20_01(int n) { return n * sizeof(double); }

int check_str(char * first, char * last) {

 int i = 0;
 for (; first[i] != '\0' && last[i] != '\0' || first[2]; i++) {
	if (first[i] != last[i]) { return 1; }
 }
 if (i < 2) { return 1; }
 else { return 0; }
}

int check_name_txt(char * first) {

	for (int i = 0; first[i] != '\0' && first[0] != '-'; i++) {
	 if (first[i] == '.' && first[i + 1] == 't' && first[i + 2] == 'x' && first[i + 3] == 't') { return 0; }
	}
	return 1;
}

void print_help() { printf("\nUsage: lss [input_file_name] [output_file_name] [options]\nWhere options include :\n -d    print debug messages[default OFF]\n -e    print errors[default OFF]\n -p    print matrix[default OFF]\n -t    print execution time[default OFF]\n -h, -? print this and exit\nDefault input_file_name value is lss_00_00_in.txt, default output_file_name value is lss_00_00_out.txt.\n");}

double time_spent(clock_t start, clock_t end) { return (double)(end - start) / CLOCKS_PER_SEC; }


int errors(int code) {

 switch (code) {

  case ERROR_INPUT: printf("\ninput error, enter for '-h' or '-?', to specify the input\n"); break;
	case ERROR_OPEN_FILE_IN: if (var_for_errors == 1) { printf("\nERROR_OPEN_FILE_IN\n"); } break;
	case ERROR_EMPTY: if (var_for_errors == 1) { printf("\nInput file is empty\n"); } break;
	case ERROR_DIMENSION: if (var_for_errors == 1) { printf("\ndimension less than 2\n"); } break;
	case ERROR_DIMENSION_MATRIX_A: if (var_for_errors == 1) { printf("\nERROR_DIMENSION_MATRIX_A\n"); } break;
	case ERROR_DIMENSION_MATRIX_B: if (var_for_errors == 1) { printf("\nERROR_DIMENSION_MATRIX_B\n"); } break;
	case ERROR_OPEN_FILE_OUT: if (var_for_errors == 1) { printf("\nERROR_OPEN_FILE_OUT\n"); } break;
	case PRINT_INFO: print_help(); break;
	}
 return code;
}

int main(int argc, char *argv[]) {


	FILE *file;
	int n;

	double *A;
	double *B;
	double *X;
	double *tmp;

	clock_t start, end;

	int print__time = 0;
	int print__matrix = 0;

	char * path_in = "lss_20_01_in.txt";
	char * path_out = "lss_20_01_out.txt";

	for (int i = 1; i < argc; i++) {

	 if ((argc > 1 || argc > 2) && check_name_txt(argv[i]) == 0) { 
		if (i == 1) { path_in = argv[1]; }
		if (i == 2) { path_out = argv[2]; }
	 }
	 else if (check_str(argv[i], "-h") == 0 || check_str(argv[i], "-?") == 0) { return errors(PRINT_INFO); }
	 else if (check_str(argv[i], "-d") == 0) { var_for_debug = 1; }
	 else if (check_str(argv[i], "-e") == 0) { var_for_errors = 1; }
	 else if (check_str(argv[i], "-p") == 0) { print__matrix = 1; }
	 else if (check_str(argv[i], "-t") == 0) { print__time = 1; }
	 else { return errors(ERROR_INPUT); }
	}


	if ((file = fopen(path_in, "r")) == NULL) { return errors(ERROR_OPEN_FILE_IN); }

	int check_not_a_char = fscanf(file, "%d", &n);
	
	if (check_not_a_char == EOF || check_not_a_char < 1 ) { return errors(ERROR_EMPTY); }

	if (n < 2) { return errors(ERROR_DIMENSION); }

	A = (double*)malloc(n * n * sizeof(double));
	B = (double*)malloc(n * sizeof(double));
	X = (double*)malloc(n * sizeof(double));
	tmp = (double*)malloc(lss_memsize_20_01(n));
	for (int i = 0; i < n; i++) { tmp[i] = i; }

	///double **A_true;
	///double *B_tmp;
	///A_true = (double**)malloc(n * sizeof(double*));
	///B_tmp = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++) {
	 ///A_true[i] = (double*)malloc(n * sizeof(double));
	 for (int j = 0; j < n; j++) {
		if (fscanf(file, "%lf", &A[i * n + j]) == EOF) { return errors(ERROR_DIMENSION_MATRIX_A); }
		///A_true[i][j] = A[i * n + j];
	 }
	}

	for (int i = 0; i < n; i++) {
	 if (fscanf(file, "%lf", &B[i]) == EOF) { return errors(ERROR_DIMENSION_MATRIX_B); }
	 ///B_tmp[i] = B[i];
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
	int answer_code = lss_20_01(n, A, B, X, tmp);
	end = clock();

	if (print__matrix == 1 && var_for_debug != 1) {
	 for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
		 printf("%*lf", 13, A[i * n + j]);
		}
		printf("%*lf\n", 13, B[i]);
	 }printf("\n");
	}

	if (print__time == 1) { printf("\nexecution time: %lf\n\n", time_spent(start, end)); }

	file = fopen(path_out, "w");

	if (file == NULL) { return errors(ERROR_OPEN_FILE_OUT); }

	if (answer_code == 0) {
	 fprintf(file, "%d\n", n);
	 for (int i = 0; i < n; i++) {
		fprintf(file, "%1.9lf\n", X[i]);
		if (var_for_debug == 1) printf("\tx_%d = %lf\n", i + 1, X[i]);
	 } if (var_for_debug == 1) printf("\n");
	}
	else {
	 fprintf(file, "%d\n", 0);
	 if (var_for_debug == 1) printf("result: %d\n", 0);
	}
	


	/*for (int i = 0; i < n; i++) {
	 double abcd = 0;
	 for (int j = 0; j < n; j++) {
		abcd += A_true[i][j] * X[j];
	 }
	 printf("%5.9lf\n", fabs(abcd) - fabs(B_tmp[i]));
	}printf("\n");*/

	/*for (int i = 0; i < n; i++) {
	 double abcd = 0;
	 for (int j = 0; j < n; j++) {
		abcd += A_true[i][j] * X[j];
	 }
	 printf("%5.5lf=%5.5lf\n", abcd, B_tmp[i]);
	}*/

	free(A);
	free(B);
	free(X);
	free(tmp);

	fclose(file);
	
	//system("pause");
	return 0;
}
