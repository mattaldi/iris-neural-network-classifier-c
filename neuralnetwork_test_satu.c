#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

/*
	neuralnetwork_test_satu.c
	test one from all the data, for classification task.
	
	original code:
		Neural Network PC Tools by Russell C. Eberhart and Roy W. Dobbins

	edited by: 
		Muhamad Aldiansyah
	
	This original code is taken from:
	Neural Network PC Tools by Russell C. Eberhart and Roy W. Dobbins
	
	The implementation from the book is using command line interface (cli).
	I edited the code so it can running in IDE like Eclipse for C.
		
*/


float find_maximum(float[], float);

int main(){

	float out0[] = {6.8,3.2,5.9,2.3};
	char file_weights1	[100] = {"C:\\Users\\M Aldiansyah\\Documents\\iris\\iris_weights1_new2.txt"};
	char file_weights2	[100] = {"C:\\Users\\M Aldiansyah\\Documents\\iris\\iris_weights2_new2.txt"};

	int i = 4, nInputNodes  = i;
	int h = 8, nHiddenNodes = h;
	int j = 3, nOutputNodes = j;

	char *label[3];
	label[0] = "setosa";
	label[1] = "versicolor";
	label[2] = "virginica";
	float out1[h];
	float out2[j];
	float w1[h][i];
	float w2[j][h];
	int location, hklas;
	float maximum;


	FILE *fpWeight1, *fpWeight2;


	/* ------------------- awal inisiasi --------------------- */
	/* inisiasi bobot1 */
	fpWeight1=fopen(file_weights1, "r");
	for (h = 0; h < nHiddenNodes; h++){
		for (i = 0; i < nInputNodes; i++){
			fscanf(fpWeight1,"%f", &w1[h][i]);
		}
	}
	fclose(fpWeight1);

	/* inisiasi bobot2 */
	fpWeight2=fopen(file_weights2, "r");
	for (j = 0; j < nOutputNodes; j++){
		for (h = 0; h < nHiddenNodes; h++){
			fscanf(fpWeight2,"%f", &w2[j][h]);
		}
	}
	fclose(fpWeight2);
	/* -------------------- akhir inisiasi --------------------- */



	/* ------- awal hitung ------- */

	/*-------------------- hidden layer --------------------------*/
	for (h = 0;  h < nHiddenNodes;  h++)
	{
		float sum = 0;
		for (i = 0;  i < nInputNodes;  i++){
			sum   +=   w1[h][i]  *  out0[i];
		}
		out1[h]   =   1.0  /  (1.0  +  exp(-sum));
	}

	/* -------------- output layer ------------ */
	for (j = 0;  j < nOutputNodes;  j++)
	{
	   float  sum = 0;
	   for (h = 0;  h < nHiddenNodes;  h++){
		   sum  +=   w2[j][h]  *  out1[h];
	   }

	   out2[j]  =  1.0  /  (1.0  +  exp(-sum));
//	   printf("%f\n",out2[j]);

	}
	/* -------------- akhir hitung --------------- */

	/* cetak hasil */
	location = find_maximum(out2, 3);
	printf("%s \n", label[location]);


	return 0;
}


float find_maximum(float a[], float n) {
  int c, index;
  float max;

  max = a[0];
  index = 0;

  for (c = 1; c < n; c++) {
    if (a[c] > max) {
       index = c;
       max = a[c];
    }
  }

  return index;
}
