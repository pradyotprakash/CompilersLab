struct a{
    int a, b;
    float c, d;
};

int f(){
    int s;
    return s++;
}

int h(int y){
    int t;
    t = y*y;
    return t;
}

int main() {
    struct a x;
    float y;
    x.a = (x.a < x.d) && x.c;
}