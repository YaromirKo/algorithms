#pragma once
/// Метод Гаусса с выбором главного элемента по строке.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#pragma warning(disable : 4996)

int lss_20_01(int n, double* A, double* B, double* X, double* tmp);