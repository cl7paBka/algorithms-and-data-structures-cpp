#include <iostream>
#include <chrono> // Для замеров времени

using namespace std;

// Рекурсивная функция для вычисления числа сочетаний
int combinations_recursive(int n, int m, int& recursive_calls) {
    recursive_calls++; // Увеличиваем количество рекурсивных вызовов
    if (m == 0 || n == m) return 1; // Базовые случаи
    return combinations_recursive(n - 1, m - 1, recursive_calls) + combinations_recursive(n - 1, m, recursive_calls);
}

// Итеративная функция для вычисления факториала
long long factorial(int num, int& steps) {
    long long fact = 1;
    for (int i = 1; i <= num; ++i) {
        fact *= i;
        steps++; // Увеличиваем количество шагов
    }
    return fact;
}

// Итеративная функция для вычисления числа сочетаний через факториалы
long long combinations_iterative(int n, int m, int& iterative_steps) {
    iterative_steps = 0;
    long long nFact = factorial(n, iterative_steps);
    long long mFact = factorial(m, iterative_steps);
    long long nMinusMFact = factorial(n - m, iterative_steps);
    return nFact / (mFact * nMinusMFact);
}

int main() {
    int n, m;
    cout << "Введите n и m (n >= m): ";
    cin >> n >> m;

    int recursive_calls = 0;
    auto start_recursive = chrono::high_resolution_clock::now(); // Начало замера времени
    int result_recursive = combinations_recursive(n, m, recursive_calls);
    auto end_recursive = chrono::high_resolution_clock::now(); // Конец замера времени
    chrono::duration<double> time_recursive = end_recursive - start_recursive;

    int iterative_steps = 0;
    auto start_iterative = chrono::high_resolution_clock::now(); // Начало замера времени
    long long result_iterative = combinations_iterative(n, m, iterative_steps);
    auto end_iterative = chrono::high_resolution_clock::now(); // Конец замера времени
    chrono::duration<double> time_iterative = end_iterative - start_iterative;

    cout << "Число сочетаний (рекурсивно): " << result_recursive << endl;
    cout << "Количество рекурсивных вызовов: " << recursive_calls << endl;
    cout << "Время выполнения (рекурсивно): " << time_recursive.count() << " секунд" << endl;

    cout << "Число сочетаний (итеративно): " << result_iterative << endl;
    cout << "Количество шагов итераций: " << iterative_steps + 2 << endl;
    cout << "Время выполнения (итеративно): " << time_iterative.count() << " секунд" << endl;

    cout << "Разница между количеством рекурсивных вызовов и количеством шагов итераций: " << abs(recursive_calls - iterative_steps) << endl;
    cout << "Разница во времени между двумя методами: " << abs(time_recursive.count() - time_iterative.count()) << " секунд" << endl;

    return 0;
}
