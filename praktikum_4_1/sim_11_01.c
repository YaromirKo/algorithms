// модуль упрощения
#include "task_11_01.h"

#define ELEM(matrix, len, row, col) (matrix + len * row)[col]

void print_m(int n, double * A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%*lf", 13, ELEM(A, n, i, j));
        } printf("\n");
    } printf("\n");
}

void mul_m(int n, double * A, double * B, double * C) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int l = 0; l < n; ++l) {
                ELEM(C, n, i, j) += ELEM(A, n, i, l) * ELEM(B, n, l, j);
            }
        }
    }
}

int sim_11_01(int n, double * A, double * tmp, double precision) {

    double s_k;
    double norm_a_k;
    double norm_x_k;

    for (int k = 0; k < n - 1; ++k) {

        s_k = 0;

        for (int j = k + 1; j < n; ++j) {
            s_k += pow(ELEM(A, n, j, k), 2);
            ELEM(tmp, n, (n - 1), j) = ELEM(A, n, j, k);
        }

        norm_a_k = sqrt(pow(ELEM(A, n, (k + 1), k), 2) + s_k);
        ELEM(tmp, n, (n - 1), k + 1) -= norm_a_k;
        norm_x_k = sqrt(pow(ELEM(tmp, n, (n - 1), k + 1), 2) + s_k);

        for (int j = k + 1; j < n; ++j) {
            ELEM(tmp, n, (n - 1), j) /= norm_x_k;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i <= k && j <= k) ELEM(tmp, n, i, j) = 1;
                else if (i >= k + 1 && j >= k + 1) ELEM(tmp, n, i, j) = 1 - ELEM(tmp, n, (n - 1), i) * ELEM(tmp, n, (n - 1), j);
                else ELEM(tmp, n, i, j) = 0;
            }
        }

        mul_m(n, tmp, A, A);
        mul_m(n, A, tmp, A);

    }
    return 0;
}
