#include <iostream>

// рекурсивная функция для вычисления n-ого члена последовательности
int fibonacci(int n) {
    if (n == 0) return 0; // базовый случай
    if (n == 1) return 1; // базовый случай
    return fibonacci(n - 1) + fibonacci(n - 2); // рекурсивный вызов
}

int main() {
    int n;
    std::cout << "Введите n для нахождения члена последовательности: ";
    std::cin >> n;
    std::cout << "Член последовательности: " << fibonacci(n) << std::endl;
    return 0;
}
