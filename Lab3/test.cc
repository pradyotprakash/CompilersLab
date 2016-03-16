struct a{
    int a, b;
    float c, d;
    struct a *** str;
};

int h(int y){
    int t;
    t = y*y;
    return t;
}

int f(){
    int s;
    return s++;
}

int main(){
    struct a x;
    struct a y;
    void * a, * b;
    x=y;

    return 0;
}