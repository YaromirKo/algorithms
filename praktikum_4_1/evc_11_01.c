// вычислительный модуль
#include "task_11_01.h"

#define _A(matrix, len, row, col) (matrix + len * row)[col]
#define L(matrix, len, row, col) (matrix + len * row)[col]
#define R(matrix, len, row, col) (matrix + len * row)[col]

int evc_11_01(int n, int max_iterations, double epsilon, double * A, double * E, double * tmp, double precision) {

    for (int k = 0; k < max_iterations; ++k) {

        for (int i = 0; i < n; ++i) _A(tmp, n, 0, i);

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j < n - 1) {
                    L(tmp, n, i, (i - 1)) = _A(A, n, i, (i - 1)) / R(tmp, n, (i - 1), (i - 1));
                }
                if (j > 0) {
                    R(tmp, n, i, j) = _A(A, n, i, j) - L(tmp, n, i, (i - 1)) * R(tmp, n, (i - 1), j);
                }
            }
        }
    }


    return 0;
}
