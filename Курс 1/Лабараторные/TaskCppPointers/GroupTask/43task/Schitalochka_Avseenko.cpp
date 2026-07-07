#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

struct Node {
    std::string data;
    Node* next;
    
    Node(std::string value) : data(value), next(nullptr) {}
};

struct CircularList {
    Node* head;
    Node* tail;
    int size;
    
    CircularList() : head(nullptr), tail(nullptr), size(0) {}
    
    void insert(int index, std::string value) {
        Node* newNode = new Node(value);
        
        if (!head) {
            head = tail = newNode;
            newNode->next = head;
            size++;
            return;
        }
        
        if (index <= 0) {
            newNode->next = head;
            head = newNode;
            tail->next = head;
            size++;
            return;
        }
        
        Node* current = head;
        int currentIndex = 0;
        
        do {
            if (currentIndex == index - 1 || currentIndex >= size - 1) {
                newNode->next = current->next;
                current->next = newNode;
                if (current == tail) {
                    tail = newNode;
                }
                size++;
                return;
            }
            current = current->next;
            currentIndex++;
        } while (current != head);
        
        // Если индекс больше размера списка, добавляем в конец
        newNode->next = head;
        tail->next = newNode;
        tail = newNode;
        size++;
    }
    
    void remove(int index){
        if (!head || size == 0) return;
        
        // Если удаляем единственный элемент
        if (size == 1){
            delete head;
            head = tail = nullptr;
            size = 0;
            return;
        }
        
        // Если удаляем первый элемент
        if (index <= 0) {
            Node* toDelete = head;
            head = head->next;
            tail->next = head;
            delete toDelete;
            size--;
            return;
        }
        
        // Ищем элемент перед удаляемым
        Node* current = head;
        int currentIndex = 0;
        
        do {
            if (currentIndex == index - 1) {
                Node* toDelete = current->next;
                current->next = toDelete->next;
                
                if (toDelete == tail) {
                    tail = current;
                }
                if (toDelete == head) {
                    head = toDelete->next;
                }
                
                delete toDelete;
                size--;
                return;
            }
            current = current->next;
            currentIndex++;
        } while (current != head);
    }
    
    void round(int wordsCount) {
        if (!head || size == 0) {
            std::cout << "Список пуст!\n";
            return;
        }
        
        if (size == 1) {
            std::cout << "Победитель: " << head->data << std::endl;
            return;
        }
        
        // Считаем от текущего head
        Node* current = head;
        Node* prev = tail;
        
        // Проходим wordsCount-1 шагов (так как считалка начинается с текущего)
        for (int i = 0; i < wordsCount - 1; i++) {
            prev = current;
            current = current->next;
        }
        
        std::cout << "Выбывает: " << current->data << std::endl;
        
        // Удаляем выбывшего
        if (current == head) {
            head = current->next;
        }
        prev->next = current->next;
        
        if (current == tail) {
            tail = prev;
        }
        
        delete current;
        size--;
        
        // Устанавливаем head на следующего после удаленного
        if (size > 0) {
            head = prev->next;
        }
    }
    
    void print(){
        if (!head || size == 0) {
            std::cout << "Список пуст\n";
            return;
        }
        
        Node* current = head;
        int index = 0;
        
        do {
            std::cout << index << ": " << current->data << std::endl;
            current = current->next;
            index++;
        } while (current != head);
        
        std::cout << "Всего участников: " << size << std::endl;
    }
    
    void clear(){
        if (!head) return;
        
        Node* current = head;
        Node* nextNode;
        
        do{
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head && size > 0);
        
        head = tail = nullptr;
        size = 0;
    }
    
    int getSize() const {
        return size;
    }
    
    ~CircularList(){
        clear();
    }
};

// Функция для подсчета слов в считалке
int countWords(const std::string& text) {
    int wordsCount = 0;
    
    for (size_t i = 0; i < text.length(); i++) {
        // Считаем разделители: пробел, запятая, восклицательный знак, точка
        if (text[i] == ' ' || text[i] == ',' || text[i] == '!' || text[i] == '.') {
            // Проверяем, что перед разделителем было слово (не просто последовательность разделителей)
            if (i > 0 && text[i-1] != ' ' && text[i-1] != ',' && text[i-1] != '!' && text[i-1] != '.') {
                wordsCount++;
            }
        }
    }
    
    // Проверяем последнее слово (если строка не заканчивается разделителем)
    size_t last = text.length() - 1;
    if (text.length() > 0 && text[last] != ' ' && text[last] != ',' && text[last] != '!' && text[last] != '.') {
        wordsCount++;
    }
    
    return wordsCount;

}

// Функция для добавления начальных участников
void addInitialPlayers(CircularList& list) {
    list.insert(0, "Андрей");
    list.insert(1, "Маша");
    list.insert(2, "Саша");
    list.insert(3, "Катя");
    list.insert(4, "Петя");
}

int main(){
    srand(time(0));
    
    CircularList list;
    std::string schitalka = "Эники, беники ели вареники, Эники, беники съели вареники, Эники, беники, хоп!";
    
    // Подсчет слов с помощью отдельной функции
    int wordsCount = countWords(schitalka);
    
    // Добавляем начальных участников
    addInitialPlayers(list);
    
    std::cout << schitalka << "\n";
    std::cout << "Считалочка в данной программе (количество слов = " << wordsCount << ")\n\n";
    
    // Выводим начальную очередь
    std::cout << "Начальная очередь участников:\n";
    list.print();
    std::cout << "\n";
    
    bool working = true;
    
    while (working) {
        std::cout << "------------------------------------------------\n";
        std::cout << "1. Добавить участника\n";
        std::cout << "2. Удалить участника\n";
        std::cout << "3. Распечатать список\n";
        std::cout << "4. Провести раунд\n";
        std::cout << "5. Очистить список (закончить игру)\n";
        std::cout << "6. Автономный режим (играть до победы)\n";
        std::cout << "7. Выход\n";
        std::cout << "------------------------------------------------\n";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                std::string name;
                int position;
                std::cout << "Введите имя участника: ";
                std::cin >> name;
                std::cout << "Введите позицию (0 - в начало, -1 - в конец): ";
                std::cin >> position;
                
                if (position < 0 || position >= list.getSize()) {
                    list.insert(list.getSize(), name);
                    std::cout << "Участник добавлен в конец списка\n";
                } else {
                    list.insert(position, name);
                    std::cout << "Участник добавлен на позицию " << position << "\n";
                }
                
                // Выводим текущую очередь после действия
                std::cout << "\nТекущая очередь:\n";
                list.print();
                break;
            }
            
            case 2: {
                if (list.getSize() == 0) {
                    std::cout << "Список пуст!\n";
                    break;
                }
                int index;
                std::cout << "Введите индекс участника для удаления: ";
                std::cin >> index;
                
                if (index >= 0 && index < list.getSize()) {
                    list.remove(index);
                    std::cout << "Участник удален\n";
                } else {
                    std::cout << "Неверный индекс!\n";
                }
                
                // Выводим текущую очередь после действия
                if (list.getSize() > 0) {
                    std::cout << "\nТекущая очередь:\n";
                    list.print();
                }
                break;
            }
            
            case 3: {
                list.print();
                break;
            }
            
            case 4: {
                if (list.getSize() == 0) {
                    std::cout << "Список пуст!\n";
                    break;
                }
                list.round(wordsCount);
                
                // Выводим текущую очередь после раунда
                if (list.getSize() > 0) {
                    std::cout << "\nТекущая очередь:\n";
                    list.print();
                }
                break;
            }
            
            case 5: {
                list.clear();
                std::cout << "Список очищен\n";
                break;
            }
            
            case 6: {
                if (list.getSize() == 0) {
                    std::cout << "Список пуст! Добавьте участников\n";
                    break;
                }
                
                std::cout << "Автономный режим начат!\n";
                while (list.getSize() > 1) {
                    std::cout << "\nТекущая очередь:\n";
                    list.print();
                    std::cout << "\nПроводим раунд...\n";
                    list.round(wordsCount);
                    std::cout << "Нажмите Enter для продолжения...";
                    std::cin.ignore();
                    std::cin.get();
                }
                
                if (list.getSize() == 1) {
                    std::cout << "\n--- ИГРА ОКОНЧЕНА ---\n";
                    std::cout << "Победитель: ";
                    list.print();
                }
                break;
            }
            
            case 7: {
                working = false;
                std::cout << "Программа сдохла\n";
                break;
            }
            
            default: {
                std::cout << "Неверный номер команды\n";
                break;
            }
        }
        
        std::cout << "\n";
    }
    
    return 0;
}