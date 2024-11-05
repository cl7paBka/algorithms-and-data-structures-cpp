#include <iostream>

using namespace std;


struct Data {
    int data;
};
struct Node {
    Data d;
    Node* next;
};

Node* list_circle(int n) {
    Node* head = new Node;
    head->d.data = 1;
    Node* prev = head;
    
    for (int i = 2; i <= n; i++) {
        Node* new_node = new Node;
        new_node->d.data = i;
        prev->next = new_node;
        prev = new_node;
    }
    
    prev->next = head;
    return head;
}

int josephus(Node* head, int m) {
    Node* current = head;
    Node* prev = nullptr;
    
    while (current->next != current) {
        for (int i = 1; i < m; i++) {
            prev = current;
            current = current->next;
        }
        
        prev->next = current->next;
        delete current;
        current = prev->next;
    }
    
    int last_person = current->d.data;
    delete current;
    
    return last_person;
}

int main() {
    int n = 20;

    for (int m = 2; m <= 20; m++) {
        Node* circle = list_circle(n);
        int last_person = josephus(circle, m);
        cout << "При m = " << m << " последний оставшийся участник: " << last_person << endl;
    }

    return 0;
}
