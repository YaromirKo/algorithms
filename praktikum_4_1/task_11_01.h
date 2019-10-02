#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

int var_for_debug = 0;
int var_for_errors = 0;

int sim_11_01(int n, double * A, double * tmp, double precision);
int evc_11_01(int n, int max_iterations, double epsilon, double* A, double* E, double* tmp, double precision);