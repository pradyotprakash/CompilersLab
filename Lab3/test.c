
int returnInt () {
    return 1;
}

int main() {
    int a;
    int b;
    int c[3];

    a = 2;
    b = 4;
    
    
    *(&a) = b; 

   
    c[ returnInt() ] = 1;
}