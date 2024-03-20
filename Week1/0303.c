#include <stdio.h>
#include <stdlib.h>


int main(void){
    //printf("hello algorithm class");
    int a =45;
    int b =37;
    int c;
    int sum=0;
    printf("%d\n",a);
    while (a != 0)
    {
        
        int d = a%2;
        if (d == 1)
        {
            c = b;
        }
        else{
            c = 0;
        }
        a = a/2;
        b = b*2;
        printf("%d\n",c);
        printf("%d, %d\n",a,b);
        sum +=c;
        printf("%d\n",sum);
        
    }
    
    printf("Sum>>");
    printf("%d\n",sum);
    return 0;
}