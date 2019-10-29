// вычислительный модуль
#include "task_20_01.h"

#define ELEM(matrix, len, row, col) (matrix + len * row)[col]

// печать матрицы n * n
void print_m2(int n, double * A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%*lf", 13, ELEM(A, n, i, j));
        } printf("\n");
    } printf("\n");
}

void bubble_sort(int n, double * vector) {

    int check = 0;
    double swap_el;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (vector[j] > vector[j + 1]) {
                swap_el = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = swap_el;
                check = 1;
            }
        }
        if (check == 0) break;
        else check = 0;
    }
}

int evc_20_01(int n, int max_iterations, double epsilon, double * A, double * E, double * tmp, double precision) {

    // если значение max_iterations <= 0, то алгоритм должен выполнятся до получения требуемой точности (без ограничения на число итераций).
    int steps_count = 1;
    if (max_iterations > 0) steps_count = max_iterations;

    for (int k = 0; k < steps_count; ++k) {

        // отладочная печать
        if (var_for_debug == 1) {
            printf("==============================================");
            printf("\n\t%s %d\n", "Computing module\n\tIteration number: ", k + 1);
            printf("==============================================\n");
        }

        // заполняем первую строку матрицы R
        for (int i = 0; i < n; ++i) ELEM(tmp, n, 0, i) = ELEM(A, n, 0, i);

        // заполняем массив tmp - служащиц для хранеия необходимых элементов матриц L и R для последующего их перемножения
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i - 1 == j) { // элементы 2ой главной диагонали для L
                    ELEM(tmp, n, i, (i - 1)) = ELEM(A, n, i, (i - 1)) / ELEM(tmp, n, (i - 1), (i - 1));
                }
                if (i == j || j > i) { // все элементы выше и включая саму диагональ матрицы R
                    ELEM(tmp, n, i, j) = ELEM(A, n, i, j) - ELEM(tmp, n, i, (i - 1)) * ELEM(tmp, n, (i - 1), j);
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

        // перемножаем R and L
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ELEM(A, n, i, j) = 0;
                for (int l = 0; l < n; ++l) {
                    // определяем элемент матрицы L
                    if (l == j) elem_L = 1;
                    else if (l - 1 == j) elem_L = ELEM(tmp, n, l, j);
                    else elem_L = 0;
                    // определяем элемент матрицы R
                    if (i > l) elem_R = 0;
                    else elem_R = ELEM(tmp, n, i, l);

                    ELEM(A, n, i, j) += elem_L * elem_R;
                    // если элемент матрицы <= precision, тогда на место этого элемента ставим 0
                    if (fabs(ELEM(A, n, i, j)) <= precision) ELEM(A, n, i, j) = 0;
                }
            }
        }

        int diagonal_el_counter = 0; // счетчик диагональных элементов
        int _switch = 1;

        if (k % 2 == 0) _switch = 0;

        // сравниваем диагональные элементы матрицы A_k и A_k+1
        for (int i = 0; i < n; ++i) {
            ELEM(tmp, n, (n + _switch), i) = ELEM(A, n, i, i);
            if (k > 0) {
                if (_switch == 0) if (fabs(ELEM(tmp, n, n, i) - ELEM(tmp, n, (n + 1), i)) < epsilon) diagonal_el_counter++;
                else if (fabs(ELEM(tmp, n, (n + 1), i) - ELEM(tmp, n, n, i)) < epsilon) diagonal_el_counter++;
            }
            // заполняем массив E диагональными элементами матрицы R*L  на k шаге
            ELEM(E, n, 0, i) = ELEM(A, n, i, i);
        }

        // отладочная печать - печатаем матрицу A, полученную после перемножения R и L
        if (var_for_debug == 1) {
            printf("matrix after multiplication R * L\n");
            print_m2(n, A);
        }

        if (diagonal_el_counter == n) {
            if (max_iterations <= 0 || (max_iterations > 0 && (k + 1) == max_iterations)) {
                // сортируем массив E по возрастанию
                bubble_sort(n, E);
                // 0 - работа завершена успешно
                return 0;
            }
        }
        if (max_iterations <= 0) steps_count++; // тк max_iterations <= 0 и не достигнута необходимая точность, то увеличиваем счетчик шагов
    }
    // сортируем массив E по возрастанию
    bubble_sort(n, E);

    // 1 - метод не сходится за указанное число итераций
    return 1;
}
