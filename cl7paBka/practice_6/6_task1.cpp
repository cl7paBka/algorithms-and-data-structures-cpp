#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// Структура узла для стека
struct Node {
    string data;  // Слово
    Node* next;   // Указатель на следующий узел
};

// Класс для стека
class Stack {
private:
    Node* top;  // Указатель на верхний элемент стека

public:
    Stack() {
        top = nullptr;  // Инициализация пустого стека
    }

    // Функция для добавления элемента в стек
    void push(string word) {
        Node* newNode = new Node();  // Создаем новый узел
        newNode->data = word;        // Записываем слово
        newNode->next = top;         // Связываем новый узел с текущим верхним элементом
        top = newNode;               // Новый узел становится верхним элементом
    }

    // Функция для удаления элемента из стека
    string pop() {
        if (top == nullptr) {
            return "";  // Если стек пуст, возвращаем пустую строку
        }
        string word = top->data;     // Получаем верхний элемент
        Node* temp = top;            // Временный указатель для удаления узла
        top = top->next;             // Перемещаем указатель на следующий элемент
        delete temp;                 // Удаляем старый верхний узел
        return word;
    }

    // Функция для проверки, пуст ли стек
    bool isEmpty() {
        return top == nullptr;
    }
};

int main() {    
    // Исходное предложение
    string sentence = "Разработать алгоритм и программу умножения двух целочисленных матриц.";

    // Создаем стек
    Stack stack;

    // Разбиваем предложение на слова
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        stack.push(word);  // Заносим каждое слово в стек
    }

    // Выводим слова в прямом порядке
    cout << "Предложение в прямом порядке:" << endl;
    while (!stack.isEmpty()) {
        cout << stack.pop() << " ";  // Извлекаем слова из стека
    }
    cout << endl;

    return 0;
}
