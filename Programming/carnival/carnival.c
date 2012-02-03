/*
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
long** W;        /* Adjacency Matrix */
long* E[4];      /*  Synolo twn Akmwn (E)  */ 
long* U;         /* Union Set   */
long* E_M;       /* Edge Maximums */

	/*	Synartiseis gia QuickSort		*/
void swap(long  int *a, long  int *b)
{
	long  int t=*a; *a=*b; *b=t;
}
long partition( long l,  long r) {
     long int pivot;
     long int i, j;
     long k = (l+r)/2;
     swap(&E[0][l],&E[0][k]);
     swap(&E[1][l],&E[1][k]);
     swap(&E[2][l],&E[2][k]);
     swap(&E[3][l],&E[3][k]);

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
		swap(&E[3][i],&E[3][j]);
	}
     swap(&E[0][l],&E[0][j]);
     swap(&E[1][l],&E[1][j]);
     swap(&E[2][l],&E[2][j]);
     swap(&E[3][l],&E[3][j]);
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
long find(long i) { // Kai sympti3i monopatiou
     long j;
     j = i;
     if (U[j] != j){
          U[j]=find(U[j]);
     }
     return U[j];
}
void unite(long x, long y, long weight) 
{

     long x_root, y_root;
     if (x==y) return;
     x_root=find(x);
     y_root=find(y);
     U[y_root]=x;       
     if (E_M[x_root]<weight){
          E_M[x_root]=weight;

     }
     if (E_M[y]<weight){
          E_M[y]=weight;
     }
}

void initialize(long n) { /*  Arxikopoihsh tou U kai tou E_M */
     long i;
     for (i = 0; i < n; i++){
          U[i]=i;
          E_M[i]=0;
     }
} 

/*  Algori8mos tou Kruskal gia evresi MST */
unsigned long long kruskal() {
     long edges = 0;      /*  akmes sto MST */
     long next = 0;      /*  Epomeni akmi pros elegxo */
     unsigned long long weight = 0;     /*  minimal spanning tree weight */
     long a,  b, i,  j; /*  counter/placeholder variables */
        
     quicksort(0, M-1);    /*   sort se au3ousa seira tis akmes */

     initialize(N); /*  Arxikopoihsh akmwn se adeio synolo */
     while ((edges < N - 1) &&(next<M) ) {
          a = E[0][next];
          b = E[1][next];
          i = find(a);
          j = find(b);
          if (i!=j) {
               unite(i, j, E[2][next]);
               weight += E[2][next];
               E[3][next]=1;  // flag oti anikei sto MST
               edges++;
          }
          next++;
     } 
     return weight;
}

long long min(long long a, long long b){
     if (a < b){
               return a;
     }else{
               return b;
     }
}

long long second_mst(unsigned long long mst){
     long i;
     long long lemax=0;
     long long lemin=-1;
     for (i=0;i<M;i++){
          if (E[3][i]!=1){    // If not in mst
                if (E_M[E[0][i]] >= E_M[E[1][i]]){
                     lemax=E_M[E[0][i]];
                } else{
                     lemax=E_M[E[1][i]];
                }
                if (lemin==-1){
                          lemin=E[2][i]-lemax;
                }else{
                     lemin=min(lemin, (E[2][i]-lemax));
                }
                     
          }
     }
     return lemin;
}

int main(){
     long i, start, end;
     long value;
     /*  Input */
	scanf("%lu",&N); //koryfes
	scanf("%lu",&M); //akmes

     /* Allocations */
     U = (long*) malloc(N * sizeof(long));
     E_M = (long*) malloc(N * sizeof(long));
     E[0]=(long*) malloc(M * sizeof(long));
     E[1]=(long*) malloc(M * sizeof(long));
     E[2]=(long*) malloc(M * sizeof(long));
     E[3]=(long*) malloc(M * sizeof(long));
          
     /*   Placement of Edges in Adjacency Matrix and Edges set   */
     for (i=0;i<M;i++){
	     scanf("%ld",&start);
	     scanf("%ld",&end);
          scanf("%ld", &value);
          E[0][i] = start-1;
          E[1][i] = end-1;
          E[2][i] = value;
          E[3][i] = 0;
     }
     
     unsigned long long mst=kruskal();
     long long mst2=second_mst(mst);
     printf("%llu %llu\n", mst, mst+mst2);
     return 0;     
}
