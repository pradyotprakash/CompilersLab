#include <stdio.h>
void f(){
	return;
}

int main(){

	int ***b;
	int **a[2];
	b=a;
	a=b;
}