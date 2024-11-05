// Задача №1.
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

typedef struct Node{
    string word;
    Node* next;
}node_t;


class Stack{
private:
    node_t* top;

public:
    // конструктор
    Stack(): top(nullptr) {}

    // деструктор для уничтодения объектов
    ~Stack() {
        while(top){ pop(); }
    }

    // методы
    void push(string word) {
        node_t* new_node = new node_t{word, top};
        top = new_node;
    }

    void pop() {
        if (top) {
            node_t* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void printStack(){
        node_t* current = top;
        while (current) {
            cout << current->word << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    Stack stack;
    string sentence = "Разработать алгоритм и программу умножения двух целочисленных матриц.";
    istringstream words(sentence);

    string word;

    // Разбиваем предложение на слова и помещаем их в стек
    while (words >> word){ stack.push(word); }

    // Вывод
    stack.printStack();

    return 0;
}
// Задача №2.

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

int main() {
    const int numStages = 5;
    const int numCommands = 10;
    vector<queue<string>> pipeline(numStages);
    vector<string> commands;

    // Инициализация команд
    for (int i = 1; i <= numCommands; ++i) {
        commands.push_back("Команда " + to_string(i));
    }

    int cycle = 1;
    int cmdIndex = 0;
    
    while (cmdIndex < numCommands || !pipeline[numStages - 1].empty()) {
        
        if (cmdIndex < numCommands) {
            pipeline[0].push(commands[cmdIndex]);
            cmdIndex++;
        }

        
        for (int stage = numStages - 1; stage > 0; --stage) {
            if (!pipeline[stage - 1].empty()) {
                pipeline[stage].push(pipeline[stage - 1].front());
                pipeline[stage - 1].pop();
            }
        }

        cout << "Цикл " << cycle << ": ";
        for (int stage = 0; stage < numStages; ++stage) {
            if (!pipeline[stage].empty()) {
                cout << "С" << (stage + 1) << " [" << pipeline[stage].front() << "] ";
            } else {
                cout << "С" << (stage + 1) << "[ пусто] ";
            }
        }
        cout << endl;

        if (!pipeline[numStages - 1].empty()) {
            cout << pipeline[numStages - 1].front() << " завершена." << endl;
            pipeline[numStages - 1].pop();
        }

        cycle++;
    }

    return 0;
}
