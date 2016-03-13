struct hello {
        int a;
        float b;
};

struct hello_world {
        int a;
        float b;
};

int get_a(struct hello_world k) {
        return 1;
}

int main() {
        int b;
        int a;
        struct hello_world k;  

        a = get_a(k);

        return 0;
}
