#include <iostream>
#include <fstream>

struct Node {   
    char val;
    Node* next;
    Node(char data, Node* nextNode = nullptr) : val(data), next(nextNode) {}
};

void push(Node*& head, char symbol) {
    Node* newNode = new Node(symbol, head);
    head = newNode;
}

char pop(Node*& head) {
    if (head == nullptr) return '\0';
    
    Node* temp = head;
    char result = head->val;
    head = head->next;
    delete temp;
    
    return result;
}

bool isEmpty(Node* head) {
    return head == nullptr;
}

int main() {
    std::ifstream file("test.txt");
    
    if (!file.is_open()) {
        std::cout << "test.txt не найден\n";
        return 1;
    }
    
    std::cout << "Содержимое файла test.txt:\n";
    std::cout << "========================================\n";
    
    // первый проход по приколу чтоб красиво было 
    char ch;
    while (file.get(ch)){
        std::cout << ch;
    }
    
    std::cout << "\n========================================\n";
    std::cout << "Текст в обратном порядке:\n";
    std::cout << "========================================\n";
    
    file.clear();
    file.seekg(0); //возвращает readposition в начало ткст файла 
    
    // второй проход
    Node* stack = nullptr;
    
    while (file.get(ch)) {
        if (ch == '\n'){ //до конца строки
            // Вывод строкии в обратном пордяке
            while (!isEmpty(stack)) {
                std::cout << pop(stack); //можно сделать лямбда функцию на переброс на пробеле каждого Nого слова но мне лень 
            }
            std::cout << '\n';
        } else {
            push(stack, ch);
        }
    }
    
    // Последняя строка тк там нет \n на конце строки
    while (!isEmpty(stack)) {
        std::cout << pop(stack);
    }
    std::cout << '\n';
    
    std::cout << "========================================\n";
    
    file.close();
    return 0;
}