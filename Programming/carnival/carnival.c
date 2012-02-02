/*TODO use the adjacency matrix to create the max table
  TODO find minimum edge
  TODO return tree without that edge
  TODO replace bubblesort
 
 * =====================================================================================
 *
 *       Filename:  carnival.c
 *
 *    Description:  Finds first and second minimal spanning trees given the edges of a graph.
 *
 *        Version:  1.0
 *        Created:  02/02/2012 01:12:49 AM
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
long N;          /* Ari8mos koryfwn */
long M;          /*  Ari8mos akmwn */
long** W;                  /* Adjacency Matrix */
long* E[3];             /*  Synolo twn Akmwn (E)  */ 
long* U;

void makeset(long i) {
     U[i] = i;
} 

long find(long i) {
     long j;
     j = i;
     while (U[j] != j)
          j = U[j];
     return j;
}

void merge(long p,  long q) {
     if (p < q) U[q] = p;
     else U[p] = q;
}

int equal(long p,  long q) {
     if (p == q) 
          return 1;
     else
          return 0;
} 

void initialize(long n) { /*  Arxikopoihsh tou U */
     long i;
     for (i = 0; i < n; i++)
          makeset(i);
} 

/*  Algori8mos tou Kruskal gia evresi MST */
void kruskal() {
     long F[N - 1][3];      /*  To MST */
     long edges = 0;      /*  akmes sto MST */
     long next = 0;      /*  Epomeni akmi pros elegxo */
     long weight = 0;     /*  minimal spanning tree weight */
     long a,  b,  c,  i,  j; /*  counter/placeholder variables */
     /*  initialize set of edges */
    
     for (i = M - 1; i > 0; i--)
          for (j = 0; j < i; j++)
               if (E[2][j] > E[2][j+1]) {
                    a = E[0][j];
                    b = E[1][j];
                    c = E[2][j];
                    E[0][j] = E[0][j + 1];
                    E[1][j] = E[1][j + 1];
                    E[2][j] = E[2][j + 1];
                    E[0][j + 1] = a;
                    E[1][j + 1] = b;
                    E[2][j + 1] = c;
               } /*  display set of edges - after sort */
          printf("\n");
     initialize(N); /*  Arxikopoihsh akmwn se adeio synolo */
     for (i = 0; i < N - 1; i++)
          for (j = 0; j < 3; j++)
               F[i][j] = -1; /*  '-1' an empty */
     while (edges < N - 1) {
          a = E[0][next];
          b = E[1][next];
          i = find(a);
          j = find(b);
          if (!equal(i, j)) {
               merge(i, j);
               F[edges][0] = E[0][next];
               F[edges][1] = E[1][next];
               F[edges][2] = E[2][next];
               edges++;
          }
          next++;
     } /*  display edges comprising minimal spanning tree */
     printf("\nMinimal Spanning Tree Edges:\n");
     printf("F = (");
     for (i = 0; i < N - 1; i++) {
          printf("(V%ld, V%ld)",  F[i][0],  F[i][1]);
          if (i < N - 2) printf(",  ");
          weight = weight + F[i][2];
     }
     printf(")\n");
     printf("Minimal Spanning Tree Weight = %lu\n",  weight);
}

int main(){
     long i, j, start, end;
     long value;
     /*  Input */
	scanf("%lu",&N); //koryfes
	scanf("%lu",&M); //akmes

     /* Allocations */
     W = (long**) malloc( N * sizeof(long*));
     for (i = 0; i < N; i++) {
            W[i] = (long*)malloc(N * sizeof(long));
     }
     U = (long*) malloc(N * sizeof(long));
     E[0]=(long*) malloc(M * sizeof(long));
     E[1]=(long*) malloc(M * sizeof(long));
     E[2]=(long*) malloc(M * sizeof(long));

          
     /* Initialization toy Adjacency Matrix */
     for (i=0;i<N;i++){
          for (j=0;j<N;j++){
               W[i][j]=0;
          }
     }

     /*   Placement of Edges in Adjacency Matrix and Edges set   */
     for (i=0;i<M;i++){
	     scanf("%lu",&start);
	     scanf("%lu",&end);
          scanf("%lu", &value);
          W[start-1][end-1] = value;
          W[end-1][start-1] = value;
          E[0][i] = (long) start-1;
          E[1][i] = (long) end-1;
          E[2][i] = value;
     }
     
     /*
     printf("\n");
     for (i = 0; i < M; i++) {
          printf(" %lu",  E[0][i]);
          printf(" %lu",  E[1][i]);
          printf(" %lu",  E[2][i]);
          printf("\n");
     }
     printf("\n");
     for (i = 0; i < N; i++) {
          for (j = 0; j < N; j++){
               printf(" %lu",  W[i][j]);
          }
          printf("\n");
     } */    // testing shit 
     kruskal();

     return 0;     
}
