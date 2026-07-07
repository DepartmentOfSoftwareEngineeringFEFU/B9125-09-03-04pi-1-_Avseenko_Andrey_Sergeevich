#include <iostream>
#include <fstream>
#include <string>

// Узел бинарного дерева
struct TreeNode {
    std::string data;  // Данные узла: число или оператор
    TreeNode* left;    // Левое поддерево
    TreeNode* right;   // Правое поддерево
};

// Стек для хранения узлов дерева (используется при построении дерева)
struct StackNode {
    TreeNode* data;
    StackNode* next;
};

// Стек для хранения строк (операторы и скобки)
struct StringStackNode {
    std::string data;
    StringStackNode* next;
};

// Стек для хранения чисел (используется при вычислении ОПЗ)
struct NumberStackNode {
    double data;
    NumberStackNode* next;
};

// ==================== Функции стека TreeNode* ====================

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

// ==================== Функции стека string ====================

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

// ==================== Функции стека чисел ====================

void numberPush(NumberStackNode*& stack, double value) {
    NumberStackNode* newNode = new NumberStackNode;
    newNode->data = value;
    newNode->next = stack;
    stack = newNode;
}

double numberPop(NumberStackNode*& stack) {
    if (stack == nullptr) return 0;
    NumberStackNode* temp = stack;
    double data = temp->data;
    stack = stack->next;
    delete temp;
    return data;
}

bool numberIsEmpty(NumberStackNode* stack) {
    return stack == nullptr;
}

// ==================== Вспомогательные функции ====================

TreeNode* createNode(const std::string& data) {
    TreeNode* node = new TreeNode;
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

int precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isOperatorStr(const std::string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isOperandChar(char c) {
    return isDigit(c) || c == '.';
}

bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    
    size_t i = 0;
    if (s[0] == '-') {
        if (s.length() == 1) return false;
        i = 1;
    }
    
    // Проверка: число не может начинаться с точки
    if (i < s.length() && s[i] == '.') {
        return false;
    }
    
    bool hasDot = false;
    bool hasDigit = false;
    
    for (; i < s.length(); i++) {
        if (s[i] == '.') {
            if (hasDot) return false;
            hasDot = true;
        } else if (isDigit(s[i])) {
            hasDigit = true;
        } else {
            return false;
        }
    }
    
    return hasDigit;
}

double stringToDouble(const std::string& s) {
    double result = 0;
    double fraction = 0;
    double divisor = 10;
    bool isNegative = false;
    bool isFraction = false;
    size_t i = 0;
    
    if (s[0] == '-') {
        isNegative = true;
        i = 1;
    }
    
    for (; i < s.length(); i++) {
        if (s[i] == '.') {
            isFraction = true;
            continue;
        }
        
        if (!isFraction) {
            result = result * 10 + (s[i] - '0');
        } else {
            fraction += (s[i] - '0') / divisor;
            divisor *= 10;
        }
    }
    
    result += fraction;
    return isNegative ? -result : result;
}

std::string doubleToString(double value) {
    if (value == 0) return "0";
    
    std::string result;
    bool isNegative = false;
    
    if (value < 0) {
        isNegative = true;
        value = -value;
    }
    
    long long intPart = (long long)value;
    double fracPart = value - intPart;
    
    if (intPart == 0) {
        result = "0";
    } else {
        while (intPart > 0) {
            result = (char)('0' + (intPart % 10)) + result;
            intPart /= 10;
        }
    }
    
    if (fracPart > 0) {
        result += '.';
        int digits = 0;
        while (fracPart > 0 && digits < 6) {
            fracPart *= 10;
            int digit = (int)fracPart;
            result += (char)('0' + digit);
            fracPart -= digit;
            digits++;
        }
    }
    
    return isNegative ? "-" + result : result;
}

// ==================== Проверка корректности выражения ====================

bool validateExpression(const std::string& expr) {
    // Проверка на пустое выражение
    if (expr.empty()) {
        std::cout << "Ошибка: пустое выражение\n";
        return false;
    }
    
    int bracketBalance = 0;
    bool lastWasOperator = true;
    bool lastWasOpenBracket = false;
    bool hasContent = false;  // Флаг наличия meaningful содержимого
    
    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];
        
        if (c == ' ') continue;
        
        hasContent = true;
        
        // Проверка на недопустимые символы
        if (!isDigit(c) && !isOperator(c) && c != '.' && c != '(' && c != ')') {
            std::cout << "Ошибка: недопустимый символ '" << c << "'\n";
            return false;
        }
        
        if (c == '(') {
            bracketBalance++;
            lastWasOperator = true;
            lastWasOpenBracket = true;
        }
        else if (c == ')') {
            bracketBalance--;
            if (bracketBalance < 0) {
                std::cout << "Ошибка: лишняя закрывающая скобка\n";
                return false;
            }
            if (lastWasOperator && !lastWasOpenBracket) {
                std::cout << "Ошибка: оператор перед закрывающей скобкой\n";
                return false;
            }
            if (lastWasOpenBracket) {
                std::cout << "Ошибка: пустые скобки\n";
                return false;
            }
            lastWasOperator = false;
            lastWasOpenBracket = false;
        }
        else if (isOperator(c)) {
            // Оператор не должен идти после другого бинарного оператора
            if (lastWasOperator && !lastWasOpenBracket && c != '-') {
                std::cout << "Ошибка: два оператора подряд '" << c << "'\n";
                return false;
            }
            lastWasOperator = true;
            lastWasOpenBracket = false;
        }
        else if (c == '.') {
            // Точка не может идти после оператора или открывающей скобки без цифры
            if (lastWasOperator) {
                std::cout << "Ошибка: число не может начинаться с точки\n";
                return false;
            }
            lastWasOperator = false;
            lastWasOpenBracket = false;
            
            // Проверка: нет ли уже точки в текущем числе
            // Идем назад до ближайшего пробела/оператора/скобки
            size_t j = i - 1;
            while (j > 0 && isOperandChar(expr[j])) {
                if (expr[j] == '.') {
                    std::cout << "Ошибка: две точки в числе\n";
                    return false;
                }
                j--;
            }
            // Проверяем граничный случай для j=0
            if (j == 0 && isOperandChar(expr[j]) && expr[j] == '.') {
                std::cout << "Ошибка: две точки в числе\n";
                return false;
            }
        }
        else if (isDigit(c)) {
            lastWasOperator = false;
            lastWasOpenBracket = false;
        }
    }
    
    if (!hasContent) {
        std::cout << "Ошибка: выражение состоит только из пробелов\n";
        return false;
    }
    
    if (bracketBalance != 0) {
        std::cout << "Ошибка: несоответствие количества скобок\n";
        return false;
    }
    
    if (lastWasOperator && !lastWasOpenBracket) {
        std::cout << "Ошибка: выражение заканчивается оператором\n";
        return false;
    }
    
    return true;
}

// ==================== Алгоритм "Сортировочная станция" ====================

std::string shuntingYard(const std::string& expression) {
    StringStackNode* opStack = nullptr;
    std::string output;
    
    size_t i = 0;
    while (i < expression.length()) {
        char c = expression[i];
        
        if (c == ' ') {
            i++;
            continue;
        }
        
        // Обработка чисел
        if (isDigit(c) || (c == '-' && (i == 0 || expression[i-1] == '(' || 
                                         (i > 0 && isOperator(expression[i-1]))))) {
            std::string number;
            if (c == '-') {
                number += c;
                i++;
            }
            while (i < expression.length() && isOperandChar(expression[i])) {
                number += expression[i];
                i++;
            }
            output += number + " ";
            continue;
        }
        
        if (c == '(') {
            stringPush(opStack, "(");
        }
        else if (c == ')') {
            while (!stringIsEmpty(opStack) && stringTop(opStack) != "(") {
                output += stringPop(opStack) + " ";
            }
            if (!stringIsEmpty(opStack)) {
                stringPop(opStack);
            }
        }
        else if (isOperator(c)) {
            std::string op(1, c);
            while (!stringIsEmpty(opStack) && stringTop(opStack) != "(" &&
                   precedence(stringTop(opStack)) >= precedence(op)) {
                output += stringPop(opStack) + " ";
            }
            stringPush(opStack, op);
        }
        i++;
    }
    
    while (!stringIsEmpty(opStack)) {
        output += stringPop(opStack) + " ";
    }
    
    return output;
}

// ==================== Построение бинарного дерева ====================

TreeNode* buildParseTree(const std::string& expression) {
    StackNode* nodeStack = nullptr;
    StringStackNode* stringStack = nullptr;
    
    size_t i = 0;
    while (i < expression.length()) {
        char c = expression[i];
        
        if (c == ' ') {
            i++;
            continue;
        }
        
        if (isDigit(c) || (c == '-' && (i == 0 || expression[i-1] == '(' || 
                                         (i > 0 && isOperator(expression[i-1]))))) {
            std::string number;
            if (c == '-') {
                number += c;
                i++;
            }
            while (i < expression.length() && isOperandChar(expression[i])) {
                number += expression[i];
                i++;
            }
            push(nodeStack, createNode(number));
            continue;
        }
        
        if (c == '(') {
            stringPush(stringStack, "(");
        }
        else if (c == ')') {
            while (!stringIsEmpty(stringStack) && stringTop(stringStack) != "(") {
                std::string op = stringPop(stringStack);
                
                TreeNode* right = pop(nodeStack);
                TreeNode* left = pop(nodeStack);
                
                TreeNode* opNode = createNode(op);
                opNode->left = left;
                opNode->right = right;
                
                push(nodeStack, opNode);
            }
            if (!stringIsEmpty(stringStack)) {
                stringPop(stringStack);
            }
        }
        else if (isOperator(c)) {
            std::string op(1, c);
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
    
    while (!stringIsEmpty(stringStack)) {
        std::string op = stringPop(stringStack);
        
        TreeNode* right = pop(nodeStack);
        TreeNode* left = pop(nodeStack);
        
        TreeNode* opNode = createNode(op);
        opNode->left = left;
        opNode->right = right;
        
        push(nodeStack, opNode);
    }
    
    return pop(nodeStack);
}

// ==================== Обходы дерева ====================

void postorderTraversal(TreeNode* node, std::string& result) {
    if (node == nullptr) return;
    postorderTraversal(node->left, result);
    postorderTraversal(node->right, result);
    result += node->data + " ";
}

void preorderTraversal(TreeNode* node, std::string& result) {
    if (node == nullptr) return;
    result += node->data + " ";
    preorderTraversal(node->left, result);
    preorderTraversal(node->right, result);
}

void inorderTraversal(TreeNode* node, std::string& result) {
    if (node == nullptr) return;
    
    bool addParentheses = isOperatorStr(node->data);
    if (addParentheses) result += "( ";
    
    inorderTraversal(node->left, result);
    result += node->data + " ";
    inorderTraversal(node->right, result);
    
    if (addParentheses) result += ") ";
}

// ==================== Вычисление ОПЗ ====================

double evaluateRPN(const std::string& rpn) {
    NumberStackNode* numStack = nullptr;
    std::string token;
    
    for (size_t i = 0; i < rpn.length(); i++) {
        if (rpn[i] == ' ') {
            if (!token.empty()) {
                if (isNumber(token)) {
                    numberPush(numStack, stringToDouble(token));
                } else if (isOperatorStr(token)) {
                    if (numberIsEmpty(numStack)) {
                        std::cout << "Ошибка: недостаточно операндов\n";
                        return 0;
                    }
                    double b = numberPop(numStack);
                    
                    if (numberIsEmpty(numStack)) {
                        std::cout << "Ошибка: недостаточно операндов\n";
                        return 0;
                    }
                    double a = numberPop(numStack);
                    
                    double result = 0;
                    
                    if (token == "+") result = a + b;
                    else if (token == "-") result = a - b;
                    else if (token == "*") result = a * b;
                    else if (token == "/") {
                        if (b == 0) {
                            std::cout << "Ошибка: деление на ноль!\n";
                            while (!numberIsEmpty(numStack)) numberPop(numStack);
                            return 0;
                        }
                        result = a / b;
                    }
                    numberPush(numStack, result);
                }
                token.clear();
            }
        } else {
            token += rpn[i];
        }
    }
    
    if (numberIsEmpty(numStack)) {
        std::cout << "Ошибка: пустое выражение\n";
        return 0;
    }
    
    double finalResult = numberPop(numStack);
    
    if (!numberIsEmpty(numStack)) {
        std::cout << "Ошибка: лишние операнды в выражении\n";
        while (!numberIsEmpty(numStack)) numberPop(numStack);
        return 0;
    }
    
    return finalResult;
}

// ==================== Визуализация дерева ====================

void printTree(TreeNode* node, int level) {
    if (node == nullptr) return;
    
    printTree(node->right, level + 1);
    
    for (int i = 0; i < level; i++) std::cout << "    ";
    
    std::cout << node->data << std::endl;
    
    printTree(node->left, level + 1);
}

// ==================== Очистка памяти ====================

void deleteTree(TreeNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void clearStack(StackNode*& stack) {
    while (!isEmpty(stack)) {
        TreeNode* node = pop(stack);
        deleteTree(node);
    }
}

void clearStringStack(StringStackNode*& stack) {
    while (!stringIsEmpty(stack)) {
        stringPop(stack);
    }
}

void clearNumberStack(NumberStackNode*& stack) {
    while (!numberIsEmpty(stack)) {
        numberPop(stack);
    }
}

// ==================== Тестирование ====================

void runTests() {
    std::ofstream testFile("test_results.txt");
    if (!testFile.is_open()) {
        std::cout << "Ошибка открытия файла для тестов!\n";
        return;
    }
    
    testFile << "ТЕСТИРОВАНИЕ КАЛЬКУЛЯТОРА\n";
    testFile << "========================\n\n";
    
    struct TestCase {
        std::string expression;
        std::string description;
        bool expectError;
    };
    
    TestCase tests[] = {
        // Корректные выражения
        {"2 + 3", "Простое сложение", false},
        {"10 - 5 * 2", "Приоритет операций", false},
        {"(2 + 3) * 4", "Скобки изменяют приоритет", false},
        {"3 + 4 * 2 / (1 - 5)", "Комплексное выражение", false},
        {"-5 + 3", "Унарный минус", false},
        {"1.5 + 2.5", "Десятичные дроби", false},
        {"10 / 3", "Деление с дробным результатом", false},
        
        // Ошибочные выражения
        {"2 +* 3", "Два оператора подряд", true},
        {"2 + ", "Выражение заканчивается оператором", true},
        {"(2 + 3", "Незакрытая скобка", true},
        {"2 + 3)", "Лишняя закрывающая скобка", true},
        {"10 / 0", "Деление на ноль", true},
        {"2..5 + 1", "Две точки в числе", true},
        {"abc + 3", "Недопустимые символы", true},
        {"", "Пустое выражение", true},
        {".5 + 2", "Число начинается с точки", true},
        {"2 + (3 - 1", "Незакрытая скобка в конце", true},
        {"()", "Пустые скобки", true},
        {"2 + ()", "Пустые скобки в выражении", true},
        {"2 + .", "Точка без цифр", true},
    };
    
    int numTests = sizeof(tests) / sizeof(tests[0]);
    int passedTests = 0;
    int failedTests = 0;
    
    for (int i = 0; i < numTests; i++) {
        testFile << "Тест " << (i + 1) << ": \"" << tests[i].expression << "\"\n";
        testFile << "  Описание: " << tests[i].description << "\n";
        testFile << "  Ожидание: " << (tests[i].expectError ? "ошибка" : "успех") << "\n";
        
        bool actualError = false;
        double result = 0;
        
        // Сначала проверяем валидность выражения
        if (!validateExpression(tests[i].expression)) {
            actualError = true;
        } else {
            // Метод 1: Сортировочная станция
            std::string rpn1 = shuntingYard(tests[i].expression);
            result = evaluateRPN(rpn1);
            
            // Особая проверка для деления на ноль
            if (tests[i].expression.find("/ 0") != std::string::npos &&
                tests[i].expression.find("/ 0.") == std::string::npos) {
                // Это настоящее деление на ноль
                if (result == 0) {
                    actualError = true;
                }
            }
            
            // Метод 2: Бинарное дерево (для сравнения)
            if (!actualError) {
                TreeNode* tree = buildParseTree(tests[i].expression);
                if (tree != nullptr) {
                    std::string rpn2;
                    postorderTraversal(tree, rpn2);
                    double result2 = evaluateRPN(rpn2);
                    
                    double diff = result - result2;
                    if (diff < 0) diff = -diff;
                    if (diff >= 0.0001) {
                        testFile << "  ✗ Результаты методов различаются!\n";
                        failedTests++;
                        deleteTree(tree);
                        continue;
                    }
                    deleteTree(tree);
                }
            }
        }
        
        if (actualError == tests[i].expectError) {
            testFile << "  ✓ Тест пройден\n";
            if (!actualError) {
                testFile << "  Результат: " << result << "\n";
            }
            passedTests++;
        } else {
            testFile << "  ✗ Тест не пройден (ожидалась " 
                     << (tests[i].expectError ? "ошибка" : "успех") 
                     << ", получено " << (actualError ? "ошибка" : "успех") << ")\n";
            failedTests++;
        }
        testFile << "\n";
    }
    
    testFile << "========================\n";
    testFile << "Пройдено: " << passedTests << " из " << numTests << "\n";
    testFile << "Провалено: " << failedTests << "\n";
    testFile.close();
    
    std::cout << "Тестирование завершено. Пройдено " << passedTests 
              << " из " << numTests << " тестов.\n";
    std::cout << "Подробные результаты в файле 'test_results.txt'\n";
}

// ==================== Главная программа ====================

int main() {
    int choice;
    
    std::cout << "КАЛЬКУЛЯТОР АРИФМЕТИЧЕСКИХ ВЫРАЖЕНИЙ\n";
    std::cout << "====================================\n";
    std::cout << "1. Вычислить выражение\n";
    std::cout << "2. Запустить тестирование\n";
    std::cout << "Выберите действие: ";
    std::cin >> choice;
    std::cin.ignore();
    
    if (choice == 2) {
        runTests();
        return 0;
    }
    
    std::string expression;
    std::cout << "Введите арифметическое выражение: ";
    std::getline(std::cin, expression);
    
    if (!validateExpression(expression)) {
        std::cout << "Выражение содержит ошибки. Вычисление невозможно.\n";
        return 1;
    }
    
    int method;
    std::cout << "\nВыберите метод перевода в ОПЗ:\n";
    std::cout << "1. Сортировочная станция\n";
    std::cout << "2. Бинарное дерево\n";
    std::cout << "Ваш выбор: ";
    std::cin >> method;
    
    std::string rpn;
    TreeNode* tree = nullptr;
    
    if (method == 1) {
        rpn = shuntingYard(expression);
        std::cout << "\nОбратная польская запись: " << rpn << std::endl;
    } else if (method == 2) {
        tree = buildParseTree(expression);
        if (tree == nullptr) {
            std::cout << "Ошибка построения дерева!\n";
            return 1;
        }
        
        std::cout << "\nДерево синтаксического разбора:\n";
        std::cout << "--------------------------------\n";
        printTree(tree, 0);
        std::cout << "--------------------------------\n";
        
        postorderTraversal(tree, rpn);
        std::cout << "Обратная польская запись (из дерева): " << rpn << std::endl;
        
        std::string preorder, inorder;
        preorderTraversal(tree, preorder);
        inorderTraversal(tree, inorder);
        
        std::ofstream treeFile("tree_traversals.txt");
        if (treeFile.is_open()) {
            treeFile << "Исходное выражение: " << expression << "\n\n";
            treeFile << "Прямой обход (префиксный): " << preorder << "\n";
            treeFile << "Симметричный обход (инфиксный): " << inorder << "\n";
            treeFile << "Обратный обход (постфиксный): " << rpn << "\n";
            treeFile.close();
            std::cout << "Обходы дерева записаны в 'tree_traversals.txt'\n";
        }
    } else {
        std::cout << "Неверный выбор метода!\n";
        return 1;
    }
    
    double result = evaluateRPN(rpn);
    std::cout << "\nРезультат вычисления: " << result << std::endl;
    
    std::ofstream resultFile("calculation_result.txt");
    if (resultFile.is_open()) {
        resultFile << "Выражение: " << expression << "\n";
        resultFile << "Метод: " << (method == 1 ? "Сортировочная станция" : "Бинарное дерево") << "\n";
        resultFile << "ОПЗ: " << rpn << "\n";
        resultFile << "Результат: " << result << "\n";
        resultFile.close();
    }
    
    if (tree != nullptr) {
        deleteTree(tree);
    }
    
    return 0;
}