#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>

void hanoi(int n, int from, int by, int to);
void move(int from, int to);

void main() {
	int h = 0;
	
	printf("\nInput the height of hanoi tower: ");
	scanf("%d", &h);
	hanoi(h, 1, 2, 3);	
}

void hanoi(int n, int from, int by, int to) {
	if (n == 1)
		move(from, to);
	else {
		hanoi(n - 1, from, to, by);
		move(from, to);
		hanoi(n - 1, by, from, to);
	}
}

void move(int from, int to) {
	printf("\nMove from P%d to P%d", from, to);
}