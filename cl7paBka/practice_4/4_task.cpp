#include <iostream>
#include <fstream>
#include <chrono> // для точного измерения времени

using namespace std;

// сортировка выбором
void selectionSort(int arr[], int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (arr[j] > arr[maxIdx]) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            swap(arr[i], arr[maxIdx]);
            swaps++;
        }
    }
}

// сортировка вставками
void insertionSort(int arr[], int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] < key) {
            comparisons++;
            arr[j + 1] = arr[j];
            j--;
            swaps++;
        }
        comparisons++; // Последнее сравнение в while
        arr[j + 1] = key;
        swaps++;
    }
}

// сортировка обменом (пузырьковая сортировка)
void bubbleSort(int arr[], int n, int& comparisons, int& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] < arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
            }
        }
    }
}

// вывод массива
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// чтение массива из файла
void readArrayFromFile(const string& filename, int arr[], int& size) {
    ifstream file(filename);
    if (!file) {
        cout << "Не удалось открыть файл " << filename << endl;
        exit(1);
    }

    size = 0;
    while (file >> arr[size]) {
        size++;
    }

    file.close();
}

int main() {
    const int N = 30; // Количество элементов массива
    int arr[N];
    int size;

    // считываем массив из файла
    readArrayFromFile("numbers.txt", arr, size);

    // копии массива для разных сортировок
    int arrSelection[N], arrInsertion[N], arrBubble[N];
    copy(arr, arr + size, arrSelection);
    copy(arr, arr + size, arrInsertion);
    copy(arr, arr + size, arrBubble);

    // сортировка выбором
    int comparisons = 0, swaps = 0;
    auto start = chrono::high_resolution_clock::now();
    selectionSort(arrSelection, size, comparisons, swaps);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> durationSelection = end - start;

    cout << "Сортировка выбором:\n";
    cout << "Количество сравнений: " << comparisons << endl;
    cout << "Количество пересылок: " << swaps << endl;
    cout << "Время выполнения: " << durationSelection.count() << " секунд" << endl;
    cout << "Отсортированный массив: ";
    printArray(arrSelection, size);
    cout << endl;

    // сортировка вставками
    comparisons = 0, swaps = 0;
    start = chrono::high_resolution_clock::now();
    insertionSort(arrInsertion, size, comparisons, swaps);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> durationInsertion = end - start;

    cout << "Сортировка вставками:\n";
    cout << "Количество сравнений: " << comparisons << endl;
    cout << "Количество пересылок: " << swaps << endl;
    cout << "Время выполнения: " << durationInsertion.count() << " секунд" << endl;
    cout << "Отсортированный массив: ";
    printArray(arrInsertion, size);
    cout << endl;

    // сортировка обменом
    comparisons = 0, swaps = 0;
    start = chrono::high_resolution_clock::now();
    bubbleSort(arrBubble, size, comparisons, swaps);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> durationBubble = end - start;

    cout << "Сортировка обменом:\n";
    cout << "Количество сравнений: " << comparisons << endl;
    cout << "Количество пересылок: " << swaps << endl;
    cout << "Время выполнения: " << durationBubble.count() << " секунд" << endl;
    cout << "Отсортированный массив: ";
    printArray(arrBubble, size);
    cout << endl;

    return 0;
}
