#include <stdio.h>
#include <stdlib.h>
#define BLK 7
int map[7][7]={0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 1, 0, 0, 0,
0 ,1, 1, 1, 1, 0, 0,
0, 0, 0, 0, 0, 1, 0,
0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0};


void fill(int x, int y){
    map[y][x] = 2;
    
}

void recur_fill(int x, int y){
    if (map[y][x]==0||map[y][x]==2)//terminate condition: 좌표에 있는 값이 2이거나, 0 일 경우.
    {
        return;
    }
    
    if (map[y][x] == 1)//좌표의 값이 1인 영역을 색칠하는 조건(1을 2로 바꾼다)
    {
        fill(x,y);
    }
    recur_fill(x + 1, y);//가로 세로 직선성분만 탐색
    recur_fill(x - 1, y);	
    recur_fill(x, y - 1);	
    recur_fill(x, y + 1);
    recur_fill(x + 1, y + 1);//대각성분까지 모두 탐색
    recur_fill(x + 1, y + -1);
    recur_fill(x - 1, y + 1);
    recur_fill(x -1 , y - 1);	
    
}
void main(){
    int i,j;
    recur_fill(3,2);
    for(i = 0; i<BLK; i++){
        for(j = 0; j<BLK; j++){
            printf("%d", map[i][j]);
        }
    printf("\n");
    }
}