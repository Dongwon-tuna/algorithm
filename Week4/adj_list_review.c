#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int node;
    struct _node *next;
}node;


int char2int(char c){
    return c-'A';
}

char int2char(int i){
    return i +'A';
}

node *LA[100];

void adjlist(node *a[],int *V, int *E){
    int i,j;
    char vrtex[3];
    node *t;
    printf("node num, edge num\n");
    scanf("%d %d",V,E);
    for ( i = 0; i < *V; i++)
    {
        a[i] = NULL;
    }
    for ( j = 0; j < *E; j++)
    {
        printf("input edge:\n");
        scanf("%s",vrtex);
        i = char2int(vrtex[1]);//연결된 것이 몇번째 요소인기 파악
        t = (node*)malloc(sizeof(node));
        t->node = char2int(vrtex[0]);
        t->next = a[i];
        a[i] = t;
        i = char2int(vrtex[0]);
        t = (node*)malloc(sizeof(node));
        t->node = char2int(vrtex[1]);
        t->next = a[i];
        a[i] = t;
    }
    
    
}

void print(node *a[],int *V, int *E){
    printf("====print====\n");
    //node *temp;
    //temp =a;
    
    for (int i = 0; i < *V; i++)
    {
        int trigger = 1;
        printf("%c:",int2char(i));
        while (trigger)
        {
            printf("%c ",int2char(a[i]->node));
            a[i] = a[i]->next;
            if (a[i] == NULL)
            {
                trigger = 0;
            }
            
        }
        printf("\n");
    }
    

}

void main(){
    int v,e;
    adjlist(LA,&v,&e);
    print(LA,&v,&e);
}