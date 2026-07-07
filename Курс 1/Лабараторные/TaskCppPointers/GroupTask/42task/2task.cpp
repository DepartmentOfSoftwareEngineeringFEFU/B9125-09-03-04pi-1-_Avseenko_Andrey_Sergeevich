#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

// Структура клиента (человека в очереди)
struct Customer {
    std::string firstName;
    std::string lastName;
};

// Узел двусвязного списка
struct Node {
    Customer* customer;
    Node* next;
    Node* prev;
    Node(Customer* cust) : customer(cust), next(nullptr), prev(nullptr) {}
};

// Функция для случайного решения с заданным процентом
bool chance(int percent) {
    return (std::rand() % 100) < percent;
}

// Функция фейк-таймер с обратным отсчетом
void startTimer(int seconds, const std::string& message, const std::string& customerName) {
    std::cout << message << customerName << "\n";
    
    for (int i = seconds; i > 0; i--) {
        std::cout << "\r" << i << ".. " << std::flush;
        for (int delay = 0; delay < 100000000; delay++);
    }
    std::cout << "\r0!   \n";
}

// Добавление человека в очередь (в конец списка)
void enqueue(Node*& head, Node*& tail, Customer* customer) {
    Node* newNode = new Node(customer);
    
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    
    startTimer(5, "Стиральная машина освобождается... ", customer->firstName + " " + customer->lastName + " встает в очередь");
    std::cout << "[INQUE] " << customer->firstName << " " << customer->lastName << " добавлен в очередь!\n";
}

// Удаление человека из очереди (из начала)
Customer* dequeue(Node*& head, Node*& tail){ 
    //функция возвращает указатель на объект структуры чтобы когда в мейн я ее сносил я мог получить доступ к его данным перед удалением 
    if (head == nullptr) {
        std::cout << "Очередь пуста, некого обслуживать!\n";
        return nullptr;
    }
    
    Node* temp = head;
    Customer* servicedCustomer = temp->customer;
    
    startTimer(5, "Стирка... ", servicedCustomer->firstName + " " + servicedCustomer->lastName);
    std::cout << "[DONE] " << servicedCustomer->firstName << " " << servicedCustomer->lastName << " заканчивает стирку и идет домой!\n";
    
    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    
    delete temp;
    return servicedCustomer;
}

// Вывод всей очереди
void printQue(Node* head) {
    if (head == nullptr) {
        std::cout << "Очередь пуста\n";
        return;
    }
    
    std::cout << "\n===== ТЕКУЩАЯ ОЧЕРЕДЬ =====\n";
    Node* current = head;
    int position = 1;
    
    while (current != nullptr) {
        std::cout << position << ". " << current->customer->firstName << " " 
                  << current->customer->lastName << "\n";
        current = current->next;
        position++;
    }
    std::cout << "Всего в очереди: " << (position - 1) << " человек\n";
    std::cout << "===========================\n";
}

// Очистка всей очереди
void clearQueue(Node*& head, Node*& tail) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp->customer;
        delete temp;
    }
    tail = nullptr;
}

// Структура для хранения оставшихся в файле людей
struct FileCustomer {
    std::string firstName;
    std::string lastName;
    FileCustomer* next;
};

// Добавление челика в список файловых клиентов
void addFileCustomer(FileCustomer*& head, const std::string& firstName, const std::string& lastName) {
    FileCustomer* newCustomer = new FileCustomer;
    newCustomer->firstName = firstName;
    newCustomer->lastName = lastName;
    newCustomer->next = nullptr;
    
    if (head == nullptr) {
        head = newCustomer;
    } else {
        FileCustomer* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newCustomer;
    }
}

// Загрузка очереди из текстового файла test.txt
void loadQueue(Node*& head, Node*& tail, FileCustomer*& fileCustomers) {
    std::ifstream file("test.txt");
    
    if (!file.is_open()) {
        std::cout << "Файл test.txt не найден!\n";
        return;
    }
    
    std::string line;
    int loadedCount = 0;
    
    std::cout << "\n[LOAD] Загрузка первых 3х посетителей из файла test.txt...\n";
    
    while (std::getline(file, line)){
        if (line.empty()) continue;
        
        size_t start = 0;
        size_t commaPos;
        
        do {
            commaPos = line.find(',', start);
            
            std::string personStr;
            if (commaPos != std::string::npos) {
                personStr = line.substr(start, commaPos - start);
                start = commaPos + 1;
            } else {
                personStr = line.substr(start);
                start = std::string::npos;
            }
            
            while (!personStr.empty() && personStr.front() == ' ') personStr.erase(0, 1);
            while (!personStr.empty() && personStr.back() == ' ') personStr.pop_back();
            
            if (!personStr.empty()) {
                size_t spacePos = personStr.find(' ');
                if (spacePos != std::string::npos) {
                    std::string firstName = personStr.substr(0, spacePos);
                    std::string lastName = personStr.substr(spacePos + 1);
                    
                    while (!firstName.empty() && firstName.front() == ' ') firstName.erase(0, 1);//стирание пробелов до имени
                    while (!firstName.empty() && firstName.back() == ' ') firstName.pop_back();
                    while (!lastName.empty() && lastName.front() == ' ') lastName.erase(0, 1); // стирание пробелов до фамилии
                    while (!lastName.empty() && lastName.back() == ' ') lastName.pop_back();
                    
                    if (!firstName.empty() && !lastName.empty()) {
                        if (loadedCount < 3) {
                            // Добавляем в очередь первых 3х
                            Customer* newCustomer = new Customer();
                            newCustomer->firstName = firstName;
                            newCustomer->lastName = lastName;
                            
                            Node* newNode = new Node(newCustomer);
                            
                            if (head == nullptr) {
                                head = newNode;
                                tail = newNode;
                            } else {
                                tail->next = newNode;
                                newNode->prev = tail;
                                tail = newNode;
                            }
                            
                            loadedCount++;
                            std::cout << "  [INQUE] В очередь загружен: " << firstName << " " << lastName << "\n";
                        } else {
                            // Остальных сохраняем в список файловых клиентов
                            addFileCustomer(fileCustomers, firstName, lastName);
                            std::cout << "  [WAIT] В файле ожидает: " << firstName << " " << lastName << "\n";
                        }
                    }
                }
            }
        } while (commaPos != std::string::npos);
    }
    
    file.close();
    
    if (loadedCount > 0) {
        std::cout << "\n[INFO] В очередь загружено " << loadedCount << " человек из файла test.txt\n";
        if (fileCustomers != nullptr) {
            int waitingCount = 0;
            FileCustomer* temp = fileCustomers;
            while (temp != nullptr) {
                waitingCount++;
                temp = temp->next;
            }
            std::cout << "[INFO] В файле осталось " << waitingCount << " человек\n";
        }
    } else {
        std::cout << "[ERROR] Не удалось загрузить данные. Формат: Имя Фамилия, Имя Фамилия\n";
    }
}

// Добавление следующего человека из файла в очередь
void addNext(Node*& head, Node*& tail, FileCustomer*& fileCustomers) {
    if (fileCustomers == nullptr) {
        std::cout << "[ERROR] В файле не осталось людей!\n";
        return;
    }
    
    FileCustomer* temp = fileCustomers;
    std::string firstName = temp->firstName;
    std::string lastName = temp->lastName;
    fileCustomers = fileCustomers->next;
    delete temp;
    
    Customer* newCustomer = new Customer();
    newCustomer->firstName = firstName;
    newCustomer->lastName = lastName;
    
    enqueue(head, tail, newCustomer);
}

// Освобождение памяти списка файловых клиентов
void clearFileCustomers(FileCustomer*& fileCustomers) {
    while (fileCustomers != nullptr) {
        FileCustomer* temp = fileCustomers;
        fileCustomers = fileCustomers->next;
        delete temp;
    }
}

int main() {
    std::srand(42);
    
    Node* head = nullptr;
    Node* tail = nullptr;
    FileCustomer* fileCustomers = nullptr;
    
    bool working = true;
    int choice;
    bool autoMode = false;
    
    std::cout << "\n==================================================\n";
    std::cout << "     СИСТЕМА УПРАВЛЕНИЯ ОЧЕРЕДЬЮ В ПРАЧЕЧНУЮ      \n";
    std::cout << "==================================================\n";
    
    loadQueue(head, tail, fileCustomers);
    printQue(head);
    
    while (working) {
        if (!autoMode) {
            std::cout << "\nВыберите действие:\n";
            std::cout << "  1. Автоматический режим (50% до конца)\n";
            std::cout << "  2. Обслужить человека (начать стирку)\n";
            std::cout << "  3. Добавить в очередь (следующий из файла)\n";
            std::cout << "  4. Показать текущую очередь\n";
            std::cout << "  5. Завершить работу программы\n";
            std::cout << "Ваш выбор: ";
            std::cin >> choice;
        }
        
        if (autoMode) {
            // В автоматическом режиме случайное событие 50/50
            bool service = chance(50);
            if (service) {
                std::cout << "\n[EVENT] Случайное событие: ОБСЛУЖИВАНИЕ\n";
                Customer* serviced = dequeue(head, tail);
                if (serviced != nullptr) delete serviced;
            } else {
                std::cout << "\n[EVENT] Случайное событие: ПОСТАНОВКА В ОЧЕРЕДЬ\n";
                addNext(head, tail, fileCustomers);
            }
            printQue(head);
            
            // Проверка на пустую очередь и отсутствие людей в файле
            if (head == nullptr && fileCustomers == nullptr) {
                std::cout << "\n[INFO] Очередь пуста и в файле нет людей. Программа завершается.\n";
                working = false;
            }
        } else {
            switch (choice) {
                case 1: {
                    autoMode = true;
                    std::cout << "\n[AUTO] Включен автоматический режим (50% до конца)\n";
                    break;
                }
                case 2: {
                    std::cout << "\n[ACTION] НАЧАЛО СТИРКИ:\n";
                    Customer* serviced = dequeue(head, tail);
                    if (serviced != nullptr) delete serviced;
                    printQue(head);
                    break;
                }
                case 3: {
                    std::cout << "\n[ACTION] ДОБАВЛЕНИЕ ИЗ ФАЙЛА:\n";
                    addNext(head, tail, fileCustomers);
                    printQue(head);
                    break;
                }
                case 4: {
                    printQue(head);
                    break;
                }
                case 5: {
                    working = false;
                    std::cout << "\n[EXIT] Завершение работы программы...\n";
                    break;
                }
                default: {
                    std::cout << "[ERROR] Неверный выбор!\n";
                    break;
                }
            }
        }
        
        if (working && !autoMode && head == nullptr && fileCustomers == nullptr && choice != 5) {
            std::cout << "\n[WARNING] Очередь пуста и в файле нет людей! Завершите программу.\n";
        }
    }
    
    clearQueue(head, tail);
    clearFileCustomers(fileCustomers);
    std::cout << "\nПрограмма отключается.\n";
    return 0;
}