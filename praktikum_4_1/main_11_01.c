// интерфейс
#include "task_11_01.h"
/// LR с отражениями
#define ERROR_OPEN_FILE_IN 404
#define ERROR_OPEN_FILE_OUT 406
#define ERROR_DIMENSION 68
#define ERROR_DIMENSION_MATRIX_A 65
#define ERROR_INPUT 400
#define PRINT_INFO 200
#define ERROR_EMPTY 500
#define SUCCESS 0

/* определение размера массива дополнительной памяти для модуля sim - модуля упрощения */
size_t sim_memsize_11_01(int n) { return n * sizeof(double); }

/* определение размера массива дополнительной памяти для модуля evc - вычислительный модуль */
size_t evc_memsize_11_01(int n) { return n * sizeof(double); }

/* сравнение строк */
int check_str(char * first, char * second, int lim) {

    for (int i = 0; (lim == 0 && (first[i] || second[i])) || (lim > 0 && i < lim); i++) {
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
void print_help() {
    printf("\nUsage: evc [input_file_name] [output_file_name] [options]\n"
           "Where options include:\n"
           " -d                print debug messages [default OFF]\n"
           " -e                print errors [default OFF]\n"
           " -p                print matrix [default OFF]\n"
           " -t                print execution time [default OFF]\n"
           " -prec=<num>       precision [default - 1e-14]\n"
           " -eps=<num>        epsilon [default - 1e-10]\n"
           " -max_iter=<num>   limit number of iterations [default - 0, i.e. not limit]\n"
           " -h, -?            print this and exit\n");
}

/* печать информации по соответвующему коду ошибки */
int errors(int code) {

    switch (code) {

        case ERROR_INPUT: printf("\ninput error, enter for '-h' or '-?', to specify the input\n"); break;
        case ERROR_OPEN_FILE_IN: if (var_for_errors == 1) { printf("\nERROR_OPEN_FILE_IN\n"); } break;
        case ERROR_EMPTY: if (var_for_errors == 1) { printf("\nInput file is empty\n"); } break;
        case ERROR_DIMENSION: if (var_for_errors == 1) { printf("\ndimension less than 1\n"); } break;
        case ERROR_DIMENSION_MATRIX_A: if (var_for_errors == 1) { printf("\nERROR_DIMENSION_MATRIX_A\n"); } break;
        case ERROR_OPEN_FILE_OUT: if (var_for_errors == 1) { printf("\nERROR_OPEN_FILE_OUT\n"); } break;
        case PRINT_INFO: print_help(); break;
    }
    return code;
}

/* печать матрицы A и B */
void print_matrix(int n, double *  A) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%*lf", 13, A[i * n + j]);
        } printf("\n");
    } printf("\n");
}


int main(int argc, char *argv[]) {

    FILE *file;

    double precision = 1e-14; // определяет, числа меньше какого считать нулем
    double epsilon = 1e-10; // точность
    int max_iter = 0; //  ограничение на число итераций алгоритма (если оно нулевое или отрицательное - ограничений нет)

    int n;       // размерность матрицы

    double *A;   // массив матрицы А
    double *E;   // массив полученных собственных значений (упорядоченных по возрастанию)
    double *tmp_sim; // массив дополнительной памяти для модуля sim - модуля упрощения
    double *tmp_evc; // массив дополнительной памяти для модуля evc - вычислительный модуль

    clock_t start, end;

    int print__time = 0;   // флаг для печати времени работы алгоритма
    int print__matrix = 0; // флаг для печати входных матриц и матриц после всех преобразований

    char * path_in = "11_01_in.txt";	 // дефолтное имя файла для входных значений
    char * path_out = "11_01_out.txt"; // дефолтное имя файла для выходных значений

    /* проверка входных параметров с консоли */
    for (int i = 1; i < argc; i++) {

        if (check_name_txt(argv[i]) == 0 && (i == 1 || i == 2)) {
            if (i == 1) { path_in = argv[1]; }
            if (i == 2) { path_out = argv[2]; }
        }
        else if (check_str(argv[i], "-h", 0) == 0 || check_str(argv[i], "-?", 0) == 0) { return errors(PRINT_INFO); }
        else if (check_str(argv[i], "-d", 0) == 0) { var_for_debug = 1; }
        else if (check_str(argv[i], "-e", 0) == 0) { var_for_errors = 1; }
        else if (check_str(argv[i], "-p", 0) == 0) { print__matrix = 1; }
        else if (check_str(argv[i], "-t", 0) == 0) { print__time = 1; }

        else if (check_str(argv[i], "-prec=",      6) == 0) { precision = atof(&argv[i][6]); }
        else if (check_str(argv[i], "-eps=",       5) == 0) { epsilon = atof(&argv[i][5]); }
        else if (check_str(argv[i], "-max_iter=", 10) == 0) { max_iter = (int)atof(&argv[i][10]); }

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
    E = (double*)malloc(n * sizeof(double));
    tmp_sim = (double*)malloc(sim_memsize_11_01(2 * n * n + n));
    tmp_evc = (double*)malloc(evc_memsize_11_01(n * n + 2 * n));

    /* заполнение массива дополнительной памяти */
    for (int i = 0; i < 2 * n; ++i) {
        for (int j = 0; j < n; ++j) {
            tmp_sim[i * n + j] = 0;
            if (i < n) tmp_evc[i * n + j] = 0;
        }
    }

    /* считывание матрицы A с файла */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%lf", &A[i * n + j]) == EOF) {
                return errors(ERROR_DIMENSION_MATRIX_A); // если элементов мьньше чем n*n, то выводим ошибку ERROR_DIMENSION_MATRIX_A
            }
        }
    }

    fclose(file);

    /* вывод значения n */
    if (var_for_debug == 1 || print__matrix == 1) {
        printf("\n\tdimension: %d\n\n", n);
    }

    /* вызов функции печати матриц */
    if (var_for_debug == 1 || print__matrix == 1) {
        print_matrix(n, A);
    }

    start = clock(); // начало работы выполнения алгоритма
                          sim_11_01(n, A, tmp_sim, precision); // Основная функция модуля упрощения матрицы
    int answer_code_evc = evc_11_01(n, max_iter, epsilon, A, E, tmp_evc, precision); // Основная функция модуля построения собственных значений матрицы
    end = clock();   // конец работы выполнения алгоритма

    /* печать матриц после преобразований подпрограммы */
    if (print__matrix == 1 && var_for_debug != 1) {
        print_matrix(n, A);
    }

    /* открытие файла на запись ответа */
    if ((file = fopen(path_out, "w")) == NULL) {
        return errors(ERROR_OPEN_FILE_OUT);
    }

    /* записываем в файл результат */
    fprintf(file, "%d\n", n);

    for (int i = 0; i < n; i++) {
        fprintf(file, "%1.9lf\n", E[i]);
        if (var_for_debug == 1 || print__matrix == 1) {
            printf("\te_%d = %1.9lf\n", i + 1, E[i]); // печать ответа в консоль
        }
    }

    if (var_for_debug == 1) {
        if (answer_code_evc == 1) printf("the method does not converge for the specified number of iterations\n");
        else printf("work completed successfully\n");
    }

    /* печать времени работы подпрограммы */
    if (print__time == 1) {
        printf("\nexecution time: %lf\n\n", (double)(end - start) / CLOCKS_PER_SEC);
    }

    fclose(file);

    free(A);
    free(E);
    free(tmp_sim);
    free(tmp_evc);

    return SUCCESS;
}
