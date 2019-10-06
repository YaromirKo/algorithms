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

int sim_11_01(int n, double * A, double * tmp, double precision) {

    double s_k;
    double norm_a_k;
    double norm_x_k;
    double * x_k;

    for (int k = 0; k < n - 1; ++k) {

        s_k = 0;
        x_k = tmp;

        for (int j = k + 1; j < n; ++j) {
            s_k += pow(ELEM(A, n, j, k), 2);
            x_k[j] = ELEM(A, n, j, k);
        }
        
        norm_a_k = sqrt(pow(ELEM(A, n, k, (k - 1)), 2) + s_k);
        x_k[k + 1] -= norm_a_k;

        for (int j = k + 1; j < n; ++j) {
            norm_x_k += pow(ELEM(A, n, j, k), 2);
        }



    }

    





    return 0;
}
