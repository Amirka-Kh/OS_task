#include <stdio.h>

int main() 
{
    int n;
    scanf("%d", &n);
    
    for (int j = 1; j <= n; j++)
    { 
        for (int h = 1; h <= n - j; h++)
        {
            printf(" ");
        }
        
        for (int h = 1; h <= 2*j - 1; h++)
        {
            printf("*");
        }
        printf("\n");
    } 
}    
