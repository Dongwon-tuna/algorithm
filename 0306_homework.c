#include <stdio.h>
#include <stdlib.h>

int primeSieve(int input){
    printf("%d\n",input);
    int *arr = (int*)malloc(sizeof(int)*input);
    for (int i = 0; i < input; i++)
    {
        arr[i] = i+1;
    }

    for (int i = 1; i < input; i++)
    {
        if (arr[i] != 0)
        {   
            int j = i+1;
            for (j; j < input; j++)
            {
                if(arr[j]%arr[i]==0){
                    arr[j] = 0;
                }
            }
            
        }
        
    }
    printf("prime number is:");
    for (int i = 1; i < input; i++)
    {
        if (arr[i]!=0)
        {
            printf("%d,",arr[i]);
        }    
        
    }
    
    free(arr);
}

void main(){
    printf("Input number:");
    int inputNum=0;
    scanf("%d",&inputNum);
    primeSieve(inputNum);
    
}