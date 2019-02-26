/// Метод Гаусса с выбором главного элемента по строке.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#pragma warning(disable : 4996)


int main() {

 FILE *file;
 int a;
 float **A;
 char temp[255];
 file = fopen("test.txt", "r");
 ///fgets(arr, '\n', file);
 fscanf(file, "%d", &a);
 A = (float**)malloc(a * sizeof(float*));

 //for (int i = 0; i < a; i++) {
	//A[i] = (float*)malloc(a * sizeof(float));
	//for (int j = 0; j < a; j++) {
	// &A[i][j];
	//}
 //}
 /*int z = 0;
 while ((temp[z] = fgetc(file)) != EOF) {
	printf("%d", z);
	if (temp[z] == ' ' || temp[z] == '\n') {
	 break;
	}
	printf("%c\n", temp[z]);

	z++;

 }*/

 fgets(temp, '\n', file);
 printf("%s\n", temp);



 /*for (int z = 0; (temp[z] = fgetc(file)) != EOF; z++) {
	printf("%d", z);
	if (temp[z] == ' ' || temp[z] == '\n') {
	 break;
	}
	printf("%c\n", temp[z]);
 }*/

 
 ///int a = atoi(arr);

 printf("%d\n", a);



 system("pause");
 return 0;
}
