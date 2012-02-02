/*TODO use the adjacency matrix to create the max table
  TODO find minimum edge
  TODO return tree without that edge
  TODO replace bubblesort
  TODO dynamic allocation
 
 * =====================================================================================
 *
 *       Filename:  internets.c
 *
 *    Description:  kruskal from the internets
 *
 *        Version:  1.0
 *        Created:  02/02/2012 01:12:49 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alex Mavrogiannis (afein), nalfemp@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h> 
unsigned long N;          /* Ari8mos koryfwn */
unsigned long M;          /*  Ari8mos akmwn */
long** W;                  /* Adjacency Matrix */
long* E[3];             /*  Synolo twn Akmwn (E)  */ 
int* U;

void makeset(int i) {
     U[i] = i;
} 

int find(int i) {
     int j;
     j = i;
     while (U[j] != j)
          j = U[j];
     return j;
}

void merge(int p,  int q) {
     if (p < q) U[q] = p;
     else U[p] = q;
}

int equal(int p,  int q) {
     if (p == q) return (1);
     else
          return (0);
} 

void initialize(int n) { /*  Arxikopoihsh tou U */
     int i;
     for (i = 0; i < n; i++)
          makeset(i);
} 

void carnival() {
     int F[N - 1][3];      /*  To MST */
     int edges = 0;      /*  akmes sto MST */
     int next = 0;      /*  Epomeni akmi pros elegxo */
     int weight = 0;     /*  minimal spanning tree weight */
     int a,  b,  c,  i,  j; /*  counter/placeholder variables */
     /*  initialize set of edges */
     for (i = 0; i < M; i++) {
          for (j = 0; j < 3; j++)
               printf(" %3lu",  E[j][i]);
          printf("\n");
     }
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
     for (i = 0; i < M; i++) {
          for (j = 0; j < 3; j++)
               printf(" %3lu", E[j][i]);
          printf("\n");
     } /*  create n disjoint subsets */
     initialize(N); /*  Arxikopoihsh akmwn se adeio synolo */
     for (i = 0; i < N - 1; i++)
          for (j = 0; j < 3; j++)
               F[i][j] = -1; /*  '-1' denotes 'empty' */
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
          printf("(V%d, V%d)",  F[i][0],  F[i][1]);
          if (i < N - 2) printf(",  ");
          weight = weight + F[i][2];
     }
     printf(")\n");
     printf("Minimal Spanning Tree Weight = %d\n",  weight);
}

int main(){
     int i, j, start, end;
     unsigned long value;
     /*  Input */
	scanf("%lu",&N); //koryfes
	scanf("%lu",&M); //akmes

     /* Allocations */
     W = (long**) malloc( N * sizeof(long*));
     for (i = 0; i < N; i++) {
            W[i] = (long*)malloc(N * sizeof(long));
     }
     U = (int*) malloc(N * sizeof(int));
     E[0]=(long*) malloc(N * sizeof(long));
     E[1]=(long*) malloc(N * sizeof(long));
     E[2]=(long*) malloc(N * sizeof(long));

          
     /* Initialization toy Adjacency Matrix */
     for (i=0;i<N;i++){
          for (j=0;j<N;j++){
               W[i][j]=0;
          }
     }

     /*   Placement of Edges in array        */
     for (i=0;i<M;i++){
	     scanf("%d",&start);
	     scanf("%d",&end);
          scanf("%lu", &value);
          W[start-1][end-1] = value;
          W[end-1][start-1] = value;
          E[0][i] = start-1;
          E[1][i] = end-1;
          E[2][i] = value;
     }
     
     for (i = 0; i < N; i++) {
          for (j = 0; j < N; j++){
               printf(" %3lu",  W[i][j]);
          }
          printf("\n");
     }

     carnival();

     return 0;     
}
