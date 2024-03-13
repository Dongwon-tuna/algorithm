#include <stdio.h>
#include <stdlib.h>


void move(int from, int to){
    printf("\nMove from %d to %d",from,to);
}

void hanoi(int n, int from, int by, int to){
    if(n==1){
        move(from, to);
    }
    else{
        hanoi(n-1,from,to,by);
        move(from,to);
        hanoi(n-1,by,from,to);
    }
}

void main(){
        printf("Input the tower height:");
        int height;
        scanf("%d",&height);
        hanoi(height,1,2,3);
    
    

}