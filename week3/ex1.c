#include <stdio.h>
int main(){
    int* pc;
    int c;
    c=22;
    printf("Address of c:%d\n",&c);              // 13564776
    printf("Value of c:%d\n\n",c);               // 22
    pc=&c;
    printf("Address of pointer pc:%d\n",pc);     // 13564776
    printf("Content of pointer pc:%d\n\n",*pc);  // 22
    c=11;
    printf("Address of pointer pc:%d\n",pc);     // 13564776
    printf("Content of pointer pc:%d\n\n",*pc);  // 11
    *pc=2;
    printf("Address of c:%d\n",&c);              // 13564776
    printf("Value of c:%d\n\n",c);               // 2
    return 0;
}
