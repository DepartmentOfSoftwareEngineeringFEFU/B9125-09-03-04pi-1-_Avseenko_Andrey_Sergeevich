#include <iostream>
#include <ctime>
#include <string>

struct Node
{
    char val;
    Node* next;
    Node(char data) : val(data), next(nullptr) {};
};

// Функция для проверки, является ли буква гласной
bool isVowel(char c)
{
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

// Функция для проверки, является ли буква согласной
bool isConsonant(char c)
{
    return isalpha(c) && !isVowel(c);
}

// Функция для добавления элемента в конец списка
void append(Node*& head, char data)
{
    Node* newNode = new Node(data);
    if (head == nullptr)
    {
        head = newNode;
        return;
    }
    newNode->next = head;
    head = newNode;

}

// Функция для вывода списка
void printList(Node* head)
{
    Node* current = head;
    while (current != nullptr)
    {
        std::cout << current->val << " ";
        current = current->next;
    }
    std::cout << "\n";
}

// Функция для удаления всех согласных из списка
void deleteConsonants(Node*& head)
{
    // Удаляем согласные в начале списка
    while (head != nullptr && isConsonant(head->val))
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    
    if (head == nullptr) return;
    
    // Удаляем согласные в середине и конце списка
    Node* current = head;
    while (current->next != nullptr)
    {
        if (isConsonant(current->next->val))
        {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        else
        {
            current = current->next;
        }
    }
}

// Функция для освобождения памяти
void clearList(Node*& head){
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Генерация случайной буквы английского алфавита + побитовый переход на рандомную букву
char RandomChar(){return 'a' + rand() % 26;} 

int main()
{
    srand(time(NULL));//для рандома
    
    int length;
    std::cout << "Введите длину списка: ";
    std::cin >> length;
    
    if (length <= 0)
    {
        std::cout << "Неверная длина списка!\n";
        return 1;
    }
    
    // Создание списка
    Node* head = nullptr;
    for (int i = 0; i < length; i++)
    {append(head, RandomChar());}
    
    std::cout << "Исходный список: ";
    printList(head);
    
    // Удаление согласных
    deleteConsonants(head);
    
    std::cout << "Список после удаления согласных: ";
    printList(head);
    
    // Очистка памяти
    clearList(head);
    
    return 0;
}