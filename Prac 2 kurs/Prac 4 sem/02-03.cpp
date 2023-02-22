class C {
private:
    int a_ = 0;

public:
    C(const C, const C) {}
    C(const C *c) {}
    C(double p) {}
    C() {}
    
    static void f() {}

    int operator~() const {
        return 1;
    }

    C operator++() {
        return C();
    }
};

C operator+ (const int a, const C b) {
    return C();
}

int operator* (const C a, C *const b) {
    return 1;
}