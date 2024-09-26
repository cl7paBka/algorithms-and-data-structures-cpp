#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Рекурсивная функция для получения числа 100 с выводом цепочки решений
int min_operations(int current, int target, vector<int>& steps) {
    if (current > target) return 100; // Если превысили цель, возвращаем большое число
    if (current == target) return 0;  // Базовый случай: достигли цели

    // Сохраняем текущий шаг
    steps.push_back(current);

    // Пробуем оба варианта и выбираем минимальный путь
    vector<int> steps_add = steps; // Для варианта с +1
    vector<int> steps_mult = steps; // Для варианта с *2

    int add_one = min_operations(current + 1, target, steps_add);   // Пробуем +1
    int multiply_two = min_operations(current * 2, target, steps_mult); // Пробуем *2

    // Возвращаем минимальный путь и соответствующие шаги
    if (add_one < multiply_two) {
        steps = steps_add; // Если добавление 1 дало меньше шагов, выбираем этот путь
        return 1 + add_one;
    } else {
        steps = steps_mult; // Если умножение на 2 дало меньше шагов, выбираем этот путь
        return 1 + multiply_two;
    }
}

int main() {
    vector<int> steps; // Для хранения цепочки шагов
    int operations = min_operations(1, 100, steps); // Старт с 1 и цель — 100

    // Вывод результата
    cout << "Минимальное количество операций: " << operations << endl;

    // Вывод цепочки решений
    cout << "Цепочка решений: ";
    for (int step : steps) {
        cout << step << " -> ";
    }
    cout << 100 << endl; // Финальное число 100

    return 0;
}
