#include <iostream>
#include <chrono> // Для замеров времени

using namespace std;

// Рекурсивная функция для нахождения НОД
int gcd_recursive(int a, int b, int& recursive_calls) {
    recursive_calls++; // Увеличиваем количество рекурсивных вызовов
    if (b == 0) return a; // Базовый случай
    return gcd_recursive(b, a % b, recursive_calls); // Рекурсивный вызов
}

// Итеративная функция для нахождения НОД
int gcd_iterative(int a, int b, int& iterative_steps) {
    iterative_steps = 0;
    while (b != 0) {
        iterative_steps++; // Увеличиваем количество шагов
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int a, b;
    cout << "Введите два натуральных числа: ";
    cin >> a >> b;

    int recursive_calls = 0;
    auto start_recursive = chrono::high_resolution_clock::now(); // Начало замера времени
    int result_recursive = gcd_recursive(a, b, recursive_calls);
    auto end_recursive = chrono::high_resolution_clock::now(); // Конец замера времени
    chrono::duration<double> time_recursive = end_recursive - start_recursive;

    int iterative_steps = 0;
    auto start_iterative = chrono::high_resolution_clock::now(); // Начало замера времени
    int result_iterative = gcd_iterative(a, b, iterative_steps);
    auto end_iterative = chrono::high_resolution_clock::now(); // Конец замера времени
    chrono::duration<double> time_iterative = end_iterative - start_iterative;


    cout << "НОД (рекурсивно): " << result_recursive << " | НОД (итеративно): " << result_iterative << endl;
    cout << "Количество рекурсивных вызовов: " << recursive_calls << " | Количество шагов итераций: " << iterative_steps << endl;
    cout << "Время выполнения (рекурсивно): " << time_recursive.count() << " секунд" << " | Время выполнения (итеративно): " << time_iterative.count() << " секунд" << endl;
    cout << "Разница между количеством рекурсивных вызовов и количеством шагов итераций: " << abs(recursive_calls-iterative_steps) << endl ;
    cout << "Разница во времени между двумя методами: " << abs(time_recursive.count() - time_iterative.count()) << " секунд" << endl;


    return 0;
}
