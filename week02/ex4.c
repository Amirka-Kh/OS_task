#include <stdio.h>

int main() 
{
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);
    
    printf("Before a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("After a = %d, b = %d\n", a, b);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
