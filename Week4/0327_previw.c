#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 100
#define MAX 90

int stack[MAX];
int top =-1;

void init_stack(void){
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

int pop(){
    if(top<0){
        printf("Stack underflow!\n");
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


int check[MAX_NODE];
int check2[MAX_NODE];


int GM[MAX_NODE][MAX_NODE];

int name2int(char c) {
    return c - 'A';
}

char int2name(int i) {
    return i + 'A';
}

void input_adjmatrix(int a[][MAX_NODE], int *V, int *E) {
    char vertex[3];
    int i, j, k;
    printf("node num, edge: ");
    scanf("%d %d", V, E);
    for (i = 0; i < *V; i++) {
        for (j = 0; j < *V; j++) {
            a[i][j] = 0; // 각 요소를 0으로 초기화
        }
    }
    for (i = 0; i < *V; i++) {
        a[i][i] = 1;
    }
    for (k = 0; k < *E; k++) {
        printf("\nedge between node(ex: AB): ");
        scanf("%s", vertex);
        i = name2int(vertex[0]);
        j = name2int(vertex[1]);
        a[i][j] = 1;
        a[j][i] = 1;
    }
}

void print_adjmatrix(int a[][MAX_NODE], int V) {
    int i, j;
    printf("\nMatrix:\n");
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void visit(int i){
        printf("%c\n",i+'A');
}

void DFS_recur_marix(int a[][MAX_NODE],int V,int i){//i starting point, V node num
    int j;
    check[i]=1;
    visit(i);//print해줌
    for ( j = 0; j < V; j++)//노드를 한바퀴 탐색
    {
        if(a[i][j]!=0){
            if(check[j] == 0){//방문 안한 노드이면>terminate con?
                DFS_recur_marix(a,V,j);//그 것으로 재귀함수 반복
            }
        }
    }
    
}


void DFS_adjmarix(int a[][MAX_NODE],int V){//동떨어진 루프 확인하는 함수
    int i;
    for ( i = 0; i < V; i++)
    {
        check[i] =0;
    }
    for ( i = 0; i < V; i++)
    {
        if(check[i] == 0){
            DFS_recur_marix(a,V,i);
        }
    }

}

void nrDFS_adjmarix(int a[][MAX_NODE],int V){
    int i,j;
    init_stack();
    for ( i = 0; i < V; i++)
    {
        check[i] = 0;
    }
    for ( i = 0; i < V; i++)
    {
        if (check[i]==0)
        {
            push(i);
            check[i] = 1;
            while (!is_stack_empty())
            {
                i = pop();
                visit(i);
                for ( j = 0; j < V; j++)
                {
                    if (a[i][j] !=0)
                    {
                        if (check[j]==0)
                        {
                            push(j);
                            check[j] = 1;
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
    }
    
    
}

typedef struct _node{
    int vertex;//vertex 변수는 노드의 값, 즉 노드가 표현하는 정점(vertex)을 나타냅니다.
    struct _node *next;//둘째, next 포인터는 다음 노드를 가리키는 포인터입니다. 이는 그래프의 간선을 표현하는 역할을 합니다.
}node;



node *GL[MAX_NODE];

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



void adjmatrix_func(){
    printf("==================Adjmatrix==================\n");
    int V, E;
    input_adjmatrix(GM, &V, &E);
    print_adjmatrix(GM, V);
    printf("==Recursive result==\n");
    //DFS_recur_marix(GM,V,0);
    DFS_adjmarix(GM,V);
    printf("==nonRecursive result==\n");
    nrDFS_adjmarix(GM,V);

}

void adjlist_func(){
    int V,E;

    printf("==================Adjlist==================\n");
    input_adjlist(GL,&V,&E);
    print_adjlist(GL,V);
    printf("==Recursive result==\n");
    //DFS_recur_list(GL,V,0);
    DFS_adjlist(GL,V);

}

int main() {
    //adjmatrix_func();
    adjlist_func();
    //========================IFDEF 사용법 익혀보기..
    return 0;
}