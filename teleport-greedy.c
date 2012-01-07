/* Teleport me DP */
#include <stdio.h>
#include <stdlib.h>

/* Linked List pou topo8etountai oi epistimones pou kanoun overlap diadromes meta3y tous */
struct IntNode{
	unsigned int id; 
	struct IntNode* next;
};
typedef struct IntNode* List_Node;

/* Ka8e timi tis anadromikis synartisis syndeetai me mia lista
 pou periexei to synolo twn epistimonwn pou xreiazontai gia to megisto apotelesma */
struct ValueNode{
	unsigned int value;
	List_Node fringe;
};
typedef struct ValueNode Value;

unsigned int N; 		// global domes dedomenwn
unsigned long* A;
unsigned long* B;

unsigned int max(unsigned int a, unsigned int b){
	if (a<b){return b;}
	else{return a;}
}

	/* Routines gia Lists */
List_Node add(List_Node fringe,unsigned int i){				// Pros8iki komvou stin fringe
	List_Node newnode = (List_Node) malloc(sizeof(List_Node)); 
	newnode->id=i;
	newnode->next=fringe;
	return newnode;		
}

int find(List_Node fringe, unsigned int i){				// Evresi komvou stin fringe 
	List_Node current=fringe;
	while (current!=NULL){
		if (current->id==i){
			return 1;
		}
	else{
			current=current->next;	
		}		
	}
	return 0;
}

unsigned int check_with_these(List_Node fringe){ // elegxos stis A kai B gia epistimones me overlapping diadromes, xwris autous sto fringe
	unsigned int i,j,result,sum=0;
	int flag=0;
	for (i=1;i<=N;i++){
		if (find(fringe,i)==1){
			sum++;
			flag=0;
			if (A[i]<B[i]){ // an prepei na paei mprosta o epistimonas ston diadromo
				for (j=1;((j<=N) && (j!=i));j++){ //elegxos gia overlap me ton proorismo allou epistimona
					if (find(fringe,j)==1){
		//				printf("	in routine check between %u and %u\n",i,j);
						if (B[j]<=A[j]){ // an o allos paei aristera
							if ((B[j]<B[i]) && (A[j]>A[i])) {// 2 eidwn overlap
		//						printf("error overlap between %u, going from %lu to %lu and %u going from %lu to %lu \n",i,A[i],B[i],j,A[j],B[j]);
								flag=1;	
								break;
						 	}	// An vre8ei overlap, stamataei o elegxos 
						}else{ 	// an o allos paei de3ia
							if (((A[j]<A[i]) && (B[j]>B[i])) || ((A[j]>A[i]) && (B[j]<B[i]))){
								flag=1;	
								break;
							}
						}
					}
				}
				if (flag==1) { break;} 
			}else {// an o epistimonas  eprepe na paei pisw
				for (j=1;(j<=N && j!=i);j++){
					if (find(fringe,j)==1){
						if (B[j]>=A[j]){ // an o allos paei de3ia
							if ((B[j]>B[i]) && (A[j]<A[i])){ // 2 eidwn overlap
								flag=1;	
								break;
						 		// An vre8ei overlap, stamataei o elegxos 
							}
						}else{ 	// an o allos paei aristera
							if (((A[j]>A[i]) && (B[j]<B[i])) || ((A[j]<A[i]) && (B[j]>B[i]))){
				printf("i'm in here with route1 %lu to %lu and route 2B %lu to %lu\n",A[i],B[i],A[j],B[j]);
								flag=1;	
								break;
							}
						}
					}
				}
				if (flag==1) { break; }
			}
		}
	}
	if (flag==1){
		result=0;
	}else{
		result=sum;
	}
	return result;
}

void Show_List(List_Node list){
	if (list!=NULL){
		printf("%u ",list->id);
		Show_List(list->next);
	}
}
void teleport(){		
	unsigned int i,j,current_max;	
	unsigned int test_result;
	Value* V=malloc((N+1)*sizeof(Value));
	V[0].value=0;
	V[0].fringe=NULL;
	V[1].fringe=add(NULL,1);
	V[1].value=1;
	for (i=2;i<=N;i++){		// O(n^2)
		current_max=1;
		for (j=1;j<i;j++){
			printf("	comparing %u with %u\n",i,j);
				// Show_List(add(V[j].fringe,i));
			test_result=check_with_these(add(V[j].fringe,i));
			if (test_result>current_max){
				printf("	win! new max is %u\n",test_result);
				current_max=test_result;
				V[i].fringe=add(V[j].fringe,i);		
			}
		}
		V[i].value=current_max;
		printf("V[%u] is %u\n",i,V[i].value);
	}
	printf("%u\n",V[N].value);
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
		//printf("A[%u]=%lu\n",i,A[i]);
		//printf("B[%u]=%lu\n",i,B[i]);
	}
	teleport();
	return 0;
}
