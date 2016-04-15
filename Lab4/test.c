struct s {
    int a[20];
};
struct t {
    int a;
    int b;
};

int * f(void * a, struct s* t, int * b) {
    float * c;
    void* d;
    struct t g;
    return &(t->a[0]);
}

