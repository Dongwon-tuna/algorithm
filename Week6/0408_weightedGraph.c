#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100
int GM[MAX_NODE][MAX_NODE];
FILE* fp;

int name2int(char c) {		// 문자를 숫자로 바꾼다. 만약 'B'가 입력되면 
	return c - 'A';			// 'B' - 'A' =  1 (아스키코드값으로 변환되어 계산됨)
}

char int2name(int i) {		// 숫자를 문자로 바꾼다.
	return i + 'A';
}

void input_adjmatrix(int a[][MAX_NODE], int* V, int* E) {		// main 함수 내의 V, E값을 바꿔야하므로 포인터값을 파라미터로 가짐
	char vertex[3];						// 연결된 두 문자를 받기위한 배열. 마지막 칸에는 널문자가 들어가야하므로 총 3칸의 배열 생성
	int i, j, k;
	int w;
	printf("\nInput number of node & edge\n");
	scanf("%d %d", V, E);			// # of node, edge
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			a[i][j] = 0;			// 모든 원소의 값을 0으로 초기화
	for (i = 0; i < *V; i++)
		a[i][i] = 1;				// 대각 성분은 자기 자신이므로 모두 1
	printf("\nInput two node consist of edge & weight -> ");
	for (k = 0; k < *E; k++) {
		scanf("%s %d", vertex, &w);		// AB 입력 받으면 vertex[0] = 'A', vertex[1] = 'B'
		i = name2int(vertex[0]);	// 'A' -> 0
		j = name2int(vertex[1]);	// 'B' -> 1
		a[i][j] = w;				// AB 연결 = BA 연결
		a[j][i] = w;
	}
}

void print_adjmatrix(int a[][MAX_NODE], int V) {	// 배열을 출력
	printf("\n");
	int i, j;

	for (i = 0; i < V; i++) {
		printf("%3c", int2name(i));
		for (j = 0; j < V; j++)
			printf("%3d", a[i][j]);
		printf("\n");
	}
}

void main() {
	int V, E;

	input_adjmatrix(GM, &V, &E);
	print_adjmatrix(GM, V);

}