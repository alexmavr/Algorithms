/*
 * =====================================================================================
 *
 *       Filename:  headquarters.c
 *
 *    Description:  Finds number of shortest s-t paths in a directed graph of k-levels
 *                  With identical level substructure
 *
 *        Version:  1.0
 *        Created:  02/02/2012 08:59:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alex Mavrogiannis (afein), nalfemp@gmail.com
 *   Organization:  National Technical University of Athens
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

#define MAX_MOD 100000007     // To teliko apotelesma emfanizetai se mod me auton ton ari8mo

unsigned long N;     // Global Pli8os koryfwn

/*  Pollaplasiasmos 2 Tetragonikwn Pinakwn NxN kai to apotelesma ston prwto */
void matrix_mul(unsigned long long **matrix1, unsigned long long int **matrix2)
{
     unsigned int i, j, k;
     unsigned long long int **temp;
     unsigned long long int buffer;

     /*  Allocation enos prosorinou pinaka pou 8a krataei to apotelesma */
     temp = (unsigned long long**) malloc( N * sizeof(unsigned long long*));
     for (i = 0; i < N; i++) {
            temp[i] = (unsigned long long*)malloc(N * sizeof(unsigned long long));
     }

     /*  Ektelesi pollaplasiasmou */
     for (i=0;i<N;i++){
          for (j=0;j<N;j++){
               buffer = 0;    // Ypologismos stoixeiou (i, j)
               for( k = 0 ; k < N ; k ++)
                    buffer += matrix1[i][k]*matrix2[k][j];
               temp[i][j] = buffer % MAX_MOD;             // To apotelesma ston temp se morfi mod 10^8+7
          }
     }

     /*  Metafora tou pinaka apotelesmatos ston 1o apo tous dyo pinakes */
     for (i=0;i<N;i++){
          for (j=0;j<N;j++ ){
               matrix1[i][j]=temp[i][j];
          }
     }
     free(temp);
}

/*  O ari8mos twn monopatiwn mporei na vre8ei pollaplasiazontas ton adjacency matrix me ton eauto tou analoga 
 *  me ton ari8mo twn epipedwn
 *  */
unsigned long long headquarters(unsigned long long **start, int k, int s, int t)
{
     unsigned long long int **temp, **result;
     unsigned int i, j;
     int k_bits=4*sizeof(unsigned long);
     temp = start;
     k--; // Den yparxei prwto epipedo 

     /*  Orismos kai arxikopoihsh apotelesmatos ws diagonios pinakas */
     result = (unsigned long long**) malloc(N * sizeof(unsigned long long*));
     for (i = 0; i < N; i++) {
            result[i] = (unsigned long long*) malloc(N * sizeof(unsigned long long));
            for (j=0;j<N;j++){
                 if (i!=j){
                      result[i][j]=0;
                 }  else {
                      result[i][j]=1;
                 }
            }
     }
     /*  Pollaplasiasmos olwn twn start^(2^i) gia ta i gia ta opoia i diadiki morfi twn epipedwn */
     j=0;
     for (i=0;i<k_bits;++i){
          if ( (k & (1 << i)) << (k_bits-i) ){       // An to i-osto lsb tou k einai 1 
               while (j < i){
                    matrix_mul(temp, temp);            // Evresi start^(2^i)
                    j++;
               }
               matrix_mul(result, temp);                  // Kai pollaplasiasmos me to apotelesma
          }
     }
     return result[s-1][t-1];               
}

int main()
{
     unsigned long long **adj_level;           // adjacency matrix gia ka8e epipedo
     unsigned long k, M, s, t, from, to, i, j;

     /* Input Constants */
     scanf("%lu", &k);
     scanf("%lu", &N);
     scanf("%lu", &M);
     scanf("%lu", &s);
     scanf("%lu", &t);

     /* Allocation and initialization of the Adjacency Matrix */
     adj_level = (unsigned long long**) malloc( N * sizeof(unsigned long long*));
     for (i = 0; i < N; i++) {
            adj_level[i] = (unsigned long long*)malloc(N * sizeof(unsigned long long));
            for (j = 0 ; j < N ;j++){
                 adj_level[i][j]=0;  
            }
     }
     
     /*  Input Edges */
     for (i=0;i<M;i++){
          scanf("%lu %lu", &from, &to);
          adj_level[from-1][to-1] = 1;
     }
     printf("%llu\n", headquarters(adj_level, k, s, t));
     return 0;
}
