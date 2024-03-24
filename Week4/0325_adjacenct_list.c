#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100

typedef struct _node{
    int vertex;//vertex 변수는 노드의 값, 즉 노드가 표현하는 정점(vertex)을 나타냅니다.
    struct _node *next;//둘째, next 포인터는 다음 노드를 가리키는 포인터입니다. 이는 그래프의 간선을 표현하는 역할을 합니다.
}node;


int name2int(char c) {
    return c - 'A';
}

char int2name(int i) {
    return i + 'A';
}

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
        i = name2int(vertex[1]);
        t = (node *)malloc(sizeof(node));
        t->vertex = name2int(vertex[0]);
        t->next = a[i];
        a[i] = t;
    }
}

void print_adjlist(node *a[],int V){
    node *temp;
    for (int i = 0; i < V; i++)
    {
        printf("Vertex %c:",int2name(i));
        temp= a[i];
        while (temp !=NULL)
        {
            printf("%c ",int2name(temp->vertex));
            temp = temp->next;
        }
        printf("\n");
        
    }
    

}

void main(){
    int V,E;
    input_adjlist(GL,&V,&E);
    print_adjlist(GL,V);
}

