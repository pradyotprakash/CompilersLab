int f(){
	return 3.3;
}

int main(){
	int a,b;
	float c,d;
	a=(b=1);
	c=a*2.5;
	printf("Output:", a, c, "p");
	printf(f());
	return 0;
}