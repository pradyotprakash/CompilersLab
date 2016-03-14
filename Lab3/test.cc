int returnInt () {
    return 1;
}

int main() {
    int c[3];
    c[returnInt()] = 1;
}