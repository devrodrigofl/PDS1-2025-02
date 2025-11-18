int fibonacci(int n) {
    if (n <= 0 || n > 30) return -1;
    if (n == 1 || n == 2) return 1;
    int fib = 0, n1 = 1, n2 = 1;
    for(int i = 3; i <= n; i++)  {
        fib = n1 + n2;
        n2 = n1;
        n1 = fib;
    }
    return fib;
}

int fibonacci2(int n) {
    if (n <= 0 || n > 30) return -1;
    if (n == 1 || n == 2) return 1;
    int fib = fibonacci2(n-1) + fibonacci2(n-2);
    return fib;
}   