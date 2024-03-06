#include <stdio.h>
#include <stdlib.h>


//Find GCD by minus, mod methods. And test it's prime num.
int GCD_minus(int a,int b){
    int c=0;
    printf("=========================Using minus method=========================\n");
    while (a>=b)
    {
        
        a = a-b;
        printf("this is minus val:%d, %d\n",a,b);
        
        if (b>a)
        {
            c =a;
            a =b;
            b =c;
            printf("this is minus val:%d, %d\n",a,b);
        }
        if (b == 0)
        {
            break;
        }
    }  
    return a;
}

int GCD_mod(int a, int b){
    printf("=========================Using mod method=========================\n");
    int c=0;
    while (a>=b)
    {
        a = a%b;
        printf("this is mod val:%d, %d\n",a,b);
        if (b>a)
        {
            c =a;
            a =b;
            b =c;
            printf("this is mod val:%d, %d\n",a,b);
        }
        if (b == 0)
        {
            break;
        }
    }  
    return a;

}

void primeTester(int a){
    int cnt=0;
    for (int i = 1; i < a+1; i++)
    {
        if (a%i == 0)
        {
            cnt = cnt+1;
        }
   
    }
    if (cnt == 2)
        {
            printf("its Prime Num\n");
        }
    else{
        printf("its not\n");
    }
    

}
int main(void){
    int input1,input2;
    printf("Input two numbers:");
    scanf("%d %d",&input1,&input2);
    

    int result1 = GCD_minus(input1,input2);
    int result2 = GCD_mod(input1,input2);
    printf("GCD_minus: %d\n",result1);
    printf("GCD_mod: %d\n",result2);
    primeTester(input1);



    return 0;


    
}