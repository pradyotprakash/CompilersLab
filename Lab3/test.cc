struct t{
	int x;
	int y;
};

struct y{
	struct t a;
	int z;
};

int main(){
	struct y a;
	a.a;
}
