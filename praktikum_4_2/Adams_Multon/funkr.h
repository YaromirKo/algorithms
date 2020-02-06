#include <math.h>

// y''+p(x)*y'+q(x)*y=f(x)
// z=y'
// z'=f(x)-p(x)*y'-q(x)*y

double p(double x){
	//return 1/x;
	return (exp(x) / (1 + exp(x)));
}

double q(double x){
	//return -9/(x*x);
	return (-1 / ((exp(x) + 1)*(exp(x) + 1)));
}

double f(double x){
	return 0;
}

