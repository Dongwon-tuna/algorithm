//non recursive hanoi
#include <stdio.h>
#include <stdlib.h>

#define MAX 30
int stack[MAX];
int top ;

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


int is_stack_empty(){
    if (top == -1)
    {
        return 0;
    }
    else return 1;
    
}

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




void nr_hanoi(int n, int from, int by, int to) {
	int done = 0;
	init_stack();
	while (!done) {
		while (n > 1) {
			push(to);
			push(by);
			push(from);			
			push(n);
            printf("while\n");
			n--;
			push(to);
			to = by;
			by = pop();
		}
		move(from, to);
		printf(" big whilie\n");
		if (!(top == -1)) {
			n = pop();
			from = pop();
			by = pop();
			to = pop();
			move(from, to);
            printf("sec while\n");

			n--;
			push(from);
			from = by;
			by = pop();
		}
		else
			done = 1;
	}
}

void main(){
        printf("Input the tower height:");
        int height;
        scanf("%d",&height);
        hanoi(height,1,2,3);
        init_stack();
        printf("\n========nr hanoi========\n");

        nr_hanoi(height,1,2,3);

    
    

}