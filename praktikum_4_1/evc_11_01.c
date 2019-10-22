// вычислительный модуль
#include "task_11_01.h"

#define _A(matrix, len, row, col) (matrix + len * row)[col]
#define L(matrix, len, row, col) (matrix + len * row)[col]
#define R(matrix, len, row, col) (matrix + len * row)[col]
#define tmp(matrix, len, row, col) (matrix + len * row)[col]
#define E(matrix, len, row, col) (matrix + len * row)[col]

// печать матрицы n * n
void print_m2(int n, double * A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%*lf", 13, _A(A, n, i, j));
        } printf("\n");
    } printf("\n");
}

void bubble_sort(int n, double * matrix) {

    double swap_el;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (matrix[j] > matrix[j + 1]) {
                swap_el = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = swap_el;
            }
        }
    }
}

int evc_11_01(int n, int max_iterations, double epsilon, double * A, double * E, double * tmp, double precision) {

    // если значение max_iterations <= 0, то алгоритм должен выполнятся до получения требуемой точности (без ограничения на число итераций).
    int steps_count = 1;
    if (max_iterations > 0) steps_count = max_iterations;

    for (int k = 0; k < steps_count; ++k) {

        // отладочная печать
        if (var_for_debug == 1) {
            printf("==============================================");
            printf("\n\t%s %d\n", "Iteration number: ", k + 1);
            printf("==============================================\n");
        }

        // заполняем первую строку матрицы R
        for (int i = 0; i < n; ++i) R(tmp, n, 0, i) = _A(A, n, 0, i);

        // заполняем массив tmp - служащиц для хранеия необходимых элементов матриц L и R для последующего их перемножения
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i - 1 == j) { // элементы 2ой главной диагонали для L
                    L(tmp, n, i, (i - 1)) = _A(A, n, i, (i - 1)) / R(tmp, n, (i - 1), (i - 1));
                }
                if (i == j || j > i) { // все элементы выше и включая саму диагональ матрицы R
                    R(tmp, n, i, j) = _A(A, n, i, j) - L(tmp, n, i, (i - 1)) * R(tmp, n, (i - 1), j);
                }
            }
        }

        // отладочная печать - печать матрицы L и R
        if (var_for_debug == 1) {
            printf("matrix L and R\n");
            print_m2(n, tmp);
        }

        double elem_L = 0;
        double elem_R = 0;

        // перемножаем L и R
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                _A(A, n, i, j) = 0;
                for (int l = 0; l < n; ++l) {
                    // определяем элемент матрицы L
                    if (l == j) elem_L = 1;
                    else if (l - 1 == j) elem_L = L(tmp, n, l, j);
                    else elem_L = 0;
                    // определяем элемент матрицы R
                    if (i > l) elem_R = 0;
                    else elem_R = R(tmp, n, i, l);

                    _A(A, n, i, j) += elem_L * elem_R;
                    // если элемент матрицы <= precision, тогда на место этого элемента ставим 0
                    if (fabs(_A(A, n, i, j)) <= precision) _A(A, n, i, j) = 0;
                }
            }
        }

        int diagonal_el_counter = 0; // счетчик диагональных элементов
        int _switch = 1;

        if (k % 2 == 0) _switch = 0;

        // сравниваем диагональные элементы матрицы A_k и A_k+1
        for (int i = 0; i < n; ++i) {
            tmp(tmp, n, (n + _switch), i) = _A(A, n, i, i);
            if (k > 0) {
                if (_switch == 0) if (fabs(tmp(tmp, n, n, i) - tmp(tmp, n, (n + 1), i)) < epsilon) diagonal_el_counter++;
                else if (fabs(tmp(tmp, n, (n + 1), i) - tmp(tmp, n, n, i)) < epsilon) diagonal_el_counter++;
            }
            // заполняем массив E диагональными элементами матрицы R*L  на k шаге
            E(E, n, 0, i) = _A(A, n, i, i);
        }

        // отладочная печать - печатаем матрицу A, полученную после перемножения R и L
        if (var_for_debug == 1) {
            printf("matrix after multiplication R * L\n");
            print_m2(n, A);
        }

        if (diagonal_el_counter == n) {
            // сортируем массив E по возрастанию
            bubble_sort(n, E);
            // 0 - работа завершена успешно
            printf("the difference of the diagonal elements k + 1 and k matrices is less than epsilon\n");
            return 0;
        }
        steps_count++; // тк max_iterations <= 0 и не достигнута необходимая точность, то увеличиваем счетчик шагов
    }
    // сортируем массив E по возрастанию
    bubble_sort(n, E);
    // 1 - метод не сходится за указанное число итераций
    return 1;
}
