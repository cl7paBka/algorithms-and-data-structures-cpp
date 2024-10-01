#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Линейный поиск
int linearSearch(const vector<double>& arr, double key, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < arr.size(); i++) {
        comparisons++;
        if (arr[i] == key) {
            return i; // элемент найден, возвращаем индекс
        }
    }
    return -1; // элемент не найден
}

// Бинарный поиск
int binarySearch(const vector<double>& arr, double key, int& comparisons) {
    comparisons = 0;
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        comparisons++;
        int mid = (low + high) / 2;

        if (arr[mid] == key) {
            return mid; // элемент найден
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; // элемент не найден
}

// Функция сортировки пузырьком
void bubbleSort(vector<double>& arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]); // меняем элементы местами
                swapped = true;
            }
        }
        // Если ни одного обмена не было, массив отсортирован
        if (!swapped) break;
    }
}

// Функция для вывода массива
void printArray(const vector<double>& arr) {
    for (double elem : arr) {
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    // Ввод и вывод файлов
    ifstream inp("inp.txt");
    ofstream out("out.txt");

    if (!inp) {
        cerr << "Не удалось открыть входной файл!" << endl;
        return 1;
    }

    if (!out) {
        cerr << "Не удалось открыть выходной файл!" << endl;
        return 1;
    }

    vector<double> arr;
    double value;

    // Считывание массива из файла
    while (inp >> value) {
        arr.push_back(value);
    }
    inp.close();

    // Вывод исходного массива
    cout << "Исходный массив:" << endl;
    printArray(arr);

    // Пользователь вводит искомое значение
    double key;
    cout << "Введите элемент для поиска: ";
    cin >> key;

    // Линейный поиск
    int linearComparisons = 0;
    int linearIndex = linearSearch(arr, key, linearComparisons);
    if (linearIndex != -1) {
        cout << "Линейный поиск: элемент " << arr[linearIndex] << " найден на индексе " << linearIndex << endl;
    } else {
        cout << "Линейный поиск: элемент не найден" << endl;
    }
    cout << "Количество сравнений (линейный поиск): " << linearComparisons << endl;

    // Сортировка пузырьком для бинарного поиска
    bubbleSort(arr);

    // Вывод отсортированного массива для бинарного поиска
    cout << "Отсортированный массив для бинарного поиска:" << endl;
    printArray(arr);

    // Бинарный поиск
    int binaryComparisons = 0;
    int binaryIndex = binarySearch(arr, key, binaryComparisons);
    if (binaryIndex != -1) {
        cout << "Бинарный поиск: элемент " << arr[binaryIndex] << " найден на индексе " << binaryIndex << endl;
    } else {
        cout << "Бинарный поиск: элемент не найден" << endl;
    }
    cout << "Количество сравнений (бинарный поиск): " << binaryComparisons << endl;

    // Запись отсортированного массива в файл
    for (double elem : arr) {
        out << elem << " ";
    }
    out.close();

    return 0;
}
