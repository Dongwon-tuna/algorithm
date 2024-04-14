#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define SIZE 20

int name2int(char c) {		// 문자를 숫자로 바꾼다. 만약 'B'가 입력되면 
	return c - 'A';			// 'B' - 'A' =  1 (아스키코드값으로 변환되어 계산됨)
}

char int2name(int i) {		// 숫자를 문자로 바꾼다.
	return i + 'A';
}

int heap[SIZE + 1];		// heap 배열

void upheap(int* heap, int k) {
	int v;
	v = heap[k];				// k번째 원소를 v에 저장
	heap[0] = INT_MAX;
	while (heap[k / 2] <= v && k / 2 > 0) {		// parent <= child 이고 k = 2 이상이면
		heap[k] = heap[k / 2];					// child = parent 로 바꾸고
		k /= 2;									// k = parent level 로 올라감 (level : 제일 위에가 level 1을 뜻함)
	}
	heap[k] = v;								// parent = child 로 바꿈. while문을 거치지 않으면 heap[k]는 변하지 않음
}

void downheap(int* heap, int N, int k) {		// N : 제일 위에 있는 값을 extract하고 제일 마지막 원소를 root로 옮기고 난 후의 heap의 길이
	int i, v;									// k = 1
	v = heap[k];
	while (k <= N / 2) {
		i = k << 1;			// i = k*2
		if (i < N && heap[i] < heap[i + 1])		// Left child와 Right child 중 큰 값을 root와 바꿔야 하므로
			i++;								// 만약 Right child가 더 크다면 i++ 를 해줌
		if (v >= heap[i])						// parent >= child면 while문 종료
			break;
		heap[k] = heap[i];						// parent = 위에서 찾은 child 중 큰 값으로 바꿈
		k = i;									// 다음 level로 이동
	}
	heap[k] = v;		// 처음에 root로 옮긴 값을 위와 같은 과정을 거친 후 Ground rule를 만족하는 위치로 옮김
}

void insert(int* heap, int* N, int v) {
	heap[++(*N)] = v;					// 처음에 *N = 0 이므로 1을 먼저 더해준다.
	upheap(heap, *N);
}

int extract(int* heap, int* N) {		// 처음에 *N = 15
	int v = heap[1];					// 제일 위에 값을 extract 하고 
	heap[1] = heap[(*N)--];				// 제일 마지막 원소를 root 위치로 옮긴다.
	downheap(heap, *N, 1);				// downheap 진행

	return v;						// 처음에 추출한 값을 반환
}

void print_heap(int* a, int N) {
	for (int i = 1; i <= N; i++)
		printf("%c  ", int2name(a[i]));
}

void heap_sort(int* a, int N) {
	int i;
	int hn = 0;		// # of heap nodes

	for (i = 1; i <= N; i++)
		insert(heap, &hn, a[i]);
	printf("After heap\n");
	print_heap(heap, N);	// 제일 위에서부터 아래로 차례대로 출력
	printf("\n");

	for (i = hn; i >= 1; i--)
		a[i] = extract(heap, &hn);
	printf("After extract\n");
	print_heap(a, N);		// 가장 마지막에 추출한 것부터 출력하게 됨
	printf("\n");			// a[]의 결과를 보면 값들이 정렬됨.
}

void main() {
	char str[] = "ABCDE";
	int len = strlen(str);
	int a[MAX];
	for (int i = 0; i < len; i++) {
		a[i + 1] = name2int(str[i]);	// heap에서 처음 원소의 index = 1 이므로 a[i+1]
	}
	heap_sort(a, len);
}