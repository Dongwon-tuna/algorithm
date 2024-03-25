#include <stdio.h>
#include <stdlib.h>
#define MAX_NODE 10

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

int main() {
    int V, E;
    input_adjmatrix(GM, &V, &E);
    print_adjmatrix(GM, V);
    return 0;
}
