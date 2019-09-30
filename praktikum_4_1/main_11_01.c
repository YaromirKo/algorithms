#include "task_11_01.h"
/// LR с отражениями
#define ERROR_OPEN_FILE_IN 404
#define ERROR_OPEN_FILE_OUT 406
#define ERROR_DIMENSION 68
#define ERROR_DIMENSION_MATRIX_A 65
#define ERROR_DIMENSION_MATRIX_B 66
#define ERROR_INPUT 400
#define PRINT_INFO 200
#define ERROR_EMPTY 500
#define SUCCESS 0

/* определение размера массива дополнительной памяти */
size_t lss_memsize_20_01(int n) { return n * sizeof(double); }

/* сравнение строк */
int check_str(char * first, char * second) {

    for (int i = 0; first[i] || second[i]; i++) {
        if (first[i] != second[i]) { return 1; }
    }
    return 0;
}

/* функция для проверки содержания в названии файлов (ввода/ввывода) ".txt" */
int check_name_txt(char * name) {

    for (int i = 0; name[0] != '-' && name[i] != '\0'; i++) {
        if (name[i] == '.' && name[i + 1] == 't' && name[i + 2] == 'x' && name[i + 3] == 't') { return 0; }
    }
    return 1;
}
/* печать образца синтаксиса входных параметров */
void print_help() { printf("\nUsage: lss [input_file_name] [output_file_name] [options]\nWhere options include :\n -d    print debug messages[default OFF]\n -e    print errors[default OFF]\n -p    print matrix[default OFF]\n -t    print execution time[default OFF]\n -h, -? print this and exit\nDefault input_file_name value is lss_20_01_in.txt, default output_file_name value is lss_20_01_out.txt.\n");}

/* печать информации по соответвующему коду ошибки */
int errors(int code) {

    switch (code) {

        case ERROR_INPUT: printf("\ninput error, enter for '-h' or '-?', to specify the input\n"); break;
        case ERROR_OPEN_FILE_IN: if (var_for_errors == 1) { printf("\nERROR_OPEN_FILE_IN\n"); } break;
        case ERROR_EMPTY: if (var_for_errors == 1) { printf("\nInput file is empty\n"); } break;
        case ERROR_DIMENSION: if (var_for_errors == 1) { printf("\ndimension less than 1\n"); } break;
        case ERROR_DIMENSION_MATRIX_A: if (var_for_errors == 1) { printf("\nERROR_DIMENSION_MATRIX_A\n"); } break;
        case ERROR_DIMENSION_MATRIX_B: if (var_for_errors == 1) { printf("\nERROR_DIMENSION_MATRIX_B\n"); } break;
        case ERROR_OPEN_FILE_OUT: if (var_for_errors == 1) { printf("\nERROR_OPEN_FILE_OUT\n"); } break;
        case PRINT_INFO: print_help(); break;
    }
    return code;
}

/* печать матрицы A и B */
void print_matrix(int n, double *  A, double * B) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%*lf", 13, A[i * n + j]);
        }
        printf("%*lf\n", 13, B[i]);
    }printf("\n");
}


int main(int argc, char *argv[]) {

    FILE *file;

    int n;       // число уравнений в системе (число неизвестных всегда считаем равным числу уравнений)

    double *A;   // массив матрицы А
    double *B;   // массив матрицы B
    double *X;   // массив значений иксов (вектор ответ)
    double *tmp; // массив дополнительной памяти для вычислений по Методу Гаусса с выбором главного элемента по строке

    clock_t start, end;

    int print__time = 0;   // флаг для печати времени работы алгоритма
    int print__matrix = 0; // флаг для печати входных матриц и матриц после всех преобразований

    char * path_in = "lss_20_01_in.txt";	 // дефолтное имя файла для входных значений
    char * path_out = "lss_20_01_out.txt"; // дефолтное имя файла для выходных значений

    /* проверка входных параметров с консоли */
    for (int i = 1; i < argc; i++) {

        if (check_name_txt(argv[i]) == 0 && (i == 1 || i == 2)) {
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

    /* открытие файла с входными значениями */
    if ((file = fopen(path_in, "r")) == NULL) {
        return errors(ERROR_OPEN_FILE_IN);
    }

    /* считываение первой строки файла */
    if (fscanf(file, "%d", &n) == EOF) {
        return errors(ERROR_EMPTY); // если файл пустой возвращаем ошибку ERROR_EMPTY
    }

    /* если число уравнений в системе (число неизвестных всегда считаем равным числу уравнений) меньше 1, возвращаем ошибку ERROR_DIMENSION */
    if (n < 1) {
        return errors(ERROR_DIMENSION);
    }

    /* выделение памяти под массивы */
    A = (double*)malloc(n * n * sizeof(double));
    B = (double*)malloc(n * sizeof(double));
    X = (double*)malloc(n * sizeof(double));
    tmp = (double*)malloc(lss_memsize_20_01(n));

    /* заполнение массива дополнительной памяти */
    for (int i = 0; i < n; i++) { tmp[i] = i; }

    /* считывание матрицы A с файла */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%lf", &A[i * n + j]) == EOF) {
                return errors(ERROR_DIMENSION_MATRIX_A); // если элементов мьньше чем n*n, то выводим ошибку ERROR_DIMENSION_MATRIX_A
            }
        }
    }

    /* считывание матрицы B с файла */
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%lf", &B[i]) == EOF) {
            return errors(ERROR_DIMENSION_MATRIX_B); // если элементов мьньше чем n, то выводим ошибку ERROR_DIMENSION_MATRIX_A
        }
    }
    fclose(file);

    /* вывод значения n */
    if (var_for_debug == 1 || print__matrix == 1) {
        printf("\n\tdimension: %d\n\n", n);
    }

    /* вызов функции печати матриц */
    if (var_for_debug == 1 || print__matrix == 1) {
        print_matrix(n, A, B);
    }

    start = clock(); // начало работы подпрограммы
    int answer_code = lss_20_01(n, A, B, X, tmp); // вызов функции подпрограммы
    end = clock();   // конец работы подпрограммы

    /* печать матриц после преобразований подпрограммы */
    if (print__matrix == 1 && var_for_debug != 1) {
        print_matrix(n, A, B);
    }

    /* печать времени работы подпрограммы */
    if (print__time == 1) {
        printf("\nexecution time: %lf\n\n", (double)(end - start) / CLOCKS_PER_SEC);
    }

    /* открытие файла на запись ответа */
    if ((file = fopen(path_out, "w")) == NULL) {
        return errors(ERROR_OPEN_FILE_OUT);
    }

    /* записываем в файл результат */
    if (answer_code == 0) {
        fprintf(file, "%d\n", n);
        for (int i = 0; i < n; i++) {
            fprintf(file, "%1.9lf\n", X[i]);
            if (var_for_debug == 1 || print__matrix == 1) {
                printf("\tx_%d = %lf\n", i + 1, X[i]); // печать ответа в консоль
            }
        } if (var_for_debug == 1 || print__matrix == 1) {
            printf("\n");
        }
    }
    else {
        fprintf(file, "%d\n", 0); // если решения системы не существует и выходной файл будет содержать одну единственную цифру '0'
        if (var_for_debug == 1 || print__matrix == 1) {
            printf("no solutions");
            // printf("result: %d\n", 0);
        }
    }

    fclose(file);

    free(A);
    free(B);
    free(X);
    free(tmp);

    return SUCCESS;
}
