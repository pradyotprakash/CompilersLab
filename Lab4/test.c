void f(int a[10]){
	a[5]=1;
}
void main(){
	int a[20][10];
	a[6][5]=4;
	printf("%d\n", a[6][5]);
	f(a[6]);
	printf("%d\n", a[6][5]);
}

