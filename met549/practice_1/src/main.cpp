#include <iostream>
#include <vector>
using namespace std;

// метод для определения и удаления номера участника 
void count_people(int n, int m) {
    vector<int> people;
    int index = 0; 
    for (int i = 1; i <= n; i++) { people.push_back(i); }

    for(int i=0; i<n-1; i++){
        index = (index + m - 1) % people.size(); 
        people.erase(people.begin() + index); 
    }
    cout << "Оставшийся номер: ";
    for (int num : people) { cout << num << " "; }
    cout<<endl;
}

int main() {
    const int n = 20; 

    // цикл для удаления каждого участика под номером m 
    for (int m = 2; m <= 20; ++m) { 
        cout << "m = " << m<<" ";
        count_people(n, m);
    }
    cout<<endl;

    return 0;
}


