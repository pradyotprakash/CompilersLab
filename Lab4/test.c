struct s {
	int c;
    int a[5][5];
    int b;
};

struct t {
    int a;
    int b;
};


int f(int *a){
	int x;
	x=*a;
	*a = 3;
	return x; 
}

int g(int x){
	return x*x;
}


// int main(){
// 	int b;
// 	struct s c;
// 	struct s* d;
// 	d=&c;
// 	x();
// 	c.a[3][2]=4;
// 	c.a[2][3]=d->a[3][2]-1;
// 	d->b=17;
// 	b=c.a[2][3]+c.b;
// 	b=-b;
// 	return b;	
// }

int main(){
	int* x;
	int b;
	x=&b;
	*x=5;
	return f(x) + g(*x);	
}