#include <iostream>
#include <chrono>

using namespace std;
    // счетчики для счета кол-ва итераций
    int cntIterative_for_task2, cntRecursive_for_task2, cntIterative_for_task3, cntRecursive_for_task3, cnt_for_task4;

// итеративная функция фибоначи
int fibonachi_iterative(int n) { 
    if (n <= 0){ cout<<"error: n has been positive"<<endl; exit(1); } 

    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) { 
        c = a + b;
        a = b; 
        b = c;
    }
    return b;
}
// рекурсивная функция фибоначи
int fibonachi_recursive(int n) { 
    if (n <= 0){ cout<<"error: n has been positive"<<endl; exit(1); } 
    if (n == 1 || n == 2) return 1; 
    
    return fibonachi_recursive(n-1) + fibonachi_recursive(n-2); 
}

// итеративная функция сочетаний
int combinations_iterative(int n, int k) {
    if (k==0 || k==n) { return 1; }

    int result = 1;
    
    for (int i=0; i<k; i++) {
        cntIterative_for_task2++;
        result *= (n - i);
        result /= (i + 1); 
    }

    return result;
}

// рекурсивная функция сочетаний
int combinations_recursive(int n, int m) {
    cntRecursive_for_task2+=1;
    if (m == 0 || m == n){ return 1; }
    return combinations_recursive(n - 1, m - 1) + combinations_recursive(n - 1, m);
}

// итеративная функция максимального делителя
int max_devider_iterative(int a, int b) {
    while (a!=0 && b!=0){
        cntIterative_for_task3+=1;
        if(a>b){
            a = a%b;
        } else{
            b=b%a;
        }
    }
    return a+b;
}
// рекурсивная функция максимального делителя
int max_devider_recursive(int a, int b) {
    cntRecursive_for_task3+=1;
    if (b == 0) { return a; }
    return max_devider_recursive(b, a % b);
}

// вспомогательная функция высчитывающая сумму кубов цифр
int sum_of_cubes_of_digits(string n) {
    int sum = 0;
    for (char c: n) {
        int digit = c - '0'; // преобразуем символ в число
        sum += digit * digit * digit; 
    }
    return sum;
}
// главная функция суммы кубов
string sum_of_cubes_main(string n) {
    while (true) {
        cnt_for_task4+=1;
        int sum = sum_of_cubes_of_digits(n);
        cout << "=>" << sum;

        if (sum == 153) {
            n = to_string(sum);break; 
        }
        n = to_string(sum); 
    }
    return n;
}

    // функция для получения из числа 1 числа 100 за наименьшее количество операций
    int cnt=0;
int executor(int start, int end){
    
    if(start==end) {
        cout<<"end\nКол-во операций: "<<cnt;
        return 0;
    } else if(end%2==0){
        end /= 2;
        cout<<end<<"-";
        cnt++;
    } else{
        end -=1;
        cout<<end<<"-";
        cnt++;
    }
    
    return executor(start, end);
}

int main() {
    // объявление переменных
    int n, m;
    string n_str, command1 = "+1", command2 = "*2";

    // задача 1
    cout << "Задача 1 - фибоначи\nВведите номер элемента: ";
    cin >> n;
    cout << fibonachi_iterative(n) << " - число под номером n (итеративно)" <<endl;
    cout << fibonachi_recursive(n) << " - число под номером n (рекурсивно)" <<endl<<endl<< endl << endl;

    
    // задача 2
    cout << "Задача 2 - сочетания\n!! n >= m !!\nВведите число n: ";
    cin >> n;
    cout << "Введите число m: ";
    cin >> m;
    // для подсчета времени(это старт рекурсивного и итеративного таймера)
    auto timeIterative_start_task2 = chrono::high_resolution_clock::now();
    auto timeRecursive_start_task2 = chrono::high_resolution_clock::now();if (n < m) { cout << "error: n должно быть меньше m." << endl; return 1; }
    cout << "----------------------\nЧисло сочетаний итеративно: " << combinations_iterative(n, m);
    cout << "\nКол-во итераций: " << cntIterative_for_task2;
    // для подсчета времени(это конец итеративного таймера)
    auto timeIterative_end_task2 = chrono::high_resolution_clock::now();
    // для подсчета времени(это старт вычисление продолжительности итеративного таймера)
    chrono::duration<double> durationIterative = timeIterative_end_task2 - timeIterative_start_task2;
    cout << "\tВремя выполнения итеративно: " << durationIterative.count() << "c" << endl;
cout << "----------------------\nЧисло сочетаний рекурсивно: " << combinations_recursive(n, m);
    cout << "\nКол-во итераций: " << cntRecursive_for_task2;
    // для подсчета времени(это конец рекурсивного таймера)
    auto timeRecursive_end_task2 = chrono::high_resolution_clock::now();
    // для подсчета времени(это старт вычисление продолжительности рекурсивного таймера)
    chrono::duration<double> durationRecursive_task2 = timeRecursive_end_task2 - timeRecursive_start_task2;
    cout << "\tВремя выполнения рекурсивно: " << durationRecursive_task2.count() << "c" << endl << endl << endl << endl;

    // задача 3
    cout << "Задача 3 - наибольший обший делитель\nВведите число a: ";
    cin >> n;
    cout << "Введите число b: ";
    cin >> m;

    // для подсчета времени(это старт рекурсивного и итеративного таймера)
    auto timeIterative_start_task3 = chrono::high_resolution_clock::now();
    auto timeRecursive_start_task3 = chrono::high_resolution_clock::now();
    cout<<"----------------------\nНаибольший общий делитель итеративно: " << max_devider_iterative(n,m);
    cout << "\nКол-во итераций: " << cntIterative_for_task3;
    // для подсчета времени(это конец итеративного таймера)
    auto timeIterative_end_task3 = chrono::high_resolution_clock::now();
    // для подсчета времени(это старт вычисление продолжительности итеративного таймера)
    chrono::duration<double> durationIterative_task3 = timeIterative_end_task3 - timeIterative_start_task3;
    cout << "\tВремя выполнения итеративно: " << durationIterative_task3.count() << "c" << endl;

    cout<<"----------------------\nНаибольший общий делитель рекурсивно: " << max_devider_recursive(n,m);
    cout << "\nКол-во итераций: " << cntIterative_for_task3;
    // для подсчета времени(это конец рекурсивного таймера)
    auto timeRecursive_end_task3 = chrono::high_resolution_clock::now();
    // для подсчета времени(это старт вычисление продолжительности рекурсивного таймера)
    chrono::duration<double> durationRecursive_task3 = timeRecursive_end_task3 - timeRecursive_start_task3;
    cout << "\tВремя выполнения рекурсивно: " << durationRecursive_task3.count() << "c" << endl << endl<< endl << endl;
    // analiz

    // задача 4
    cout << "Задача 4 - сумма кубов\nВведите число: ";
    cin >> n_str;
    cout<<n_str;
    sum_of_cubes_main(n_str);
    cout << "\nКол-во итераций: " << cnt_for_task4 <<endl<< endl << endl;
    // зависимость чем больше цифр в числе тем больше кол-во итераций

    // задача 5
    cout<< "Задача 5 - исполнитель\n";
    // старт и конец исполнителя
    int start = 1, end = 100;
    executor(start, end);
    cout<<endl;

    return 0;  
}

