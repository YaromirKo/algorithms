#pragma warning(disable : 4996)
#include "task.h"
#include "chart.h"


size_t odu_memsize(int n) {
	return (size_t)(double*)malloc(n * sizeof(double));
}

double correct_answer(double x) {
	//return (x*x*x);
	//return 1 - x * x + 2 * x;
	return 3 * x + exp(-2 * x);
	//return (exp(x)/(exp(x)+1));
}

int main() {
	int j = 0;
	int n = 0;
	int value = 0;
	double a = 0, b = 0, f0 = 0, f1 = 0,e=0;
	double *f = NULL;
	double *temp = NULL;
	FILE *infile, *outfile;

	if ((infile = fopen("datin.txt", "r")) == NULL) {
		printf("Cannot open infile");
		return -2;
	}

	if ((outfile = fopen("datout.txt", "w")) == NULL) {
		printf("Cannot open outfile");
		return -3;
	}

	///[a;b] y[a]=f0, y[b]=f1, eps--  ��������, n--���������� �����
	fscanf(infile, "%lf", &a);
	fscanf(infile, "%lf", &b);
	fscanf(infile, "%lf", &f0);
	fscanf(infile, "%lf", &f1);
	fscanf(infile, "%lf", &e);
	fscanf(infile, "%d", &n);

	f = (double*)odu_memsize(1000000);
	temp = (double*)odu_memsize(1000000);
	
	if (f == NULL) {
		printf("Cannot allocate memory");
		return -4;
	}

	if (temp == NULL) {
		printf("Cannot allocate memory");
		return -4;
	}

	value = odu(a, b, f0, f1, e, f,temp,n);
	//fprintf(outfile, "%d\n", n);
	
	for (j = 0; j < value; j++){
		if (j%(value / n) == 0){
			fprintf(outfile, "%lf %1.9f\n", a+j*(b-a)/value,f[j]);
		}
	}
	fclose(outfile);//��������� �������� ����
	outfile = fopen("istina.txt", "w");
	for (j = 0; j < value; j++) {
		if (j % (value / n) == 0) {
			fprintf(outfile, "%1.9lf %1.9lf %1.9f\n", a + j*(b - a) / value, f[j], correct_answer(a + j*(b - a) / value));
		}
	}
	fclose(outfile);//��������� �������� ����

	fclose(infile);//��������� ������� ����
    print_line();

	free(f);//����������� ������
	free(temp);

	return 0;
}

