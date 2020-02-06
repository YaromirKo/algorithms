#pragma warning(disable : 4996)
#include "task.h"
#include "chart.h"



size_t odu_memsize(int n) {
	return (size_t)(double*)malloc(n * sizeof(double));
}

double correct_answer(double x) {
	//return (x*x*x);
	return (exp(x)/(exp(x)+1));
}

// { z=y'
// { z'=f(x)-p(x)*y'-q(x)*y

int main() {
	int j = 0;
	int n = 0;
	int value = 0;
	double a = 0, b = 0, f0 = 0, f1 = 0, e = 0;
	double *f = NULL;
	double *temp = NULL;
	FILE *infile, *outfile;

	if ((infile = fopen("datin.txt", "r")) == NULL) {
		printf("Cannot open infile");
		getchar();
		return -2;
	}

	if ((outfile = fopen("datout.txt", "w")) == NULL) {
		printf("Cannot open outfile");
		getchar();
		return -3;
	}

	fscanf(infile, "%lf", &a);
	fscanf(infile, "%lf", &b);
	fscanf(infile, "%lf", &f0);
	fscanf(infile, "%lf", &f1);
	fscanf(infile, "%lf", &e);
	fscanf(infile, "%d", &n);

	f = (double*)odu_memsize(5000);
	temp = (double*)odu_memsize(5000);
	
	if (f == NULL) {
		printf("Cannot allocate memory");
		return -4;
	}

	if (temp == NULL) {
		printf("Cannot allocate memory");
		return -4;
	}

	value = odu(a, b, f0, f1, e, f,temp,n);

    outfile = fopen("istina.txt", "w");
    for (j = 0; j < value; j++) {
        if (j % (value / n) == 0) {
            fprintf(outfile, "%lf %1.9f\n", a + j*(b - a) / value, correct_answer(a + j*(b - a) / value));
        }
    }


    fclose(outfile);
	fprintf(outfile, "%d\n", n);
	
	for (j = 0; j < value; j++) {
		if (j%(value / n) == 0) {
			fprintf(outfile, "%lf %1.9f %1.9f %1.9f\n", a+j*(b-a)/value,f[j],correct_answer(a + j*(b - a) / value), correct_answer(a + j*(b - a) / value)-f[j]);
		}
	}

    print_line();

	fclose(infile);
	fclose(outfile);
	free(f);
	free(temp);

	return 0;
}

