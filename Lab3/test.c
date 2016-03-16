struct S
{
    int a;
    float b;
};

float* f(float* g){
    void* c;
    c=g;
    return c;
}

int main()
{
    float f1,f2,f3;
    float fa[3];
    int ia[3];
    int i1,i2;
    struct S x;
    float* y;

    i1 = f1 + f2;       // i1 = (int) f1 +FLOAT f2
    f3 = f1 / i2;       // f3 =  f1 /FLOAT ((float) i2)
    f1 = i1 * x.a;      // f1 = (float) i1 +INT x.a
    i1 = fa[0] + ia[5]; // i1 = (int) fa[0] +FLOAT ((float) ia[0])
}