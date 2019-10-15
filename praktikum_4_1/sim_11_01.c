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

void print_m_tmp(int n, double * tmp) {
    for (int i = n; i < 2 * n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%*lf", 13, ELEM(tmp, n, i, j));
        } printf("\n");
    } printf("\n");
}

int sim_11_01(int n, double * A, double * tmp, double precision) {

    double s_k;
    double norm_a_k;
    double norm_x_k;

    for (int k = 0; k < n - 1; ++k) {

        if (var_for_debug == 1) {
            printf("==============================================");
            printf("\n\t%s %d\n", "Iteration number: ", k + 1);
            printf("==============================================\n");
        }

        s_k = 0;

        for (int j = k + 2; j < n; ++j) {
            s_k += pow(ELEM(A, n, j, k), 2);
            ELEM(tmp, n, (2 * n), j) = ELEM(A, n, j, k);
        }

        norm_a_k = sqrt(pow(ELEM(A, n, (k + 1), k), 2) + s_k);

        if (var_for_debug == 1) printf("norm a_k = %lf\n", norm_a_k);

        ELEM(tmp, n, (2 * n), (k + 1)) = ELEM(A, n, (k + 1), k) - norm_a_k;

        if (var_for_debug == 1) {
            printf("vector x_k: ");
            for (int j = 0; j < n; ++j) {
                printf(" %lf ", ELEM(tmp, n, (2 * n), j));
            } printf("\n");
        }

        norm_x_k = sqrt(pow(ELEM(tmp, n, (2 * n), (k + 1)), 2) + s_k);

        if (var_for_debug == 1) printf("norm x_k = %lf\n", norm_x_k);

        for (int j = k + 1; j < n; ++j) {
            ELEM(tmp, n, (2 * n), j) /= norm_x_k;
        }

        if (var_for_debug == 1) {
            printf("vector x_k: ");
            for (int j = 0; j < n; ++j) {
                printf(" %lf ", ELEM(tmp, n, (2 * n), j));
            } printf("\n");
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j && i <= k && j <= k) ELEM(tmp, n, i, j) = 1;
                else if (i > k && j > k) {
                    if (i == j) ELEM(tmp, n, i, j) = 1 - 2 * ELEM(tmp, n, (2 * n), i) * ELEM(tmp, n, (2 * n), j);
                    else ELEM(tmp, n, i, j) = 2 * ELEM(tmp, n, (2 * n), i) * ELEM(tmp, n, (2 * n), j);
                }
                else ELEM(tmp, n, i, j) = 0;
            }
        }

        if (var_for_debug == 1) {
            printf("matrix U\n");
            print_m(n, tmp);
            printf("matrix A\n");
            print_m(n, A);
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ELEM(tmp, n, (n + i), j) = 0;
                for (int l = 0; l < n; ++l) {
                    ELEM(tmp, n, (n + i), j) += ELEM(tmp, n, i, l) * ELEM(A, n, l, j);
                }
            }
        }

        if (var_for_debug == 1) {
            printf("U * A\n");
            print_m_tmp(n, tmp);
            printf("matrix A in tmp\n");
            print_m_tmp(n, tmp);
            printf("matrix U\n");
            print_m(n, tmp);
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ELEM(A, n, i, j) = 0;
                for (int l = 0; l < n; ++l) {
                    ELEM(A, n, i, j) += ELEM(tmp, n, (n + i), l) * ELEM(tmp, n, l, j);
                }
            }
        }

        if (var_for_debug == 1) {
            printf("A * U\n");
            print_m(n, A);
        }

    }
    return 0;
}
