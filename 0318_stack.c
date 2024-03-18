#include <stdio.h>
#include <stdlib.h>

//stack push pop
#define MAX 10
int stack[MAX];
int top;

void init_stack(void){
    top = -1;
}

int push(int t){
    if (top>=MAX-1)
    {
        printf("Stack overflow!\n");
        return -1;
    }

    stack[++top] = t;//top 증가시키고 그 리고 값 복사
    return t;
    
}

int pop(){
    if(top<0){
        printf("Stack underflow!\n");
        return -1;
    }

    return stack[top--];
}


int main(void){
    int k;
    init_stack;
    while (1)
    {

        printf("Input num(if you want quit, input 11)\n");
        scanf("%d",&k);
        if (k == 11)
        {
            break;
        }
        
        int s = push(k);
        if(s==-1){
            break;
            
        }
    }
    while (1)
    {
        
        int k = pop();
        if (top == -1)
        {
            break;

        }
        printf("Pop: %d top: %d\n",k,top);        
    }
  
}