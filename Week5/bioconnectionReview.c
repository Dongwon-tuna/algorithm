#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 100
#define MAX 100


int char2int(char c){
    return c - 'A';
}

char int2char(int i){
    return i + 'A';
}

//======================================for stack(this is for DFS)
int stack[MAX];
int top;

int check[MAX_NODE];

void init_stack(){
    top = -1;
}

int put(int k){
    if (top >=MAX-1)
    {
        printf("stack overflow\n");
        return -1;
    }
    stack[++top] = k;//선위연산 통하여 탑 올리고 값을 복사
    return stack[top];
    
}

int pop(){
    if (top <0)
    {
        printf("stack underflow\n");
        return -1;
    }
    int a = stack[top--];
    return a;//후위연산을 통해 리턴해주고 탑을 내림
}

//=======================================for adjlist
typedef struct _node{
    int vertex;
    struct _node *next;
}node;

node *GL[MAX_NODE];



void adjlist(node *a[],int E){
    for (int i = 0; i < E; i++)
    {
        a[i] = NULL;
    }
    node *t;
    int j,k;
    char nodeInput[3];
    for (int i = 0; i < E; i++)
    {
        printf("Input the connection(AB): ");
        scanf("%s",&nodeInput);
        j = char2int(nodeInput[0]);
        t = (node*)malloc(sizeof(node));
        t->vertex = char2int(nodeInput[1]);
        t->next = a[j];
        a[j] = t;
        j = char2int(nodeInput[1]);
        t = (node*)malloc(sizeof(node));
        t->vertex = char2int(nodeInput[0]);
        t->next = a[j];
        a[j] = t;
    }
    
    
}

void adjlistPrint(node *a[],int V){
    printf("hello\n");
    for (int i = 0; i < V; i++)
    {
        printf("%c: ",int2char(i));
        //printf("%c",in(a[i]->vertex));
        while (a[i] !=NULL)
        {
            printf("%c ",int2char(a[i]->vertex));
            a[i] = a[i]->next;
        }
        printf("\n");
        
    }
    
}
//=======================================DFS

void visit(int k){
    printf("%d\n",k);
}


void DFS_recur_list(node *a[],int V, int i){
    node *k;
    check[i] = 1;
    printf("%d\n",i);
    for (k = a[i] ; k!=NULL; k=k->next)
    {
        if (check[k->vertex]==0)
        {
            DFS_recur_list(a,V,k->vertex);
        }
        
    }

}



void DFS_adjlist(node *a[],int V){
    int i;
    for(i =0;i<V;i++){
        check[i] = 0;
    }
    for ( i = 0; i < V; i++)
    {
        if (check[i] == 0)
        {
            DFS_recur_list(a,V,i);
        }
 
    }
    
}



void main(){
    int nodeNum, edgeNum;
    printf("Input node num & edge num: ");
    scanf("%d %d",&nodeNum, &edgeNum);
    adjlist(GL,edgeNum);
    adjlistPrint(GL,nodeNum);
    printf("DFS\n");
    DFS_adjlist(GL,nodeNum);
}