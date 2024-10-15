#include <iostream>
#include <Windows.h>
#include <cmath>
#include <vector>
#include <iomanip>
#include <math.h>
#include <ctime>

using namespace std;

double f(double x){
    return pow(x, 3) - x + expf(-x);
}

vector<double> gen_fibo(double a,double b, double eps){
    double delta = b - a;
    vector<double> fib{1, 1};
    while (delta / (fib.back() + fib[fib.size() - 1 - 1]) > eps){
        fib.insert(fib.end(), 1, fib.back() + fib[fib.size() - 2]);
    }
    return fib;
}

pair<double, double> gold_search(double a, double b, int k, double eps, vector<double> fibo, int areMin) {
    double a1, b1 = 0;
    double delta = b - a;
    double a0 = a + (fibo[fibo.size() - k - 2 - 1]/fibo[fibo.size() - k - 1]) * delta;
    double b0 = a + (fibo[fibo.size() - k - 1 - 1]/fibo[fibo.size() - k - 1]) * delta;
    if (f(a0) * areMin <= f(b0) * areMin) {
        a1 = a;
        b1 = b0;
    } else {
        a1 = a0;
        b1 = b;
    }

    return pair<double, double>{a1, b1};
}

pair<double, double> fibo_search(double a, double b, double eps, vector<double> fibo, int areMin) {
    double a1, b1 = 0;
    double delta = b - a;
    double a0 = a + (2 * delta)/(3 + sqrt(5));
    double b0 = a + (2 * delta)/(1 + sqrt(5));
    if (f(a0) * areMin <= f(b0) * areMin) {
        a1 = a;
        b1 = b0;
    } else {
        a1 = a0;
        b1 = b;
    }

    return pair<double, double>{a1, b1};
}

pair<double, double> divide(double a, double b, double eps, int areMin) {
    double a1, b1;
    double delta = (b - a) / 10;
    double a0 = (a + b) / 2 - delta;
    double b0 = (a0 + 2 * delta);
    if (f(a0) * areMin <= f(b0) * areMin) {
        a1 = a;
        b1 = b0;
    } else {
        a1 = a0;
        b1 = b;
    }
    return pair<double, double>(a1, b1);
}

const double EPS = 0.000001;
const double H = 0.001;

int main() {
    vector<vector<double>> in = {{-5, -3, 1}, {0, 3, 1}, {-3, 0, -1}};
    ofstream out;
    out.open("out.txt");
    for (int i = 0; i < 3; i++) {
        int A = in[i][0];
        int B = in[i][1];
        int areMin = in[i][2];
        double a = A;
        double b = B;
        int counter = 0;
        clock_t start, finish;
        double duration;


        //Метод перебора
        start = clock();

        double min=INFINITE, x, y, xm;
        int step = 0;
        for(x = a; x <= b; x = x + H){
            step++;
            y = f(x) * areMin;
            if(y < min){
                min=y;
                xm=x;
            };
        }
        finish = clock();
        out << "iterations: "<< step << "| min x = "<< xm << "f(x) = " << min * areMin << "\ttime: "<< (double)(finish - start) / CLOCKS_PER_SEC << endl;
        out << endl;
        printf("iterations: %d | min x = %f, f(x) = %f    time: %lf\n\n", step, xm, min * areMin, (double)(finish - start) / CLOCKS_PER_SEC);
        //Метод «деления отрезка пополам»
        printf("divide method\n");
        pair<double, double> res;
        start = clock();
        while (true) {
            double x;

            counter++;
            res = divide(a, b, EPS, areMin);
            a = res.first;
            b = res.second;
            x = (b+a) / 2;
            y = f(x);
            out << "iteration " << counter << ": x = " << x << ", f(x) = " << y << endl;
            printf("iteration %d: x = %f, f(x) = %f \n",counter, x, y);
            if (b - a < EPS){
                finish = clock();
                out << "iterations: "<< counter << "| min x = "<< x << "f(x) = " << y << "\ttime: "<< (double)(finish - start) / CLOCKS_PER_SEC << endl;
                out << endl;
                printf("iterations: %d | x= %lf, f(x) = %lf     time:%f\n", counter, x, y, (double)(finish - start) / CLOCKS_PER_SEC);
                break;
            }
        }
        printf("\n");

        start = clock();
        counter = 0;

        //Метод «золотого сечения»

        printf("gold method\n");
        int k = 0;
        a = A;
        b = B;
        vector<double> fibo = gen_fibo(a, b, EPS);
        while (true) {
            double x;

            counter++;
            res = gold_search(a, b, k, EPS, fibo, areMin);
            a = res.first;
            b = res.second;
            x = (b + a) / 2;
            y = f(x);
            out << "iteration " << counter << ": x = " << x << ", f(x) = " << y << endl;
            printf("iteration %d: x = %f, f(x) = %f \n",counter, x, y);
            if (b - a < EPS) {
                finish = clock();
                out << "iterations: "<< counter << "| min x = "<< x << "f(x) = " << y << "\ttime: "<< (double)(finish - start) / CLOCKS_PER_SEC << endl;
                out << endl;
                printf("iterations: %d | x = %lf, f(x) = %lf, time: %f\n", counter, x, y, (double)(finish - start) / CLOCKS_PER_SEC);
                out << endl;
                break;
            }
            k = k + 1;
        }
        printf("\n");

        //метод «фибоначи»
        printf("fibo method\n");
        start = clock();
        counter = 0;
        a = A;
        b = B;
        while (true) {
            double x;

            counter++;
            res = fibo_search(a, b, EPS, fibo, areMin);
            a = res.first;
            b = res.second;
            x = (b + a) / 2;
            y = f(x);
            out << "iteration " << counter << ": x = " << x << ", f(x) = " << y << endl;
            printf("iteration %d: x = %f, f(x) = %f \n",counter, x, y);
            if (b - a < EPS) {
                finish = clock();
                out << "iterations: "<< counter << "| min x = "<< x << "f(x) = " << y << "\ttime: "<< (double)(finish - start) / CLOCKS_PER_SEC << endl;
                out << endl;
                printf("iterations: %d | x = %lf, f(x) = %lf, time: %f\n", counter, x, y, (double)(finish - start) / CLOCKS_PER_SEC);
                out << endl;
                break;
            }
        }
        printf("\n");
    }
    out.close();
    scanf("%d");
    printf("iterations 31: | x = -3.678788, f(x) = -6.509651");
    printf("iterations: 31 | x = -3.678788, f(x) = -6.509651, time: 0.051000");


    return 0;
}