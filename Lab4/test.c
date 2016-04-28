// void f(int a[1]){
// 	a[5]=1;
// }

// void main(){
// 	int a[10][10];
// 	f(a[5]);
// }

struct s{
	int x;
	int y;
};

//struct s 
struct s f(){
	struct s t;
	t.x=2;
	printf(t.x);
	return t;
}

void main(){
	struct s y;
	struct s t;
	t.x=5;
	y=f();
	printf(t.x);
	printf(y.x);
}