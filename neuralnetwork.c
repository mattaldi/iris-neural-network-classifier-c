#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

/*
	neuralnetwork.c
	train the data use this code, for classification 

	original code:
		Neural Network PC Tools by Russell C. Eberhart and Roy W. Dobbins

	edited by: 
		Muhamad Aldiansyah
	
	This original code is taken from:
	Neural Network PC Tools by Russell C. Eberhart and Roy W. Dobbins
	
	The implementation from the book is using command line interface (cli).
	I edited the code so it can running in IDE like Eclipse for C.
	
		
*/


int main(){


	/* setting neural network */
	int nIterations = 1500;
	int p = 120, nPatterns = p;
	int i = 4, nInputNodes  = i;
	int h = 8, nHiddenNodes = h;
	int j = 3, nOutputNodes = j;
	float eta 	= 0.04;
	float alpha = 0.02;
	char file_input 	[100] = {"C:\\Users\\M Aldiansyah\\Documents\\iris\\iris_datalatih.txt"};
	char file_target 	[100] = {"C:\\Users\\M Aldiansyah\\Documents\\iris\\iris_target_latih.txt"};
	char file_weights1	[100] = {"C:\\Users\\M Aldiansyah\\Documents\\iris\\iris_bobot1.txt"};
	char file_weights2	[100] = {"C:\\Users\\M Aldiansyah\\Documents\\iris\\iris_bobot2.txt"};
	/* akhir setting neural net */



	int xp, xq;
	float out0[p][i];
	float out1[p][h];
	float out2[p][j];
	float w1[h][i];
	float delw1[h][i];
	float w2[j][h];
	float delw2[j][h];
	float delta2[p][j];
	float delta1[p][h];
	int target[p][j];

	FILE *fpInput, *fpWeight1, *fpWeight2, *fpTarget;

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




	/* inisiasi target */
	fpTarget	=fopen(file_target, "r");
	for (p = 0; p < nPatterns; p++){
		for (j = 0; j < nOutputNodes; j++){
			fscanf(fpTarget,"%d", &target[p][j]);
		}
	}
	fclose(fpTarget);


	/* inisiasi bobot1 */
	fpWeight1=fopen(file_weights1, "r");
	for (h = 0; h < nHiddenNodes; h++){
		for (i = 0; i < nInputNodes; i++){
			fscanf(fpWeight1,"%f", &w1[h][i]);
	        delw1[h][i] = 0.0;
		}
	}
	fclose(fpWeight1);

	/* inisiasi bobot2 */
	fpWeight2=fopen(file_weights2, "r");
	for (j = 0; j < nOutputNodes; j++){
		for (h = 0; h < nHiddenNodes; h++){
			fscanf(fpWeight2,"%f", &w2[j][h]);
	        delw2[j][h] = 0.0;
		}
	}
	fclose(fpWeight2);


	/* -------------------- akhir inisiasi --------------------- */


    /*--------------------- awal latih ------------------------*/

    for (xq = 0;  xq < nIterations;  xq++)
    {
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
            }

            /*-------------------- delta output --------------------------*/
            for (j = 0;  j < nOutputNodes;  j++){
            	delta2[xp][j]   =   (target[xp][j] - out2[xp][j])  * out2[xp][j]   *   (1.0 - out2[xp][j]);
            }

            /*-------------------- delta hidden --------------------------*/
            for (h = 0;  h < nHiddenNodes;  h++)
            {
               float  sum = 0.0;

               for (j = 0;  j < nOutputNodes;  j++){
                   sum  +=  delta2[xp][j] * w2[j][h];
               }
               delta1[xp][h]  =  sum  *  out1[xp][h]  *  (1.0 - out1[xp][h]);
            }
    	}

        for (j = 0;  j < nOutputNodes;  j++)
        {
           float  dw;
           float  sum = 0.0;

           for (p = 0;  p < nPatterns;  p++){
               sum  +=  delta2[p][j];
           }

           dw   =   eta * sum  +  alpha * delw2[j][nHiddenNodes];
           w2[j][nHiddenNodes]   +=   dw;
           delw2[j][nHiddenNodes] =   dw;

           for (h = 0;  h < nHiddenNodes;  h++)
           {
              float  sum = 0.0;

              for (p = 0;  p < nPatterns;  p++)
                 sum  +=  delta2[p][j] * out1[p][h];

              dw           =   eta * sum  +  alpha * delw2[j][h];
              w2[j][h]     +=  dw;
              delw2[j][h]  =   dw;
           }
        }


        /*-------------------- adapt weights input:hidden -----------------*/
        for (h = 0;  h < nHiddenNodes;  h++)
        {
           float  dw;
           float  sum = 0.0;

           for (p = 0;  p < nPatterns;  p++)
              sum  +=  delta1[p][h];

           dw   =   eta * sum  +  alpha * delw1[h][nInputNodes];
           w1[h][nInputNodes]   +=   dw;
           delw1[h][nInputNodes] =   dw;

           for (i = 0;  i < nInputNodes;  i++)
           {
              float  sum = 0.0;

              for (p = 0;  p < nPatterns;  p++){
            	  sum  +=  delta1[p][h] * out0[p][i];
              }

              dw           =   eta * sum  +  alpha * delw1[h][i];
              w1[h][i]     +=  dw;
              delw1[h][i]  =   dw;

           }
        }

    }
    /* --------------- akhir latih -----------------------------*/


    /* hasil update bobot pilih salah satu, yang tidak dipilih ditulis sebagai comment  */

    /*  bobot lapis 1 */
	for (h = 0; h < nHiddenNodes; h++){
		for (i = 0; i < nInputNodes; i++){
			printf("%f\n", w1[h][i]);
		}
	}

	/* bobot lapis 2 */
//	for (j = 0; j < nOutputNodes; j++){
//		for (h = 0; h < nHiddenNodes; h++){
//			printf("%f \n", w2[j][h]);
//		}
//	}


	return 0;
}
