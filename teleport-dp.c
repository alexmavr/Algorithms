/* Teleport me DP */
#include <stdio.h>
#include <stdlib.h>

unsigned int N; 		// global domes dedomenwn
unsigned long* A;
unsigned long* B;

void teleport(){		
	unsigned int i,j,current_max,total_max=0;	
	unsigned long int best[N+1];
	for (i=1;i<=N;i++){
		current_max=0;
		for (j=i-1;j>0;j--){
			if ((B[i]>=B[j]) && (best[j]>current_max)){
				current_max=best[j];
			}
		}
		best[i]=current_max+1;
		if (total_max<best[i]){
			total_max=best[i];
		}
	}
	printf("%u\n",total_max);
}
	/*	Synartiseis gia QuickSort		*/
void swap(long unsigned int *a, long unsigned int *b)
{
	long unsigned int t=*a; *a=*b; *b=t;
}
unsigned int partitionA(unsigned int l, unsigned long int r) {
	unsigned long int pivot;
	unsigned int i, j;
	pivot = A[l];
	i = l;
	j = r + 1;
	while (1) {
		do++i;
		while (A[i] <= pivot && i <= r);
		do--j;
		while (A[j] > pivot);
		if (i >= j) break;
		swap(&A[i],&A[j]);
		swap(&B[i],&B[j]);

	}
	swap(&A[l],&A[j]);
	swap(&B[l],&B[j]);
	return j;
}
unsigned int partitionB(unsigned int l, unsigned long int r) {
	unsigned long int pivot;
	unsigned int i, j;
	pivot = B[l];
	i = l;
	j = r + 1;
	while (1) {
		do++i;
		while (B[i] <= pivot && i <= r);
		do--j;
		while (B[j] > pivot);
		if (i >= j) break;
		swap(&B[i],&B[j]);

	}
	swap(&B[l],&B[j]);
	return j;
}
void quickSortB(unsigned int l, unsigned int r) {
	unsigned int j;
	if (l < r) {
		// divide and conquer
		j = partitionB(l, r);
		quickSortB(l, j - 1);
		quickSortB(j + 1, r);
	}
}
void quickSortA(unsigned int l, unsigned int r) {
	unsigned int j;
	if (l < r) {
		// divide and conquer
		j = partitionA(l, r);
		quickSortA(l, j - 1);
		quickSortA(j + 1, r);
	}
}

void fixsort(){
	unsigned int i,start=1,end=1;
	for (i=2;i<=N;i++){
		if (A[i]==A[start]){
			end=i;
		} else{
			quickSortB(start,end);
			start=end=i;
		}
	}
	if (start!=end){
		quickSortB(start,end);
	}
}
int main(){
	/* Anagnosi ari8mou epistimonwn */
	scanf("%u",&N);
	/* Anagnosi twn A kai B, evresi megistou ari8mou 8alamwn */
	unsigned int i;
	A = (unsigned long *) malloc((N+1)*sizeof(unsigned long)); // Arxikoi proorismoi epistimonwn
	B = (unsigned long *) malloc((N+1)*sizeof(unsigned long)); // Telikoi proorismoi epistimonwn
	for (i=1;i<=N;i++){
		scanf("%lu",&A[i]);
		scanf("%lu",&B[i]);
	}
	quickSortA(1,N);
	fixsort();
	teleport();
	return 0;
}
