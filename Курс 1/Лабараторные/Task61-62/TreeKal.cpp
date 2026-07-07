#include <iostream>
#include <fstream>
#include <string>

// Узел дерева
struct TreeNode {
    std::string data;  // Теперь храним строку вместо одного символа
    TreeNode* left;
    TreeNode* right;
};

// Стек для узлов дерева
struct StackNode {
    TreeNode* data;
    StackNode* next;
};

// Стек для строк (операторов и скобок)
struct StringStackNode {
    std::string data;
    StringStackNode* next;
};

// Функции для работы со стеком TreeNode*
TreeNode* top(StackNode*& stack) {
    if (stack == nullptr) return nullptr;
    return stack->data;
}

void push(StackNode*& stack, TreeNode* node) {
    StackNode* newNode = new StackNode;
    newNode->data = node;
    newNode->next = stack;
    stack = newNode;
}

TreeNode* pop(StackNode*& stack) {
    if (stack == nullptr) return nullptr;
    StackNode* temp = stack;
    TreeNode* data = temp->data;
    stack = stack->next;
    delete temp;
    return data;
}

bool isEmpty(StackNode* stack) {
    return stack == nullptr;
}

// Функции для работы со стеком string
std::string stringTop(StringStackNode*& stack) {
    if (stack == nullptr) return "";
    return stack->data;
}

void stringPush(StringStackNode*& stack, const std::string& s) {
    StringStackNode* newNode = new StringStackNode;
    newNode->data = s;
    newNode->next = stack;
    stack = newNode;
}

std::string stringPop(StringStackNode*& stack) {
    if (stack == nullptr) return "";
    StringStackNode* temp = stack;
    std::string data = temp->data;
    stack = stack->next;
    delete temp;
    return data;
}

bool stringIsEmpty(StringStackNode* stack) {
    return stack == nullptr;
}

// Создание узла дерева
TreeNode* createNode(const std::string& data) {
    TreeNode* node = new TreeNode;
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// Приоритет операторов
int precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

// Проверка: является ли символ оператором
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Проверка: является ли символ цифрой
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Проверка: является ли символ буквой
bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Проверка: может ли символ быть частью операнда
bool isOperandChar(char c) {
    return isDigit(c) || isLetter(c) || c == '.';
}

// Построение дерева синтаксического разбора из инфиксного выражения
TreeNode* buildParseTree(const std::string& expression) {
    StackNode* nodeStack = nullptr;
    StringStackNode* stringStack = nullptr;
    
    size_t i = 0;
    while (i < expression.length()) {
        char c = expression[i];
        
        // Пропускаем пробелы
        if (c == ' ') {
            i++;
            continue;
        }
        
        // Если цифра или буква - считываем весь операнд
        if (isDigit(c) || isLetter(c)) {
            std::string operand;
            while (i < expression.length() && isOperandChar(expression[i])) {
                operand += expression[i];
                i++;
            }
            push(nodeStack, createNode(operand));
            continue;
        }
        
        // Если оператор или скобка
        if (c == '(') {
            stringPush(stringStack, "(");
        }
        else if (c == ')') {
            // Выталкиваем операторы до открывающей скобки
            while (!stringIsEmpty(stringStack) && stringTop(stringStack) != "(") {
                std::string op = stringPop(stringStack);
                
                TreeNode* right = pop(nodeStack);
                TreeNode* left = pop(nodeStack);
                
                TreeNode* opNode = createNode(op);
                opNode->left = left;
                opNode->right = right;
                
                push(nodeStack, opNode);
            }
            // Удаляем '(' из стека
            if (!stringIsEmpty(stringStack)) {
                stringPop(stringStack);
            }
        }
        else if (isOperator(c)) {
            std::string op(1, c);
            // Выталкиваем операторы с большим или равным приоритетом
            while (!stringIsEmpty(stringStack) && stringTop(stringStack) != "(" &&
                   precedence(stringTop(stringStack)) >= precedence(op)) {
                std::string topOp = stringPop(stringStack);
                
                TreeNode* right = pop(nodeStack);
                TreeNode* left = pop(nodeStack);
                
                TreeNode* opNode = createNode(topOp);
                opNode->left = left;
                opNode->right = right;
                
                push(nodeStack, opNode);
            }
            stringPush(stringStack, op);
        }
        i++;
    }
    
    // Обрабатываем оставшиеся операторы
    while (!stringIsEmpty(stringStack)) {
        std::string op = stringPop(stringStack);
        
        TreeNode* right = pop(nodeStack);
        TreeNode* left = pop(nodeStack);
        
        TreeNode* opNode = createNode(op);
        opNode->left = left;
        opNode->right = right;
        
        push(nodeStack, opNode);
    }
    
    TreeNode* root = pop(nodeStack);
    return root;
}

// Прямой обход (префиксный): корень -> левое -> правое
void preorderTraversal(TreeNode* node, std::string& result) {
    if (node == nullptr) return;
    
    result += node->data;
    result += " ";
    
    preorderTraversal(node->left, result);
    preorderTraversal(node->right, result);
}

// Обратный обход (постфиксный): левое -> правое -> корень
void postorderTraversal(TreeNode* node, std::string& result) {
    if (node == nullptr) return;
    
    postorderTraversal(node->left, result);
    postorderTraversal(node->right, result);
    
    result += node->data;
    result += " ";
}

// Симметричный обход (инфиксный): левое -> корень -> правое
void inorderTraversal(TreeNode* node, std::string& result) {
    if (node == nullptr) return;
    
    // Добавляем скобки для наглядности, если узел - оператор
    bool addParentheses = (node->data == "+" || node->data == "-" || 
                          node->data == "*" || node->data == "/");
    
    if (addParentheses) result += "( ";
    
    inorderTraversal(node->left, result);
    
    result += node->data;
    result += " ";
    
    inorderTraversal(node->right, result);
    
    if (addParentheses) result += ") ";
}

// Вывод дерева на экран (рекурсивно с отступами)
void printTree(TreeNode* node, int level, const std::string& prefix) {
    if (node == nullptr) return;
    
    // Вывод правого поддерева (сверху)
    printTree(node->right, level + 1, "    ");
    
    // Вывод текущего узла с отступом
    for (int i = 0; i < level; i++) {
        std::cout << "    ";
    }
    if (!prefix.empty()) {
        std::cout << prefix;
    }
    std::cout << node->data << std::endl;
    
    // Вывод левого поддерева (снизу)
    printTree(node->left, level + 1, "    ");
}

// Удаление дерева
void deleteTree(TreeNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Очистка стека узлов
void clearStack(StackNode*& stack) {
    while (!isEmpty(stack)) {
        TreeNode* node = pop(stack);
        deleteTree(node);
    }
}

// Очистка строкового стека
void clearStringStack(StringStackNode*& stack) {
    while (!stringIsEmpty(stack)) {
        stringPop(stack);
    }
}

int main() {
    std::string expression;
    
    std::cout << "Введите арифметическое выражение в инфиксной форме: ";
    std::getline(std::cin, expression);
    
    // Построение дерева
    TreeNode* root = buildParseTree(expression);
    
    if (root == nullptr) {
        std::cout << "Ошибка: некорректное выражение!\n";
        return 1;
    }
    
    // Вывод дерева на экран
    std::cout << "\nДерево синтаксического разбора:\n";
    std::cout << "--------------------------------\n";
    printTree(root, 0, "");
    std::cout << "--------------------------------\n";
    
    // Выполнение обходов
    std::string preorderResult;
    std::string inorderResult;
    std::string postorderResult;
    
    preorderTraversal(root, preorderResult);
    inorderTraversal(root, inorderResult);
    postorderTraversal(root, postorderResult);
    
    // Вывод результатов на экран
    std::cout << "\nРезультаты обходов:\n";
    std::cout << "Прямой обход (префиксный): " << preorderResult << std::endl;
    std::cout << "Симметричный обход (инфиксный): " << inorderResult << std::endl;
    std::cout << "Обратный обход (постфиксный): " << postorderResult << std::endl;
    
    // Запись результатов в файл
    std::ofstream outFile("traversals.txt");
    if (outFile.is_open()) {
        outFile << "Исходное выражение: " << expression << "\n\n";
        outFile << "Прямой обход (префиксный): " << preorderResult << "\n";
        outFile << "Симметричный обход (инфиксный): " << inorderResult << "\n";
        outFile << "Обратный обход (постфиксный): " << postorderResult << "\n";
        outFile.close();
        std::cout << "\nРезультаты обходов записаны в файл 'traversals.txt'\n";
    } else {
        std::cout << "Ошибка при открытии файла для записи!\n";
    }
    
    // Очистка памяти
    deleteTree(root);
    
    return 0;
}