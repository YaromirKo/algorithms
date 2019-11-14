#include "lss_20_01.h"
/// Метод Гаусса с выбором главного элемента по строке.
#define ELEM(matrix, len, row, col) (matrix + len * row)[col]

/* печать матриц A и B с заголовком */
void print_matrix_a_b(int n, double * A, double * B, char * string) {

 printf("\t%s\n\n", string);
 for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
	 printf("%*lf", 13, ELEM(A, n, i, j));
	}
	printf("%*lf\n", 13, B[i]);
 }printf("\n");
}

/* подпрограмма решающая систему уравнений методом Гаусса с выбором главного элемента по строке */
int lss_20_01(int n, double * A, double * B, double * X, double * tmp) {

 int count_null = 0; // для подсчета нулей в строке соответстующей i-ой итерации
 int column; // номер столбца с максимальным по модулю значением элемента в i-ой строке матрицы А
 int swap_сolumns = 0; // флаг для перестановки колонок
 
 double max; // максимальное по модулю значение элемента в i-ой строке матрицы А
 double save_1; // вспомогательная переменная


 /* Прямой ход. Исходная система сводится к эквивалентной системе с верхней треугольной матрицей */
 for (int i = 0; i < n; i++) {

	max = ELEM(A, n, i, i); 

	/* поиск максимального по модулю значения элемента в i-ой строке матрицы А */
	for (int j = i; j < n; j++) {
	 if (fabs(ELEM(A, n, i, j)) <= 1e-9) { // подсчет нулей в строке i
		count_null++;
	 }
	 if (fabs(max) < fabs(ELEM(A, n, i, j))) {
		column = j;
		max = ELEM(A, n, i, j);
		swap_сolumns = 1;
	 }
	}

	/* проверка на нулевые значения строки */
	if (n - i == count_null) {
	 if (fabs(B[i]) <= 1e-9) { // если i-ая строка состоит из нулей и соответствующий элемент матрицы B = 0, тогда
		X[(int)tmp[i]] = 0; // присваиваем значение '0' в массиве X по i-му элементу массива tmp(содержащий индексы иксов в порядке соответствущий перестановкам колонок матрицы A) 
		count_null = 0;
		continue;
	 }
	 else { return 1; } //  если i-ая строка состоит из нулей и соответствующий элемент матрицы B != 0, тогда возвращаем '1', тк решений нет
	}
	else { count_null = 0; }

	/* печать номера итерации, если была указана опция '-d' */
	if (var_for_debug == 1) { printf("\n\t%s %d\n", "Iteration number: ", i + 1); }

	/* перестановка значений колонок в матрице A и сохраняем индексы иксов */
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

	save_1 = ELEM(A, n, i, i); // ведущий элемент
	B[i] = B[i] / ELEM(A, n, i, i); // делим i элемент матрицы B на ведущий элемент

	for (int j = i; j < n; j++) {
	 ELEM(A, n, i, j) = ELEM(A, n, i, j) / save_1; // делим элементы строки на ведущий элемент
	}

	/* зануляем столбцы под соответствующими ведущими элементами, преобразовываем внутреннюю часть матрицы A, B (после строки с ведущим элементом) */
	for (int j = i + 1; j < n; j++) {
	 save_1 = ELEM(A, n, j, i); 
	 B[j] = B[j] - B[i] * ELEM(A, n, j, i);

	 for (int k = i; k < n; k++) {
		ELEM(A, n, j, k) = ELEM(A, n, j, k) - save_1 * ELEM(A, n, i, k);
	 }
	 count_null = 0;
	}
	if (var_for_debug == 1) { print_matrix_a_b(n, A, B, "transform the inner part of the matrix");	}
 }

 /* обратный ход. Находим иксы */
 for (int i = n - 1; i > -1; i--) {
	save_1 = B[i];
	int abc = tmp[i];
	for (int j = n - 1; j > i; j--) {
	 save_1 -= ELEM(A, n, i, j) * X[(int)tmp[j]];
	}
	X[abc] = save_1;
 }

 return 0; // если решение найдено возвращаем '0'
}
