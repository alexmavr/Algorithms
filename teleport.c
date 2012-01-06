/* Teleport me BFS */
#include <stdio.h>
#include <stdlib.h>

/* Linked List pou topo8etountai oi epistimones pou kanoun overlap diadromes meta3y tous */
struct IntNode{
	unsigned int id; 
	struct IntNode* next;
};
typedef struct IntNode* List_Node;

/* FIFO Queue me dedomena ta head twn listwn me tous epistimones pou prepei na apokleistoun sti seira pou prepei na epeksergastoun 
	Apotelei to frontier tis BFS kai eksasfalizei ti swsti seira epeksergasias twn katastasewn
*/
struct QueueNode{
	List_Node value;
	struct QueueNode* next;
};
typedef struct QueueNode* Queue_Node;

struct _Queue{
	Queue_Node top;
	Queue_Node bottom;
};
typedef struct _Queue* Queue;

Queue frontier;

unsigned int N; 		// global domes dedomenwn
unsigned long* A;
unsigned long* B;
unsigned int newfails[2];

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

	/* Routines gia Queue */
void Queue_Create(void){
	frontier=(Queue) malloc(sizeof(Queue)); 
	frontier->top=malloc(sizeof(Queue_Node));
	frontier->top->value=malloc(sizeof(List_Node));
	frontier->top->value->id=0;
	frontier->top->next=NULL;
	frontier->bottom=frontier->top;
	
}

void Queue_Add(List_Node Data){
	Queue_Node newone=(Queue_Node) malloc(sizeof(Queue_Node));
	newone->next=NULL;
	newone->value=Data;
	frontier->bottom->next=newone;
	frontier->bottom=newone;
}

List_Node Queue_Get(void){
	List_Node result=frontier->top->value;
	Queue_Node grab = frontier->top;	
	frontier->top=frontier->top->next;
	free(grab);
	return result;
}

unsigned int check_without_these(List_Node fringe){ // elegxos stis A kai B gia epistimones me overlapping diadromes, xwris autous sto fringe
	unsigned int i,j,result,sum=0;
	int flag=0;
	newfails[0]=newfails[1]=0;
	for (i=0;i<N;i++){
		if (find(fringe,i)==0){
			sum++;
			flag=0;
			if (A[i]<B[i]){ // an prepei na paei mprosta o epistimonas ston diadromo
				for (j=1;((j<=N) && (j!=i));j++){ //elegxos gia overlap me ton proorismo allou epistimona
					if (find(fringe,j)==0){
						if ((B[j]>A[i]) && (B[j]<B[i])){
							newfails[0]=i;
							newfails[1]=j; // pros8iki twn epistimonwn pou kanoun overlap sto fringe
							flag=1;	
							break;
						} 		// An vre8ei overlap, stamataei o elegxos 
					}
				}
				if (flag==1) { break;} 
			}else {// an o epistimonas  eprepe na paei pisw
				for (j=1;(j<=N && j!=i);j++){
					if (find(fringe,j)==0){
						if ((B[j]<A[i]) && (B[j]>B[i])){
							newfails[0]=i;
							newfails[1]=j;
							flag=1;	
							break;
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
		printf("found something at depth %u\n",sum);
		result=sum;
	}
	return result;
}

void teleport(){		//Search kata Breadth-first (logo tis queue)
	Queue_Create();
	int found=0;
	unsigned int value;
	List_Node current;
	value=check_without_these(NULL);
	if (value!=0){
		printf("%u\n",value);
		found=1;
	}
	Queue_Add(add(NULL,newfails[0]));
	Queue_Add(add(NULL,newfails[1]));

	while ((frontier->top!=NULL) && (found==0)){
		current=Queue_Get();
		printf("now checking how it looks like without mr %u\n",current->id);
		value=check_without_these(current);
		if (value!=0){
			printf("%u\n",value);
			found=1;
		}
		Queue_Add(add(current,newfails[0]));
		Queue_Add(add(current,newfails[1]));
	}
	if (found==0){
		printf("0\n");
	}
}

int main(){
	/* Anagnosi ari8mou epistimonwn */
	scanf("%u",&N);
	/* Anagnosi twn A kai B, evresi megistou ari8mou 8alamwn */
	unsigned int i;
	newfails[0]=newfails[1]=0;
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
