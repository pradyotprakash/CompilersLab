struct s {
	int c;
    int a[5][5];
    int b;
};

struct t {
	struct s q;
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

int z(){
	struct t p;
	int* x;
	x=&(p.q.c);
	*x=5;
	return f(x) + (g(p.q.c)+1);	
}

int main(){
	int b;
	struct s c;
	struct s* d;
	d=&c;
	c.a[3][2]=4;
	c.a[2][3]=d->a[3][2]-1;
	d->b=17;
	b=c.a[2][3]+c.b;
	b=-b;
	b=b+z();
	return b;	
}
