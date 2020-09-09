#include <stdio.h>
#include <stdlib.h>

int main(){
	char s[100];
	while(1){
		scanf("%100s",s);
		system(s);	
	}
	return 0;
}

/* to run it I used gcc: "gcc ex3.c -o ex3", then "./ex3"
