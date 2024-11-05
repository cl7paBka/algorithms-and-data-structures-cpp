#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

// cтруктура для удобства возвращения результата
typedef struct Sort_result{
    vector<int> sortedArray;
    int comparisons;
    int swaps;
    double duration; 
}res_t;

// пузырьковая сортировка O(n**2)
res_t bubble_sort(vector<int>& arr){
    int comparisons = 0;
    int swaps = 0;
    auto time_start = chrono::high_resolution_clock::now();

    for (int i=0; i<arr.size()-1; i++){
        for (int j=i; j<arr.size()-1; j++){
            comparisons++;
            if (arr[j+1] > arr[j]){
                swap(arr[j+1], arr[j]);
                swaps++;
            }
        }
    }

    auto time_end = chrono::high_resolution_clock::now();
    float duration = chrono::duration<float>(time_end-time_start).count();

    return{arr, comparisons, swaps, duration};
}

res_t insertion_sort(vector<int>& arr) {
    int comparisons = 0;
    int swaps = 0;
    auto time_start = chrono::high_resolution_clock::now();

    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] < key) {
            comparisons++;
            arr[j + 1] = arr[j]; 
            j--;
            swaps++;
        }
        
        comparisons++;
        arr[j + 1] = key; 
        swaps++;
    }

    auto time_end = chrono::high_resolution_clock::now();
    float duration = chrono::duration<float>(time_end - time_start).count();

    return {arr, comparisons, swaps, duration};
}

// сортировка выбором O(n**2)
res_t selected_sort(vector<int>& arr){
    int comparisons = 0;
    int swaps = 0;
    auto time_start = chrono::high_resolution_clock::now();

    for (int i=0; i<arr.size(); i++){
        for (int j = i+1; j<arr.size(); j++){
            comparisons++;
            if (arr[j] > arr[i]){
                swap(arr[i], arr[j]);
                swaps++;
            }
        }
    }

    auto time_end = chrono::high_resolution_clock::now();
    float duration = chrono::duration<float>(time_end-time_start).count();

    return{arr, comparisons, swaps, duration};
}

void print_result(const string& name, const res_t& result){
    cout << name << ":\n";
    for (int num : result.sortedArray){ cout << num << " "; }

    cout << "\nСравнения: " << result.comparisons << ", Кол-во перемещения перем: " << result.swaps 
    << ", Время: " << result.duration << " секунд\n\n";
}

int main(){
    // открываю файл
    ifstream file("input.txt"); 
    // проверка
    if (!file){  cout << "Ошибка открытия файла" << endl; return 1; }

    vector<int> arr; // массив
    int number;

    // читаем числа
    while (file >> number){ arr.push_back(number); }

    file.close(); 


    vector<int> original_arr = arr; // копия массива
    // сортировки
    print_result("bubble Sort", bubble_sort(original_arr));

    original_arr = arr;
    print_result("selection Sort", selected_sort(original_arr));

    original_arr = arr;
    print_result("insertion Sort", insertion_sort(original_arr));

    return 0;
}
