#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NODE 100
#define MAX 90



typedef struct _node{
    int vertex;
    struct _node *next;
}node;

int check2[MAX_NODE];
int check1[MAX_NODE];
int stack[MAX];
int top;

node *GL[MAX_NODE];

int name2int(char c) {
    return c - 'A';
}

char int2name(int i) {
    return i + 'A';
}

void visit(int i){
        printf("%c\n",i+'A');
}


void init_stack(void) {
	top = -1;
}

int push(int t) {
	if (top >= MAX - 1) {
		printf("\n  Stack overflow!\n\n");
		return -1;
	}
	stack[++top] = t;
	return t;
}

int pop() {
	if (top < 0) {
		printf("\n  Stack underflow!\n\n");
		return -1;
	}
	return stack[top--];
}

int is_stack_empty(){
    if (top == -1)
    {
        return 1;
    }
    else return 0;
    
}

void input_adjlist(node *a[], int *V, int *E) {
    char vertex[3];
    int i, j;
    node *t;
    printf("input the num of node & edge\n");
    scanf("%d %d", V, E);
    for (i = 0; i < *V; i++) {
        a[i] = NULL;
    }

    for (j = 0; j < *E; j++) {
        printf("\ninput the two node consist of edge\n");
        scanf("%s", vertex);
        i = name2int(vertex[0]);
        t = (node *)malloc(sizeof(node));
        t->vertex = name2int(vertex[1]);
        t->next = a[i];
        a[i] = t;
        //printf("vertex: %d t->next: %d a[%d]: %d\n",t->vertex,t->next,i,a[i]);
        i = name2int(vertex[1]);
        t = (node *)malloc(sizeof(node));
        t->vertex = name2int(vertex[0]);
        t->next = a[i];
        //printf(" vertex: %d t->next: %d\n",t->vertex,t->next);
        a[i] = t;
        //printf("vertex: %c t->next: %d a[%d]: %d\n",t->vertex,t->next,i,a[i]);
    }
}


void DFS_recur_list(node *a[],int V, int i){
    node *k;
    check2[i] = 1;
    visit(i);
    for (k = a[i] ; k!=NULL; k=k->next)
    {
        if (check2[k->vertex]==0)
        {
            DFS_recur_list(a,V,k->vertex);
        }
        
    }

}



void DFS_adjlist(node *a[],int V){
    int i;
    for(i =0;i<V;i++){
        check2[i] = 0;
    }
    for ( i = 0; i < V; i++)
    {
        if (check2[i] == 0)
        {
            DFS_recur_list(a,V,i);
        }
 
    }
    
}

void print_adjlist(node *a[],int V){
    node *temp;
    for (int i = 0; i < V; i++)
    {
        printf("Vertex %c:",int2name(i));
        temp= a[i];
        //printf("a[%d] : %d\n",i,a[i]);
        while (temp !=NULL)
        {
            printf("%c ",int2name(temp->vertex));
            temp = temp->next;
        }
        printf("\n");
        
    }
    

}

void nrDFS_adjlist(node *a[],int V){
    int i,j;
    node * temp;
    init_stack();//스택을 초기화
    for ( i = 0; i < V; i++)
    {
        check1[i] = 0;//방문 여부 모두 초기화
    }
    for ( i = 0; i < V; i++)
    {
        temp =a[i];//head의 주소를 temp에 복사
        if (check1[i] ==0)//방문하지 않은 노드라면
        {
			check1[i] = 1;//방문하고,
            push(i);//그 값을 push
        }
        while (!is_stack_empty())//스택이 비어있을 때 까지 실행되는 반복문
        {
            i = pop();//쌓여있는 스택 pop;
            visit(i);
            for(temp ;temp!=NULL;temp = temp->next)//head의 주소에서 head의  next가 NULL 일때까지 반복
            if (check1[temp->vertex] == 0)//방문하지 않은 노드
            {
                check1[temp->vertex] = 1;//방문하고,
                push(temp->vertex);//push
            }  
        } 
    }
}

void adjlist_func(){
    int V,E;

    printf("==================Adjlist==================\n");
    input_adjlist(GL,&V,&E);
    print_adjlist(GL,V);
    printf("==Recursive result==\n");
    DFS_adjlist(GL,V);
    printf("==nonRecursive result==\n");
    nrDFS_adjlist(GL,V);

}
void main(){
      adjlist_func();

}