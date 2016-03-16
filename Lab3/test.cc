struct s {
    int a;
};
struct t {
    int a;
    int b;
};
int * f(void * a, int * b) {
    float * c;
    c = a; // Allowed. All pointers are compatible with void *.
    b = c; // Error. int * and float * are incompatible.
    b = a; // Allowed. All pointers are compatible with void *
    return a; // Allowed. void * and int * are compatible.
    return b; // Allowed
    return c; // Error. float * and int * are incompatible.
}

int g() {
    struct s a, *p;
    struct t * b, **q;
    void * v;
    p = &a; // Allowed
    q = b; // Error
    q = &b; // Allowed
    v = f(*q, &(p->a)); // Allowed
    q = *v; // Error. Cannot dereference void *.
    return (*(*q)).b; // Allowed
}
