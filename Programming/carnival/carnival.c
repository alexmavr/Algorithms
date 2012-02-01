/*
 * =====================================================================================
 *
 *       Filename:  carnival.c
 *
 *    Description:  Problem 2, Set 3,  Algorithms class
 *
 *        Version:  0.1
 *        Created:  02/01/2012 08:37:39 PM
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

unsigned long E, V;
unsigned long a[2000][2000]; // Adjacency Matrix

void printArray(){
     int i, j;
     for(i=0;i<V;i++)
     {
          for(j=0;j<V;j++)
          {
               printf("%lu\t", a[i][j]);
          }
          printf("\n");
     }
}

void union_ij(int i, int j, int p[]){
     if(j > i)
          p[j] = i;
     else
          p[i] = j;
}

int root(int v, int p[]){

     while(p[v] != v)
     {v = p[v];}

     return v;
}

void kruskal(unsigned long minimum){
     int i, j, u, v, p[2000], t[2000][2];
     int counter=0;
     int k=0;
     unsigned long min, sum=0;
     for (i = 0; i < V; i++){
          p[i] = i;
     }  
     while (counter < V){
          min = minimum;
          for (i = 0; i < V; i++){
               for (j = 0;j < V; j++){
                    if (a[i][j] < min){
                         min = a[i][j];
                         u = i;
                         v = j;
                    }
               }
          }
          if (min != minimum){
               i = p[u];
               j = p[v];
               if (i != j)
               {
                    t[k][0] = root(u, p);
                    t[k][1] = root(v, p);
                    k++;
                    sum += min;
                    union_ij(i, j, p);
               }
               a[u][v] = a[v][u] = minimum;

          }counter +=1;
     }   
     if (counter != V){
          printf("spanning tree not exist\n");
     }
     if (counter == V){
          printf("Adges Spanning tree is\n");
          for (k = 0; k < V-1 ; k++){
               printf(" %d -> %d ", t[k][0], t[k][1]);
          }
          printf("\nst = %lu \n", sum);
     }  
}

unsigned long carnival(){
     return 1;     
}

int main(){
     int i, j, start, end;
     unsigned long value;
     /*  Input */
	scanf("%lu",&V);
	scanf("%lu",&E);
          
     for (i=0;i<V;i++){
          for (j=0;j<V;j++){
               a[i][j]=0;
          }
     }

     /*   Placement of Edges in array        */
     for (i=0;i<E;i++){
	     scanf("%d",&start);
	     scanf("%d",&end);
          scanf("%lu", &value);
          a[start-1][end-1]=value;
          a[end-1][start-1]=value;
     }

     
     kruskal(value); 

     // TODO test thoroughly
     // TODO debug kruskal
     // TODO use the adjacency matrix to create the max table
     // TODO find minimum edge
     // TODO return tree without that edge

/*     printf("%lu", carnival());
     printf("enter the number of vertices\n");
     scanf("%d", &n);
     AdjacencyMatrix(n);
     kruskal(n);
 */

     return 0;     
}
