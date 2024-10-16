#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <ctime>

using namespace std;

double function(double x){
    return pow(x, 3) - x + expf(-x);
}

pair<double, double> segments_devide(double a, double b, double eps, int max_or_min) {
    double a1, b1;
    double duration = (b - a) / 10;

    double a0 = (a + b) / 2 - duration;
    double b0 = (a0 + 2 * duration);

    if (function(a0) * max_or_min <= function(b0) * max_or_min) { a1 = a; b1 = b0; }
    else { a1 = a0; b1 = b; }

    return pair<double, double>(a1, b1);
}

pair<double, double> gold_search(double a, double b, int k, double eps, vector<double> fibo, int max_or_min) {
    double a1 = 0, b1 = 0;
    double duration = b - a;

    double a0 = a + (fibo[fibo.size() - k - 2 - 1]/fibo[fibo.size() - k - 1]) * duration;
    double b0 = a + (fibo[fibo.size() - k - 1 - 1]/fibo[fibo.size() - k - 1]) * duration;

    if (function(a0) * max_or_min <= function(b0) * max_or_min) { a1 = a; b1 = b0; }
    else { a1 = a0; b1 = b; }

    return pair<double, double>{a1, b1};
}

vector<double> generate_fibonacci(double a,double b, double eps){
    double duration = b - a;
    vector<double> fib{1, 1};

    while (duration / (fib.back() + fib[fib.size() - 1 - 1]) > eps){ fib.insert(fib.end(), 1, fib.back() + fib[fib.size() - 2]); }

    return fib;
}

pair<double, double> fibonacci_search(double a, double b, double eps, vector<double> fibo, int max_or_min) {
    double a1 = 0, b1 = 0;
    double duration = b - a;

    double a0 = a + (2 * duration)/(3 + sqrt(5));
    double b0 = a + (2 * duration)/(1 + sqrt(5));

    if (function(a0) * max_or_min <= function(b0) * max_or_min) { a1 = a; b1 = b0; }
    else { a1 = a0; b1 = b; }

    return pair<double, double>{a1, b1};
}

const double EPS = 1e-6;
const double H = 0.001;

int main() {
    // отрезки и макс(мин)
    vector<vector<double>> segments = {{-5, -3, 1}, {0, 3, 1}, {-3, 0, -1}};
    ofstream file("file.txt");

    // для ровного отображения(можно убрать)
    file << fixed << setprecision(5);

    
    for (int i = 0; i < 3; i++) {
        int iteration_for_met1=0,iteration_for_met2=0,iteration_for_met3=0,iteration_for_met4=0;

        int seg_start = segments[i][0];
        int seg_end = segments[i][1];
        int max_or_min = segments[i][2];

        double copy_seg_start = seg_start;
        double copy_seg_end = seg_end;
        clock_t clock_st, clock_end;
        double duration;


        //Метод перебора
        file<<"---bruteforce method, for segment "<< "["<<seg_start << "," << seg_end << "]" << endl;
        clock_st = clock();
        // min берем за большое число
        double x_value, y_value=1000000, x, y;
        for(x = copy_seg_start; x <= copy_seg_end; x += H){
            iteration_for_met1++;
            y = function(x) * max_or_min;
            if(y < y_value){
                y_value=y;
                x_value=x;
            };
        }
        clock_end = clock();
        file << "iterations(1-2000): ... x = ... f(x) = ..."<<endl;
        file<<"---res--------------------------------res---"<<endl;
        file << "iterations: "<< iteration_for_met1 << "\nmin x = "<< x_value << "\nf(x) = " << y_value * max_or_min << "\ntime: "<< (double)(clock_end - clock_st) / CLOCKS_PER_SEC << endl;
        file << endl;

        //Метод «деления отрезка пополам»
        file<<"---segments_devide method, for segment "<< "["<< seg_start << "," << seg_end << "]" << endl;
        pair<double, double> res;
        clock_st = clock();
        while (true) {
            double x;

            iteration_for_met2++;
            res = segments_devide(copy_seg_start, copy_seg_end, EPS, max_or_min);
            copy_seg_start = res.first;
            copy_seg_end = res.second;
            x = (copy_seg_end+copy_seg_start) / 2;
            y = function(x);
            file << "iteration " << iteration_for_met2 << ": x = " << x << ", f(x) = " << y << endl;
            if (copy_seg_end - copy_seg_start < EPS){
                clock_end = clock();
                file<<"---res--------------------------------res---"<<endl;
                file << "iterations: "<< iteration_for_met2 << "\nmin x = "<< x << "\nf(x) = " << y * max_or_min << "\ntime: "<< (double)(clock_end - clock_st) / CLOCKS_PER_SEC << endl;
                file << endl;
                break;
            }
        }
        file<<endl;

        clock_st = clock();

        //Метод «золотого сечения»

        file<<"---gold method, for segment "<< "["<<seg_start << "," << seg_end << "]" << endl;
        int k = 0;
        copy_seg_start = seg_start;
        copy_seg_end = seg_end;
        vector<double> fibonacci = generate_fibonacci(copy_seg_start, copy_seg_end, EPS);
        while (true) {
            double x;

            iteration_for_met3++;
            res = gold_search(copy_seg_start, copy_seg_end, k, EPS, fibonacci, max_or_min);
            copy_seg_start = res.first;
            copy_seg_end = res.second;
            x = (copy_seg_end + copy_seg_start) / 2;
            y = function(x);
            file << "iteration " << iteration_for_met3 << ": x = " << x << ", f(x) = " << y << endl;
            if (copy_seg_end - copy_seg_start < EPS) {
                clock_end = clock();
                file<<"---res--------------------------------res---"<<endl;
                file << "iterations: "<< iteration_for_met3 << "\nmin x = "<< x << "\nf(x) = " << y * max_or_min << "\ntime: "<< (double)(clock_end - clock_st) / CLOCKS_PER_SEC << endl;
                file << endl;
                file << endl;
                break;
            }
            k = k + 1;
        }
        file<<"\n";

        //метод «фибоначи»
        file<<"---fibo method, for segment "<< "["<<seg_start << "," << seg_end << "]" << endl;
        clock_st = clock();
        copy_seg_start = seg_start;
        copy_seg_end = seg_end;
        while (true) {
            double x;

            iteration_for_met4++;
            res = fibonacci_search(copy_seg_start, copy_seg_end, EPS, fibonacci, max_or_min);
            copy_seg_start = res.first;
            copy_seg_end = res.second;
            x = (copy_seg_end + copy_seg_start) / 2;
            y = function(x);
            file << "iteration " << iteration_for_met4 << ": x = " << x << ", f(x) = " << y << endl;
            if (copy_seg_end - copy_seg_start < EPS) {
                clock_end = clock();
                file<<"---res--------------------------------res---"<<endl;
                file << "iterations: "<< iteration_for_met4 << "\nmin x = "<< x << "\nf(x) = " << y * max_or_min << "\ntime: "<< (double)(clock_end - clock_st) / CLOCKS_PER_SEC << endl;
                file << endl;
                file << endl;
                break;
            }
        }
        file<<"\n";
    }
    file.close();

    // Вывод из файла
    ifstream file_for_out("file.txt");

    string line;
    while (getline(file_for_out, line)) {
        cout << line << endl;
    }

    file.close();
    return 0;
}