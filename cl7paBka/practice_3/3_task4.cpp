#include <iostream>
#include <cmath> // Для функции pow
#include <chrono> // Для измерения времени
#include <vector> // Для хранения цепочек решений

using namespace std;

// Функция для вычисления суммы кубов цифр числа
int sum_of_cubes(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += pow(digit, 3);
        n /= 10;
    }
    return sum;
}

// Рекурсивная функция для получения числа 153 с цепочкой решения
int converge_to_153_recursive(int n, int& iterations, vector<int>& recursive_chain) {
    iterations++;
    recursive_chain.push_back(n); // Сохраняем текущее число
    if (n == 153) return n;
    return converge_to_153_recursive(sum_of_cubes(n), iterations, recursive_chain);
}

// Итеративная функция для получения числа 153 с цепочкой решения
int converge_to_153_iterative(int n, int& iterations, vector<int>& iterative_chain) {
    iterations = 0;
    while (n != 153) {
        iterative_chain.push_back(n); // Сохраняем текущее число
        n = sum_of_cubes(n);
        iterations++;
    }
    iterative_chain.push_back(n); // Сохраняем последнее число (153)
    return n;
}

int main() {
    int n;
    cout << "Введите натуральное число, кратное 3: ";
    cin >> n;

    // Рекурсивный подход
    int recursive_iterations = 0;
    vector<int> recursive_chain; // Для хранения цепочки решений (рекурсивно)
    auto start_recursive = chrono::high_resolution_clock::now();
    int result_recursive = converge_to_153_recursive(n, recursive_iterations, recursive_chain);
    auto end_recursive = chrono::high_resolution_clock::now();
    chrono::duration<double> time_recursive = end_recursive - start_recursive;

    // Итеративный подход
    int iterative_iterations = 0;
    vector<int> iterative_chain; // Для хранения цепочки решений (итеративно)
    auto start_iterative = chrono::high_resolution_clock::now();
    int result_iterative = converge_to_153_iterative(n, iterative_iterations, iterative_chain);
    auto end_iterative = chrono::high_resolution_clock::now();
    chrono::duration<double> time_iterative = end_iterative - start_iterative;
    
    // Вывод результатов
    cout << "Рекурсивно итоговое число: " << result_recursive << " | Итеративно итоговое число: " << result_iterative << endl;
    cout << "Количество рекурсивных вызовов: " << recursive_iterations << " | Количество шагов итераций: " << iterative_iterations << endl;
    cout << "Время выполнения (рекурсивно): " << time_recursive.count() << " секунд" << " | Время выполнения (итеративно): " << time_iterative.count() << " секунд" << endl;
    cout << "Разница между количеством рекурсивных вызовов и количеством шагов итераций: " << abs(recursive_iterations - iterative_iterations) << endl;
    cout << "Разница во времени между двумя методами: " << abs(time_recursive.count() - time_iterative.count()) << " секунд" << endl;

    // Вывод цепочки решений для рекурсивного метода
    cout << "\nЦепочка решений (рекурсивно):" << endl;
    for (const auto& step : recursive_chain) {
        cout << step << " => ";
    }
    cout << "Конец цепочки" << endl;

    // Вывод цепочки решений для итеративного метода
    cout << "\nЦепочка решений (итеративно):" << endl;
    for (const auto& step : iterative_chain) {
        cout << step << " => ";
    }
    cout << "Конец цепочки" << endl;

    return 0;
}
