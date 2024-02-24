#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

float find_maximum(float[], float);

int main(){

	
	char file_input 	[100] = {"C:\\Users\\M Aldiansyah\\Documents\\iris\\iris_datauji.txt"};
	char file_weights1	[100] = {"C:\\Users\\M Aldiansyah\\Documents\\iris\\iris_bobot1_new.txt"};
	char file_weights2	[100] = {"C:\\Users\\M Aldiansyah\\Documents\\iris\\iris_bobot2_new.txt"};

	int p = 30, nPatterns = p;
	int i = 4, nInputNodes  = i;
	int h = 8, nHiddenNodes = h;
	int j = 3, nOutputNodes = j;

	int xp, xq;
	float out0[p][i];
	float out1[p][h];
	float out2[p][j];
	float out2_[j];
	float w1[h][i];
	float w2[j][h];
	int target[p][j];
	int location, hklas;
	float maximum;
	char *label[3];
	label[0] = "setosa";
	label[1] = "versicolor";
	label[2] = "virginica";

	FILE *fpInput, *fpWeight1, *fpWeight2;

	/* ------------------- awal inisiasi --------------------- */

	/* inisiasi input */
	fpInput		=fopen(file_input, "r");
	for (p = 0; p < nPatterns; p++){
		for (i = 0; i < nInputNodes; i++){
			fscanf(fpInput,"%f", &out0[p][i]);
//			printf("%f\n",out0[p][i]);
		}
	}
	fclose(fpInput);






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


    /*--------------------- awal latih ------------------------*/

	/* pattern ke - xp */
	for (xp = 0;  xp < nPatterns;  xp++)
	{
		/*-------------------- hidden layer --------------------------*/
		for (h = 0;  h < nHiddenNodes;  h++)
		{
			float sum = 0;
			for (i = 0;  i < nInputNodes;  i++){
				sum   +=   w1[h][i]  *  out0[xp][i];
			}
			out1[xp][h]   =   1.0  /  (1.0  +  exp(-sum));
		}

		/* -------------- output layer ------------ */
		for (j = 0;  j < nOutputNodes;  j++)
		{
		   float  sum = 0;
		   for (h = 0;  h < nHiddenNodes;  h++){
			   sum  +=   w2[j][h]  *  out1[xp][h];
		   }

		   out2[xp][j]  =  1.0  /  (1.0  +  exp(-sum));
//		   printf("%f\n",out2[xp][j]);
		   out2_[j] = out2[xp][j];

		}
		location = find_maximum(out2_, 3);
		printf("%s \n", label[location]);






    }


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
