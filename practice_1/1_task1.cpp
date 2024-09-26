#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 20;  

    // исходный список участников
    vector<int> initial_list;
    for (int i = 1; i <= n; ++i) {
        initial_list.push_back(i);
    }

    // цикл по m от 2 до 20 не включиттельно
    for (int m = 2; m <= 20; ++m) { 
        // создание списка участников для каждого значения m
        vector<int> a = initial_list;
        int index = 0;  // индекс для текущего участника
        int current_n = n;  // текущее количество участников

        // цикл, пока не останется один участник
        while (current_n > 1) {
            // индекс выбывающего участника
            index = (index + m - 1) % current_n;

            // удаление выбывающего участника
            a.erase(a.begin() + index);

            // уменьшение количества участников
            current_n--;
        }

        cout << "Для m=" << m << ", последний оставшийся участник: " << a[0] << endl;
    }

    return 0;
}
