#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 100
#define MAX 90

typedef struct _dnode{
    int key;
    struct _dnode *prev;
    struct _dnode *next;
}dnode;

dnode *head, *tail;

int check[MAX_NODE];
int check2[MAX_NODE];


int GM[MAX_NODE][MAX_NODE];
dnode *GL[MAX_NODE];

int name2int(char c) {
    return c - 'A';
}

char int2name(int i) {
    return i + 'A';
}

int visit(int k){
    printf("%d\n",k);
}

void init_queue(){
    head = (dnode*)calloc(1,sizeof(dnode));
    tail = (dnode*)calloc(1,sizeof(dnode));
    head->prev = head;
    head->next = tail;
    tail->prev = head;
    tail->next = tail;
}

int put(int k){//k는 데이터
    dnode *t;
    if((t=(dnode*)malloc(sizeof(dnode)))==NULL){
        printf("out of memory!\n");
        return -1;
    }
    t->key = k;
    tail->prev->next = t;
    t->prev = tail->prev;
    tail->prev = t;
    t->next = tail;
    return k;
}

int get(){
    dnode *t;
    int k;
    t = head->next;
    if (t == tail)
    {
        printf("underflow\n");
        return-1;
    }
    k = t->key;
    head->next = t->next;
    t->next->prev = head;
    free(t);
    return k;
    
}
//============================================================adjmat, adjlist
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

void input_adjlist(dnode *a[], int *V, int *E) {
    char vertex[3];
    int i, j;
    dnode *t;
    printf("input the num of node & edge\n");
    scanf("%d %d", V, E);
    for (i = 0; i < *V; i++) {
        a[i] = NULL;
    }

    for (j = 0; j < *E; j++) {
        printf("\ninput the two node consist of edge\n");
        scanf("%s", vertex);
        i = name2int(vertex[0]);
        t = (dnode *)malloc(sizeof(dnode));
        t->key = name2int(vertex[1]);
        t->next = a[i];
        a[i] = t;
        //printf("vertex: %d t->next: %d a[%d]: %d\n",t->vertex,t->next,i,a[i]);
        i = name2int(vertex[1]);
        t = (dnode *)malloc(sizeof(dnode));
        t->key = name2int(vertex[0]);
        t->next = a[i];
        //printf(" vertex: %d t->next: %d\n",t->vertex,t->next);
        a[i] = t;
        //printf("vertex: %c t->next: %d a[%d]: %d\n",t->vertex,t->next,i,a[i]);
    }
}
//============================================================print mat, list

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

void print_adjlist(dnode *a[],int V){
    dnode *temp;
    for (int i = 0; i < V; i++)
    {
        printf("Vertex %c:",int2name(i));
        temp= a[i];
        //printf("a[%d] : %d\n",i,a[i]);
        while (temp !=NULL)
        {
            printf("%c ",int2name(temp->key));
            temp = temp->next;
        }
        printf("\n");
        
    }
    

}

//============================================================adjlist ,mat BFS

void BFS_adjmatrix(int a[][MAX_NODE], int V)
{
    int i, j;
    int cnt = 0;
    init_queue();
    for(i = 0; i<V; i++) check[i] = 0;
    for(i = 0; i<V; i++){
        if(check[i] == 0){
            ++cnt;
            put(i);
            check[i] = 1;
            while(!(head->next == tail)){//queue_empty()
                i = get();
                visit(i);
                for( j = 0; j<V; j++){
                    if(a[i][ j] != 0){
                        if(check[j] == 0){
                            put( j);
                            check[j] = 1;
                        }
                    }
                }
            }   
        }
    }
    printf("Number of graph loops: %d\n",cnt);
}


void BFS_adjlist(dnode *a[],int V){
    int i;
    dnode *t;
    init_queue();
    for ( i = 0; i < V; i++)
    {
        check2[i] = 0;
    }
    for ( i = 0; i < V; i++)
    {
        if (check2[i]==0)
        {
            put(i);
            check2[i] = 1;
            while(!(head->next == tail)){//queue_empty()
                i = get();
                visit(i);
                for (t =a[i]; t != NULL; t=t->next)
                {
                    if (check2[t->key]==0)
                    {
                        put(t->key);
                        check2[t->key] = 1;
                    }
                    
                }
                
            }
            
        }
        
    }  
    
}

//=====================================================print func
void adjmatrix_func(){
    printf("==================Adjmatrix==================\n");
    int V, E;
    input_adjmatrix(GM, &V, &E);
    print_adjmatrix(GM, V);
    printf("===BFS adjmat===\n");
    BFS_adjmatrix(GM,V);

}

void adjlist_func(){
    int V,E;

    printf("==================Adjlist==================\n");
    input_adjlist(GL,&V,&E);
    print_adjlist(GL,V);
    printf("===BFS adjlist===\n");
    BFS_adjlist(GL,V);
    

}

void main(){
    adjmatrix_func();
    //adjlist_func();
}