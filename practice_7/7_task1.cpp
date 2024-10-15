#include <iostream>

using namespace std;

// Структура для представления узла
struct Node {
    int data;    // значение узла (номер участника)
    Node *next;  // указатель на следующий узел
};

// Функция для инициализации кольцевого списка
Node* Init_Circle(int n) {
    Node *head = new Node; // создаем первый узел
    head->data = 1;        // присваиваем значение первому участнику
    Node *prev = head;
    
    // Создаем узлы для остальных участников
    for (int i = 2; i <= n; i++) {
        Node *new_node = new Node;
        new_node->data = i;
        prev->next = new_node;
        prev = new_node;
    }
    
    prev->next = head; // замыкаем список на первый узел
    return head;
}

// Функция для удаления узла с шагом m и нахождения последнего участника
int Josephus_Circle(Node *head, int m) {
    Node *current = head;
    Node *prev = nullptr;
    
    // Процесс удаления узлов, пока не останется один
    while (current->next != current) {
        // Пробегаем m-1 шагов
        for (int i = 1; i < m; i++) {
            prev = current;
            current = current->next;
        }
        
        // Удаляем текущий узел
        prev->next = current->next;
        delete current;
        current = prev->next;
    }
    
    int last_person = current->data;
    delete current; // удаляем последний узел
    return last_person;
}

int main() {
    int n = 20;  // количество участников
    
    // Для каждого m от 2 до 20 выводим результат
    for (int m = 2; m <= 20; m++) {
        Node *circle = Init_Circle(n);  // создаем новый список для каждого m
        int last_person = Josephus_Circle(circle, m);
        cout << "При m = " << m << " последний оставшийся участник: " << last_person << endl;
    }

    return 0;
}
