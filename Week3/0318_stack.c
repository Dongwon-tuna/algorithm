#include <stdio.h>
#include <stdlib.h>

//stack push pop
#define MAX 10
int stack[MAX];
int top = -1;

void init_stack(void){
    top = -1;
}

int push(int t){
    if (top>=MAX-1)
    {
        printf("Stack overflow!\n");
        return -1;
    }
    top++;
    //printf("top: %d t: %d\n",top,t);
    stack[top] = t;//top 증가시키고 그 리고 값 복사
    return t;
    
}

int pop(){
    if(top<0){
        printf("Stack underflow!\n");
        return -1;
    }

    return stack[top--];
}



void pushing(){
    int k;
    int cnt =0;
    init_stack;
    printf("inti top: %d\n",top);
    while (1)
    {
        scanf("%d",&k);
        
        int y = push(k);
        if (y == 100)
        {
            pop(y);
            break;
            
        }
        else if (y == -1)
        {
            break;
        }
        
        
    }

}

void poping(){
    for (int i = top; i >=0; i--)
    {
        printf("pop: %d, top: %d\n",pop(i),top);
    }
}

int main(void){
    
    pushing();
    poping();
    
    
  
}