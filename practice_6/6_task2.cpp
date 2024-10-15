#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    queue<string> pipelineStages[5];  // Очереди для каждой стадии C1, C2, C3, C4, C5
    
    // Создаем массив команд
    string commands[] = {"Команда 1", "Команда 2", "Команда 3", "Команда 4", "Команда 5", 
                         "Команда 6", "Команда 7", "Команда 8", "Команда 9", "Команда 10"};

    int commandCount = 10;  // Количество команд
    
    // Процесс моделирования конвейера
    for (int cycle = 1; cycle <= commandCount + 4; ++cycle) {
        // Перемещаем команды по конвейеру
        for (int stage = 4; stage > 0; --stage) {
            if (!pipelineStages[stage-1].empty()) {
                string command = pipelineStages[stage-1].front();
                pipelineStages[stage-1].pop();
                pipelineStages[stage].push(command);
            }
        }

        // На первой стадии вызываем новую команду, если она существует
        if (cycle <= commandCount) {
            pipelineStages[0].push(commands[cycle - 1]);
        }

        // Если команда дошла до пятой стадии, выводим её
        if (!pipelineStages[4].empty()) {
            cout << pipelineStages[4].front() << " завершена на цикле " << cycle << endl;
            pipelineStages[4].pop();
        }
    }

    return 0;
}
