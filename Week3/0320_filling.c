#include <stdio.h>
#include <stdlib.h>

#define BLK 7
int canvas[7][7] = {0, 1, 0, 0, 0, 0, 0,
0, 0, 1, 1, 1, 0, 0,
0, 1, 0, 0, 0, 1, 0,
0 ,1, 0, 0, 0, 1, 0,
0, 1, 0, 0, 1, 0, 0,
0, 0, 1, 1, 1, 0, 0,
0, 0, 0, 0, 0, 0, 0};


void fill(int x, int y){
    canvas[x][y] = 2;
}

void recurl_fill(int x, int y){
    if(canvas[x][y] == 1||canvas[x][y] == 2){
        return;
    }
    fill(x,y);
    recurl_fill(x-1,y);
    recurl_fill(x,y-1);
    recurl_fill(x+1,y);
    recurl_fill(x,y+1);

}

void main()
{
    int i, j;
    recurl_fill(3,3);
    for(i = 0; i<BLK; i++){
        for(j = 0; j<BLK; j++){
            printf("%d", canvas[i][j]);
        }
    printf("\n");
    }

}