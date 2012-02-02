/*TODO use the adjacency matrix to create the max table
  TODO find minimum edge
  TODO return tree without that edge
 
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
long* U;       /* Union */

	/*	Synartiseis gia QuickSort		*/
void swap(long  int *a, long  int *b)
{
	long  int t=*a; *a=*b; *b=t;
}
int partition( long l,  long r) {
     long int pivot;
     int i, j;
	pivot = E[2][l];
	i = l;
	j = r + 1;
	while (1) {
		do++i;
		while (E[2][i] <= pivot && i <= r);
		do--j;
		while (E[2][j] > pivot);
		if (i >= j) break;
		swap(&E[0][i],&E[0][j]);
		swap(&E[1][i],&E[1][j]);
		swap(&E[2][i],&E[2][j]);
	}
     swap(&E[0][l],&E[0][j]);
     swap(&E[1][l],&E[1][j]);
     swap(&E[2][l],&E[2][j]);
	return j;
}

void quicksort( long l,  long r) {
     long j;
	if (l < r) {
		// divide and conquer
		j = partition(l, r);
		quicksort(l, j - 1);
		quicksort(j + 1, r);
	}
}

     /*  Synartiseis gia kruskal's */
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
     long a,  b, i,  j; /*  counter/placeholder variables */
    
     quicksort(0, M);    /*   sort se au3ousa seira tis akmes */
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
