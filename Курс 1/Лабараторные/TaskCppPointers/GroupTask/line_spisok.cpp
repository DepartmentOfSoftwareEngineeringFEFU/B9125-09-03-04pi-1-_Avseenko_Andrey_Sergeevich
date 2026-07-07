#include <iostream>
#include <cstdlib>
#include <ctime>

struct Node
{
    int val;
    Node* next;
    Node(int data) : val(data),  next(nullptr) {};
};

int RandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// void CreateList(Node*& head){
    
//     head = new Node(RandomInt(1,100));
//     Node* current = head;

//     for(int i = 1; i < 100; i++ ){
//         int randomInt = RandomInt(1, 100);
//         current->next = new Node(randomInt);
//         current = current->next;
//     }
// }

void CreateList(Node*& head){
    
    int size;
    std::cout << "Введите количество элементов: ";
    std::cin >> size;
    
    // Валидация введенного значения
    while (size <= 0){
        std::cout << "Ошибка! Введите положительное целое число: ";
        std::cin >> size;
    }
    
    // Если число нечетное то докидываем
    
    head = new Node(RandomInt(1, 100));
    Node* current = head;

    for(int i = 1; i < size; i++){
        current->next = new Node(RandomInt(1, 100));
        current = current->next;
    }
}

void CreateElement(Node*& head, int index){ //идем с начала до конца пока не найдем место для создания
    Node* newNode = new Node(RandomInt(1, 100));

    if(index <= 0){
        newNode->next = head;
        head = newNode;
        return;
    }

    int i = 0; 
    Node* current = head;

    while(i!=index-1 && current->next!=nullptr){
        i++;
        current = current->next;
    }

    //если не сработает в создании за пределом спсика, то сюда проверку

    newNode->next = current->next;
    current->next = newNode;
}

void PrintList(Node* head){ //функция вывода листа с переносом на каждом 20м элементе списка. 
    if(head == nullptr){
        std::cout<<"Список пусть"<<"\n";
        return;
    }else{
        
    int i = 0;
    Node* current = head;
    while (current != nullptr) {
        i++;
        // Выводим в формате [дата_поле | адрес_элемента]
        std::cout << "[" << current->val << " | " << current << "]";
        
        // Добавляем запятую и пробел между элементами (кроме последнего)
        if (current->next != nullptr) {
            std::cout << ", ";
        }
        
        // Перенос строки на каждом 5 элементе
        if (i % 5 == 0) {
            std::cout << "\n";
        }
        
        current = current->next;
    }
    std::cout << "\n";
}};

void PrintElement(Node* head, int index, int length){
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


void DeleteElement(Node*& head, int index, int length){

    if(index < 0 || index >= length){std::cout<<"Неверный индекс элемента находится за пределами списка"; return;}
    if (head == nullptr){
        std::cout<<"Списка не существует!\n";
        return;
    }

    if (index == 0){ //удаление нулевого элемента
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

        Node* current = head;
        int tempIndex = 0;

        while(current != nullptr && tempIndex < index-1){
            current = current->next;
            tempIndex ++;
        }

        if (current == nullptr || current->next == nullptr) {
            std::cout << "Элемент не найден\n";
            return;}
        else{ //после проверок типа перезаписываем ссылку предыдущего current на элемент после удаляемого.
            Node* toDelete = current->next;
            current->next = toDelete->next;
            delete toDelete;
    }
}

void DeleteList(Node*& head){
    while(head != nullptr){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    std::cout<<"Лист был удален"<<"\n";
};

int CountLength(Node* head){
    if(head == nullptr){return 0;}else{
    Node* current = head;
    int length=0;

    while(current != nullptr){
        current = current->next;
        length++;
    }
    return length;};
};

int main() {

    bool Working = true; // работаем в цкиле до ввода команды на выход 
    srand(time(0));
    int length=0;
    Node* head = nullptr;
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
        std::cout<<"------------------------------------------------\n";

        int choise;
        std::cin>>choise;
        
        switch (choise)
        {
        case 1: //"1. Создать список";
            {if(head == nullptr){
                CreateList(head);
            }else{
                std::cout<<"Уже сущесвтует рабочий список\n";
            }}
            break;

        case 2: //"2. Создать элемент";
            if(head!=nullptr){ int userIndex;
            std::cin>>userIndex;
            CreateElement(head, userIndex-1);}
            break;

        case 3: // "3. Удалить элемент";
            if(head!=nullptr){ int userIndex;
            std::cin>>userIndex;
            DeleteElement(head, userIndex-1, length);}
            break;

        case 4: // "4. Удалить список";
            {if(head != nullptr){DeleteList(head); length = 0;}
            else{
                std::cout<<"Списка не существует!\n";
            }};
            break;
            
        case 5: // "5. Распечатать 'элемент'";
            if(head != nullptr){int userIndex;
            std::cin>>userIndex;
            PrintElement(head, userIndex-1, length);}else{
                std::cout<<"Списка не существует!\n";}
            break;

        case 6: // "6. Распечатать список";
            {if(head != nullptr){PrintList(head);}else{
                std::cout<<"Списка не существует!\n";
            }}
            break;

        case 7: // "7. Завершить рабоут скрипта";
            {Working = false;}
            break;

        default: //wrong command
            std::cout << "Неверный номер команды\n";
            break;
        };

        if(choise < 6 && head != nullptr){PrintList(head); length = CountLength(head); std::cout<<length;}else{std::cout<<"\n";};


    }
    std::cout<<"Конец работы"<<"\n";
}