#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip> // Заголовочный файл для форматирования вывода
#include <chrono>  // Для более точного времени, с <ctime> возникли проблемы, не получалось найти точное время
#include <fstream> // Для работы с файлами
#include <sstream> // Для работы со строками

using namespace std;
using namespace std::chrono;

typedef double (*Func)(double);

double example_function(double x) { // Функция x**3 - x + e**(-x)
    return pow(x, 3) - x + exp(-x);
}

// Пассивный поиск (перебор)
pair<double, double> passive_search(Func f, double a, double b, double h, int& iterations, bool find_max, ostringstream& oss) {
    double extreme_x = a;
    double extreme_f = f(a);

    for (double x = a; x <= b; x += h) {
        iterations++;
        double current_f = f(x);
        if ((find_max && current_f > extreme_f) || (!find_max && current_f < extreme_f)) {
            extreme_f = current_f;
            extreme_x = x;
        }
    }

    return make_pair(extreme_x, extreme_f);
}

// Метод деления отрезка пополам
pair<double, double> bisection_method(Func f, double a, double b, double epsilon, vector<pair<double, double>>& steps, int& iterations, bool find_max, ostringstream& oss) {
    double a0 = a, b0 = b;
    int iter_count = 0;

    while ((b0 - a0) > epsilon) {
        iter_count++;
        
        double delta = (b0 - a0) / 10;
        double alpha0 = a0 + (b0 - a0) / 2 - delta;
        double beta0 = a0 + (b0 - a0) / 2 + delta;

        double f_alpha = f(alpha0);
        double f_beta = f(beta0);

        if ((find_max && f_alpha <= f_beta) || (!find_max && f_alpha >= f_beta)) {
            b0 = beta0;
        } 
        else {
            a0 = alpha0;
        }

        steps.push_back({(a0 + b0) / 2, f((a0 + b0) / 2)});
    }

    double extreme_x = (a0 + b0) / 2.0;
    iterations = iter_count;

    return make_pair(extreme_x, f(extreme_x));
}

// Метод золотого сечения
pair<double, double> golden_section_search(Func f, double a, double b, double epsilon, vector<pair<double, double>>& steps, int& iterations, bool find_max, ostringstream& oss) {
    const double phi = (1 + sqrt(5)) / 2;
    const double resphi = 2 - phi;

    double x1 = a + resphi * (b - a);
    double x2 = b - resphi * (b - a);
    double f1 = f(x1);
    double f2 = f(x2);
    int iter_count = 0;

    while (abs(b - a) > epsilon) {
        iter_count++;
        steps.push_back({x1, f1});
        if ((find_max && f1 < f2) || (!find_max && f1 > f2)) {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = a + resphi * (b - a);
            f1 = f(x1);
        } else {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = b - resphi * (b - a);
            f2 = f(x2);
        }
    }

    double extreme_x = (a + b) / 2.0;
    steps.push_back({extreme_x, f(extreme_x)});
    iterations = iter_count;
    return make_pair(extreme_x, f(extreme_x));
}

// Метод Фибоначчи
pair<double, double> fibonacci_search(Func f, double a, double b, double epsilon, vector<pair<double, double>>& steps, int& iterations, bool find_max, ostringstream& oss, int n = 1000) {
    vector<int> fib(n + 1, 1);
    for (int i = 2; i <= n; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    int k = 1;
    double delta0 = b - a;
    while (delta0 / fib[k + 1] > epsilon) {
        k++;
    }

    double a0 = a, b0 = b;
    double x1 = a0 + double(fib[k - 2]) / fib[k] * (b0 - a0);
    double x2 = a0 + double(fib[k - 1]) / fib[k] * (b0 - a0);
    double f1 = f(x1);
    double f2 = f(x2);
    int iter_count = 0;

    while (abs(b0 - a0) > epsilon) {
        iter_count++;
        steps.push_back({x1, f1});
        if ((find_max && f1 < f2) || (!find_max && f1 > f2)) {
            b0 = x2;
            x2 = x1;
            f2 = f1;
            x1 = a0 + double(fib[k - 2]) / fib[k] * (b0 - a0);
            f1 = f(x1);
        } else {
            a0 = x1;
            x1 = x2;
            f1 = f2;
            x2 = a0 + double(fib[k - 1]) / fib[k] * (b0 - a0);
            f2 = f(x2);
        }
        k--;
    }

    double extreme_x = (a0 + b0) / 2.0;
    steps.push_back({extreme_x, f(extreme_x)});
    iterations = iter_count;
    return make_pair(extreme_x, f(extreme_x));
}

// Вывод шагов метода
void print_steps(const vector<pair<double, double>>& steps, ostringstream& oss) {
    oss << "Шаги приближений (x, f(x)):\n";
    for (const auto& step : steps) {
        oss << "x = " << step.first << ", f(x) = " << step.second << endl;
    }
}

int main() {
    double a, b, epsilon, h;
    bool find_max;

    // Буфер для накопления вывода
    ostringstream oss;

    // Печатаем вопросы и считываем ответы
    oss << "Введите границы интервала [a, b]:\n";
    cout << oss.str();
    cin >> a >> b;
    oss << "Границы интервала [a, b]: " << a << " " << b << endl;

    oss << "Введите требуемую точность epsilon:\n";
    cout << oss.str();
    cin >> epsilon;
    oss << "Точность epsilon: " << epsilon << endl;

    oss << "Введите шаг для пассивного поиска h:\n";
    cout << oss.str();
    cin >> h;
    oss << "Шаг для пассивного поиска h: " << h << endl;

    oss << "Введите 1 для поиска максимума или 0 для поиска минимума:\n";
    cout << oss.str();
    cin >> find_max;
    oss << "Поиск максимума (1) или минимума (0): " << find_max << endl;

    // Время выполнения и количество итераций
    vector<pair<double, double>> steps_bisection, steps_fib, steps_golden;

    int iterations_passive = 0, iterations_bisection = 0, iterations_golden = 0, iterations_fib = 0;

    // Пассивный поиск
    auto start = high_resolution_clock::now();
    auto result_passive = passive_search(example_function, a, b, h, iterations_passive, find_max, oss);
    auto stop = high_resolution_clock::now();
    auto duration_passive = duration_cast<microseconds>(stop - start);

    oss << "\nМетод пассивного поиска:\n";
    oss << "Экстремум x = " << result_passive.first << ", f(x) = " << result_passive.second << endl;
    oss << "Время выполнения: " << duration_passive.count() / 1e6 << " сек\n";
    oss << "Количество итераций: " << iterations_passive << endl;

    // Метод деления отрезка пополам
    start = high_resolution_clock::now();
    auto result_bisection = bisection_method(example_function, a, b, epsilon, steps_bisection, iterations_bisection, find_max, oss);
    stop = high_resolution_clock::now();
    auto duration_bisection = duration_cast<microseconds>(stop - start);

    oss << "\nМетод деления отрезка пополам:\n";
    print_steps(steps_bisection, oss);
    oss << "Экстремум x = " << result_bisection.first << ", f(x) = " << result_bisection.second << endl;
    oss << "Время выполнения: " << duration_bisection.count() / 1e6 << " сек\n";
    oss << "Количество итераций: " << iterations_bisection << endl;

    // Метод золотого сечения
    start = high_resolution_clock::now();
    auto result_golden = golden_section_search(example_function, a, b, epsilon, steps_golden, iterations_golden, find_max, oss);
    stop = high_resolution_clock::now();
    auto duration_golden = duration_cast<microseconds>(stop - start);

    oss << "\nМетод золотого сечения:\n";
    print_steps(steps_golden, oss);
    oss << "Экстремум x = " << result_golden.first << ", f(x) = " << result_golden.second << endl;
    oss << "Время выполнения: " << duration_golden.count() / 1e6 << " сек\n";
    oss << "Количество итераций: " << iterations_golden << endl;

    // Метод Фибоначчи
    start = high_resolution_clock::now();
    auto result_fib = fibonacci_search(example_function, a, b, epsilon, steps_fib, iterations_fib, find_max, oss);
    stop = high_resolution_clock::now();
    auto duration_fib = duration_cast<microseconds>(stop - start);

    oss << "\nМетод Фибоначчи:\n";
    print_steps(steps_fib, oss);
    oss << "Экстремум x = " << result_fib.first << ", f(x) = " << result_fib.second << endl;
    oss << "Время выполнения: " << duration_fib.count() / 1e6 << " сек\n";
    oss << "Количество итераций: " << iterations_fib << endl;

    // Вывод в файл
    ofstream file("output.txt");
    if (file.is_open()) {
        file << oss.str();
        file.close();
    } else {
        cerr << "Не удалось открыть файл для записи." << endl;
    }

    return 0;
}
