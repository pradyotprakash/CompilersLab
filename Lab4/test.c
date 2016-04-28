void f(int *a){
	a[5]=10;
}

void main(){
	int a[20][20];
	f(a[5]);
	printf(a[5][5]);
}
