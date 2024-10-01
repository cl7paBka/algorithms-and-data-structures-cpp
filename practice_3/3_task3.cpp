#include <iostream>
#include <chrono> // Для замеров времени
#include <vector> // Для хранения цепочек решений

using namespace std;

// Рекурсивная функция для нахождения НОД с цепочкой решений
int gcd_recursive(int a, int b, int& recursive_calls, vector<pair<int, int>>& recursive_chain) {
    recursive_calls++; // Увеличиваем количество рекурсивных вызовов
    recursive_chain.push_back({a, b}); // Добавляем текущие значения в цепочку решений
    if (b == 0) return a; // Базовый случай
    return gcd_recursive(b, a % b, recursive_calls, recursive_chain); // Рекурсивный вызов
}

// Итеративная функция для нахождения НОД с цепочкой решений
int gcd_iterative(int a, int b, int& iterative_steps, vector<pair<int, int>>& iterative_chain) {
    iterative_steps = 0;
    while (b != 0) {
        iterative_steps++; // Увеличиваем количество шагов
        iterative_chain.push_back({a, b}); // Добавляем текущие значения в цепочку решений
        int temp = b;
        b = a % b;
        a = temp;
    }
    iterative_chain.push_back({a, b}); // Добавляем финальное значение
    return a;
}

int main() {
    int a, b;
    cout << "Введите два натуральных числа: ";
    cin >> a >> b;

    // Для рекурсивного метода
    int recursive_calls = 0;
    vector<pair<int, int>> recursive_chain; // Хранение цепочки решений для рекурсии
    auto start_recursive = chrono::high_resolution_clock::now(); // Начало замера времени
    int result_recursive = gcd_recursive(a, b, recursive_calls, recursive_chain);
    auto end_recursive = chrono::high_resolution_clock::now(); // Конец замера времени
    chrono::duration<double> time_recursive = end_recursive - start_recursive;

    // Для итеративного метода
    int iterative_steps = 0;
    vector<pair<int, int>> iterative_chain; // Хранение цепочки решений для итераций
    auto start_iterative = chrono::high_resolution_clock::now(); // Начало замера времени
    int result_iterative = gcd_iterative(a, b, iterative_steps, iterative_chain);
    auto end_iterative = chrono::high_resolution_clock::now(); // Конец замера времени
    chrono::duration<double> time_iterative = end_iterative - start_iterative;

    // Вывод результатов
    cout << "НОД (рекурсивно): " << result_recursive << " | НОД (итеративно): " << result_iterative << endl;
    cout << "Количество рекурсивных вызовов: " << recursive_calls << " | Количество шагов итераций: " << iterative_steps << endl;
    cout << "Время выполнения (рекурсивно): " << time_recursive.count() << " секунд" << " | Время выполнения (итеративно): " << time_iterative.count() << " секунд" << endl;
    cout << "Разница между количеством рекурсивных вызовов и количеством шагов итераций: " << abs(recursive_calls - iterative_steps) << endl;
    cout << "Разница во времени между двумя методами: " << abs(time_recursive.count() - time_iterative.count()) << " секунд" << endl;

    // Вывод цепочки решений для рекурсивного метода
    cout << "Цепочка решений (рекурсивно):" << endl;
    for (const auto& step : recursive_chain) {
        cout << "a = " << step.first << ", b = " << step.second << endl;
    }

    // Вывод цепочки решений для итеративного метода
    cout << "Цепочка решений (итеративно):" << endl;
    for (const auto& step : iterative_chain) {
        cout << "a = " << step.first << ", b = " << step.second << endl;
    }

    return 0;
}
