#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// чтение
void read_file(string& filename, vector<int>& numbers) {
    ifstream file(filename);
    if (!file.is_open()) { cerr << "Ошибка при открытии файла!" << endl; exit(1); }

    int number;
    while (file >> number) {
        numbers.push_back(number);
    }
}

// метод бинарного поиска
int binary_search(const vector<int>& numbers, int key, int& comparison) {
    int left = 0;
    int right = numbers.size() - 1;

    while (left <= right) {
        comparison++;
        int mid = left + (right - left) / 2;

        if (numbers[mid] == key) {
            return mid;
        } else if (numbers[mid] > key) { 
            left = mid + 1; // перемещение вправо
        } else {
            right = mid - 1; // перемещение влево
        }
    }
    return -1; // error
}


// метод линейного поиска
int linear_search(const vector<int>& numbers, int key, int& comparison) {
    for (int i = 0; i < numbers.size(); i++) {
        comparison++;
        if (numbers[i] == key) {
            return i;
        }
    }
    return -1; // error
}

int main() {
    string inputFile = "sorted_input.txt";

    vector<int> numbers;
    read_file(inputFile, numbers);
    
    // поиск
    int key;
    cout << "Введи число для поиска: ";
    cin >> key;

    int linearSearchCount = 0;
    int linearResult = linear_search(numbers, key, linearSearchCount);

    int binarySearchCount = 0;
    int binaryResult = binary_search(numbers, key, binarySearchCount);

    // вывод результатов поиска
    if (linearResult != -1) {
        cout << "Индекс от linear search: " << linearResult << " (" << linearSearchCount << " операции сравнения)" << endl;
    } else {
        cout << "Элемент не найден линейным поиском (" << linearSearchCount << " операции сравнения)" << endl;
    }

    if (binaryResult != -1) {
        cout << "Индекс от binary search: " << binaryResult << " (" << binarySearchCount << " операции сравнения)" << endl;
    } else {
        cout << "Элемент не найден бинарным поиском (" << binarySearchCount << " операции сравнения)" << endl;
    }

    return 0;
}
