#include <iostream>
#include <cstdlib>
#include <ctime>

struct Node
{
    int val;
    Node* next;
    Node* prev;
    Node(int data) : val(data),  next(nullptr), prev(nullptr){};
};

int RandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// void CreateList(Node*& head, Node*& tail){

//     head = new Node(RandomInt(1,100)); //вроде переменная под это не нужна?
//     Node* current = head;

//     for(int i = 1; i < 100; i++){
//         Node* newNode = new Node(RandomInt(1, 100));
//         current->next = newNode;
//         newNode->prev = current;
//         current = newNode;
//     }

//     tail = current;

// }

void CreateList(Node*& head, Node*& tail){
    
    int size;
    std::cout << "Введите количество элементов: ";
    std::cin >> size;
    
    // Валидация хз
    while (size <= 0){
        std::cout << "Ошибка! Введите положительное целое число: ";
        std::cin >> size;
    }
    
    if (size % 2 != 0){
        size++;
        std::cout << "Размер списка изменён на чётное число: " << size << std::endl;
    }
    
    //первый узел
    head = new Node(RandomInt(1, 100));
    head->prev = nullptr;
    Node* current = head;

    // остальные
    for(int i = 1; i < size; i++){
        Node* newNode = new Node(RandomInt(1, 100));
        current->next = newNode;
        newNode->prev = current;
        current = newNode;
    }
    
    // Устанавливаем tail на последний узел
    tail = current;
    tail->next = nullptr;
    
    std::cout << "Создан двусвязный список из " << size << " элементов" << std::endl;
}

void CreateElement(Node*& head, Node*& tail, int index, int length){ //идем с ближайшего конца пока не найдем место для создания
    Node* newNode = new Node(RandomInt(1, 100));

    if(index <= 0){
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    }

    if(index >= length){
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        return;
    }

    Node* current = nullptr;

    if(index <= length / 2){
        int i = 0;
        current = head; 
        while(i!=index){ //&& current->next!=nullptr
            current = current->next;
            i++;
        }
    }else{
        int i = length;
        current = tail; 
        while(i!=index){ //&& current->prev!=nullptr
            current = current->prev;
            i--;
        }
    }

    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
}

void PrintList(Node* head, Node* tail, int length){//функция вывода листа с переносом на каждом 20м элементе списка. 
    std::cout<<"-------------------------------------\n"; //прямой вывод
    if(head == nullptr){
        std::cout<<"Список пусть"<<"\n";
        return;
    }else{
        
    int i = 0;
    Node* current = head;

    while(current != nullptr){
        i++;
        std::cout<<"№"<<i<<":"<<current->val<<", "<<(i % 20 == 0 ? "\n" : "");
        current = current->next;
    }
    std::cout<<"\n";
    std::cout<<"-------------------------------------\n"; //обратный вывод

    i = length+1;
    Node* current2 = tail;

    while(current2 != nullptr){
        i--;
        std::cout<<"№"<<i<<":"<<current2->val<<", "<<(i % 20 == 0 ? "\n" : "");
        current2 = current2->prev;
    }
}};

void PrintElement(Node* head, Node* tail, int index, int length){
    if(index < 0 || index >= length){
        std::cout<<"Элемента по индексу "<<index-1<<" не сущесвтует \n";}
    else{
        Node* current = head;
        for(int i = 0; i< index; i++){
            current = current->next;
        }
        std::cout<<"Элемент по индексу "<<index-1<<" : "<<current->val<<"\n";
    }
}

void DeleteElement(Node*& head, Node*& tail, int index, int length){

    if(index < 0 || index >= length){std::cout<<"Неверный индекс элемента находится за пределами списка"; return;}
    if (head == nullptr){
        std::cout<<"Списка не существует!\n";
        return;
    }

    if (index == 0){ //удаление нулевого элемента
        Node* temp = head;
        head->next->prev = nullptr; //рубим связь с первым
        head = head->next;
        delete temp;
        return;
    }

    if(index == length-1){
        Node* temp = tail;
        tail->prev->next = nullptr;
        tail = tail->prev;
        delete temp;
        return;
    }

    if(index <= length / 2){
        Node* current = head;
        int tempIndex = 0;
        while(current != nullptr && tempIndex < index-1){
            current = current->next;
            tempIndex ++;
        }
        if (current == nullptr || current->next == nullptr) {
            std::cout << "Элемент не найден\n";
            return;}
        else{ //после проверок перезаписываем ссылку предыдущего current на элемент после удаляемого.
            Node* toDelete = current->next;
            current->next = toDelete->next;
            toDelete->next->prev = current; //немного непонятно, но если нет ошибки то некритично
            delete toDelete;
    }
    }else{
        Node* current = tail;
        int tempIndex = length;

        while(current != nullptr && tempIndex > index+1){ //возможно нужно убрать единицу ?
            current = current->prev;
            tempIndex --;
        }
        if (current == nullptr || current->prev == nullptr){
            std::cout << "Элемент не найден\n";
            return;}
        else{ //после проверок перезаписываем ссылку предыдущего current на элемент после удаляемого.
            Node* toDelete = current->prev;
            current->prev = current->prev->prev;
            current->prev->prev->next = current; //все те же танцы с бубном, хочется лучше и красивее но может потом
            delete toDelete;
        }
    }
}

void DeleteList(Node*& head, Node*& tail){ //не могу вставить сюда с ctrl+c втф. тут в удалении вроде все ок
    while(head != nullptr){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    std::cout<<"Лист был удален"<<"\n";
    
};

int CountLength(Node* head){//считаем кол-во элементов. все ок вроде
    if(head == nullptr){return 0;}else{
    Node* current = head;
    int length=0;

    while(current != nullptr){
        current = current->next;
        length++;
    }
    return length;};
};

void TaskSum(Node* head, Node* tail, int length) {
    
    int n = length / 2;
    if (n == 0) {
        std::cout << "Недостаточно элементов для составления пар! \n"; //такое вообще невозможно но пусть будет
        return;
    }
    
        Node* left = head;
    Node* right = tail;
    
    int minSum = left->val + right->val;
    int minIndex = 1;
    
    std::cout << "Пары и их суммы:\n";
    
    for (int i = 0; i < n; i++) {
        int currentSum = left->val + right->val;
        std::cout << "Пара " << (i+1) << ": " 
                  << left->val << " + " << right->val 
                  << " = " << currentSum << "\n";
        
        if (currentSum < minSum) {
            minSum = currentSum;
            minIndex = i + 1;
        }
        
        // Двигаемся навстречу друг другу
        left = left->next;
        right = right->prev;
    }
    
    std::cout << "\n Минимальная сумма: " << minSum 
              << " (пара №" << minIndex << ")\n";
}


int main() {

    bool Working = true; // работаем в цкиле до ввода команды на выход 
    srand(time(0));
    int length=0;
    Node* head = nullptr;
    Node* tail = nullptr;
    std::cout<<"Начало работы, номер команды из меню ниже\n";



    while (Working){

        std::cout<<"------------------------------------------------\n";
        std::cout<<"1. Создать список\n";
        std::cout<<"2. Создать элемент\n";
        std::cout<<"3. Удалить элемент\n";
        std::cout<<"4. Удалить список\n";
        std::cout<<"5. Распечатать элемент\n";
        std::cout<<"6. Распечатать список\n";
        std::cout<<"7. Завершить рабоут скрипта\n";
        std::cout<<"8. Выполнить задание \n";
        std::cout<<"------------------------------------------------\n";

        int choise;
        std::cin>>choise;

        switch (choise)
        {
        case 1: //"1. Создать список";
            {if(head == nullptr){
                CreateList(head, tail);
            }else{
                std::cout<<"Уже сущесвтует рабочий список\n";
            }}
            break;

        case 2: //"2. Создать элемент";
            if(head!=nullptr){ int userIndex;
            std::cin>>userIndex;
            CreateElement(head, tail, userIndex-1, length);}
            break;

        case 3: // "3. Удалить элемент";
            if(head!=nullptr){ int userIndex;
            std::cin>>userIndex;
            DeleteElement(head, tail, userIndex-1, length);}
            break;

        case 4: // "4. Удалить список";
            {if(head != nullptr){DeleteList(head, tail); length = 0;}
            else{
                std::cout<<"Списка не существует!\n";
            }};
            break;
            
        case 5: // "5. Распечатать 'элемент'";
            if(head != nullptr){int userIndex;
            std::cin>>userIndex;
            PrintElement(head, tail, userIndex-1, length);}else{
                std::cout<<"Списка не существует!\n";}
            break;

        case 6: // "6. Распечатать список";
            {if(head != nullptr){PrintList(head, tail, length); }else{
                std::cout<<"Списка не существует!\n";
            }}
            break;

        case 7: // "7. Завершить рабоут скрипта";
            {Working = false;}
            break;

        case 8: // "8. Выполнить задание";
            {if(head != nullptr){TaskSum(head, tail, length); }else{
                std::cout<<"Списка не существует!\n";
            }}
            break;

        default: //wrong command
            std::cout << "Неверный номер команды\n";
            break;
        };

        if(choise < 6 && head != nullptr){length = CountLength(head); PrintList(head, tail, length);}else{std::cout<<"\n";};

    }
    std::cout<<"Конец работы"<<"\n";
}
