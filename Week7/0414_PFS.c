#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100
#define UNSEEN (-INT_MAX)

typedef struct node {
	int vertex;
	int weight;
	struct node* next;
}node;

node* G[MAX_NODE];		// adjlist를 하고난 결과 나온 배열
int weight[MAX_NODE];	// 가중치를 저장하는 배열
int parent[MAX_NODE];	// get한 노드를 어떤 노드가 넣어줬는지 알아내기위한 배열. 즉, 넣어준 노드가 부모 노드이다.
int nheap = 0;			// # of elements in the heap
int heap[MAX_NODE];		// heap 배열

char int2name(int i) {
	return i + 'A';
}

int name2int(char c) {
	return c - 'A';
}

void visit(int i) {
	printf(" -> %c ", int2name(i));
}

void input_adjlist(node* g[], int* V, int* E) {
	char vertex[3];
	
	int i, j, w;
	node* t;	// list들을 서로 연결시키기 위한 구조체 포인터

	printf("\nInput number of node & edge\n");
	scanf("%d %d", V, E);

	for (i = 0; i < *V; i++)
		g[i] = NULL;			// 처음 값들을 모두 NULL로 초기화 -> list의 끝이 NULL

	printf("\nInput two node consist of edge and weight\n");

	for (j = 0; j < *E; j++) {
		scanf("%s %d", vertex, &w);

		i = name2int(vertex[0]);			
		t = (node*)malloc(sizeof(node));	
		t->vertex = name2int(vertex[1]);
		t->weight = w;						// 가중치도 저장한다.
		t->next = g[i];						
		g[i] = t;							

		i = name2int(vertex[1]);			// AB면 BA도 만족하므로 Symmetric 하는 과정
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->next = g[i];
		t->weight = w;
		g[i] = t;
	}

}

void print_adjlist(node* g[], int V) {
	node* t = NULL;

	for (int i = 0; i < V; i++) {
		printf("\n % c : ", int2name(i));
		for (t = g[i]; t != NULL; t = t->next)
			printf("-> %c:%d ", int2name(t->vertex), t->weight);	// 가중치도 같이 출력한다.
	}
}

void pq_init() {
	nheap = 0;
}

int pq_empty() {		// heap이 비어있는지 확인
	if (nheap == 0) 
		return 1;
	return 0;
}

void upheap(int h[], int k)	{
	int v;
	v = h[k];

	while (weight[h[k / 2]] <= weight[v] && k / 2 > 0) {	// 부모가 자식보다 우선순위 낮으면 (전에는 vertex 값으로 비교를 했다면 PFS는 가중치 값을 비교를 함)
		h[k] = h[k / 2];									// 부모 - 자식 위치를 바꿈
		k /= 2;												
	}
	h[k] = v;
}

void downheap(int h[], int k)
{
	int i, v;
	v = h[k];

	while (k <= nheap / 2) {								// 자식 있는 노드만 생각
		i = k << 1;											// 자식과 비교하기 위해 2를 곱함

		if (i < nheap && weight[h[i]] < weight[h[i + 1]])	// 자식이 있고, 오른쪽 자식이 우선순위 더 크면
			i++;											// 오른쪽 자식을 쓰자

		if (weight[v] >= weight[h[i]]) break;				// 내가 더 크면 여기서 멈추자
		h[k] = h[i];										// 아니면 자리를 바꿔주자. 자식을 위로 올리자.

		k = i;												// 나는 한 층 아래로 내려간다.	
	}
	h[k] = v;
}

int pq_extract(int h[]) {		// heap 안에서 가중치가 가장 큰 것을 extract하고
	int v = h[1];
	h[1] = h[nheap--];			// 가장 오른쪽에 있는 값을 제일 위로 올려서
	downheap(h, 1);				// downheap을 한다.
	return v;					// 처음에 제일 위에(앞에) 있던 노드를 반환한다.
}

void adjust_heap(int h[], int n) {		// 업데이트한 가중치로 다시 배열해야하므로
	for (int k = n / 2; k >= 1; k--)
		downheap(h, k);
}

void print_heap(int h[]) {
	printf("\n");
	for (int i = 1; i <= nheap; i++)						// 1부터 출력해주기
		printf(" %c:%d ", int2name(h[i]), weight[h[i]]);	// 인덱스와 가중치 출력
}

int pq_update(int h[], int v, int p) {
	if (weight[v] == UNSEEN) {				// unseen 노드라면
		h[++nheap] = v;						// 힙에 인덱스 저장
		weight[v] = p;						// 힙에 가중치 저장
		upheap(h, nheap);					// upheap을 한다. 즉, 우선순위가 높은게 heap 위쪽으로 온다.
		return 1;
	}
	else {									// fringe 노드라면
		if (weight[v] < p) {				// 입력한 것이 우선순위가 더 높다면 (예를 들어 원래 weight(I) = -3 이였는데 H가 tree가 될때 weight(I) = -2 이므로 update 해야함.
			weight[v] = p;					// 업데이트
			adjust_heap(h, nheap);			// 가중치를 update 했으므로 다시 downheap을 해서 올바르게 배열해야함.
			return 1;
		}
		else
			return 0;						// update할 필요 없음
	}
}

void PFS_adjlist(node* g[], int V)
{
	node* t;
	pq_init(); // 힙 초기화

	for (int i = 0; i < V; i++) {			// heap의 가중치와 부모 노드를 초기화
		weight[i] = UNSEEN;					// 모든 노드 = unseen 노드
		parent[i] = 0;						// initialize a tree
	}

	// 모든 노드를 돌면서
	for (int i = 0; i < V; i++) {
		if (weight[i] == UNSEEN) {			// unseen 노드이면
			parent[i] = -1;					// 첫 정점
			pq_update(heap, i, UNSEEN);		// 2가지 기능을 한다. 자세한 설명은 pq_update 함수에 있다.

			while (!pq_empty()) {			// 힙이 빌 때까지 = 모든 노드 방문할 때까지
				print_heap(heap);			// 힙에 있는 값들을 가중치와 함께 출력.
				i = pq_extract(heap);		// 가장 우선순위 높은 값을 겟한다 = 트리 정점이 된다.
				weight[i] = -weight[i];		// 부호를 반전시킨다. 가중치를 양수로 바꾸는 과정
				visit(i);

				for (t = g[i]; t != NULL; t = t->next) {	// 방금 위에서 방문하면서 정점이 된 그 노드와 연결되어 있는 노드들이 fringe nodes로 된다.
					if (weight[t->vertex] < 0)				// unseen 노드거나, 주변 정점이면
						if (pq_update(heap, t->vertex, -(t->weight)))	// 가중치를 저장하거나(unseen 노드), 가중치 갱신(주변 정점), 위 함수들에서 사용하는 weight는 음수인데 t->weight는 양수이므로 (-)
							parent[t->vertex] = i;						// 부모를 설정해주기. (fringe node가 된 이 노드가 어떤 노드 때문에 됐는지)
				}
			}
		}
	}
}

// 최소 비용 출력
void print_cost(int weight[], int V) {
	int cost = 0;
	for (int i = 1; i < V; i++) {
		cost += weight[i];
	}
	printf("%d\n", cost);
}

// 자식 노드 - 부모 노드 출력
void print_tree(int parent[], int V) {
	printf("\n\nTree structure\n");

	printf("son    ");
	for (int i = 0; i < V; i++)
		printf("%c ", int2name(i));

	printf("\n----------------------------\n");

	printf("parent   ");
	for (int i = 1; i < V; i++)
		printf("%c ", int2name(parent[i]));
}


void main() {
	int V, E;


	input_adjlist(G, &V, &E);
	printf("\nOriginal graph\n");
	print_adjlist(G, V);

	// PFS
	printf("\n\nVisit order of Minimum Spanning Tree\n");
	PFS_adjlist(G, V);

	// 자식 - 부모 출력
	print_tree(parent, V);

	// 최소 비용 출력
	printf("\n\nMinimum Cost is \n");
	print_cost(weight, V);


}
