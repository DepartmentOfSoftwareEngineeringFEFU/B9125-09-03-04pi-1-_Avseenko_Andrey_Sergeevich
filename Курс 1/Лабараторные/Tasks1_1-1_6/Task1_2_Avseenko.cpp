#include <iostream>
#include <string>
#include <set>

// Множество допустимых латинских букв и дефиса (релоцируемся так сказать xddd)
const std::set<char> validLatinLetters = {
    // Заглавные буквы
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
    // Строчные буквы
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
    // Дефис (в двойных фамилиях/именах)
    '-'
};

// Функция проверки строки на содержание только латинских букв
bool isValidLatinName(const std::string& name) { // эта функция без нейронки, теперь с set'ом)
    if (name.empty()) {
        return false;
    }
    
    // Проходим по каждому символу строки
    for (size_t i = 0; i < name.length(); ++i) {
        char ch = name[i];
        // Проверяем, есть ли символ в множестве допустимых
        if (validLatinLetters.find(ch) == validLatinLetters.end()) {
            return false;
        }
    }
    return true;
}

// Функция для преобразования первой буквы в заглавную - ref с deepseek, но для латиницы
std::string capitalizeFirst(const std::string& str) {
    if (str.empty()) return str;
    
    std::string result = str;
    
    // Преобразуем все буквы в строчные
    for (size_t i = 0; i < result.length(); ++i) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] + 32; // Преобразуем в строчную
        }
    }
    
    // Первую букву делаем заглавной
    if (result[0] >= 'a' && result[0] <= 'z') {
        result[0] = result[0] - 32; // Преобразуем в заглавную
    }
    
    return result;
}

// Функция для удаления пробелов 1
std::string trimLeft(const std::string& str) {
    size_t i = 0;
    while (i < str.length() && (str[i] == ' ' || str[i] == '\t')) {
        i++;
    }
    return str.substr(i);
}

// Функция для удаления пробелов 2
std::string trimRight(const std::string& str) {
    size_t end = str.length();
    while (end > 0 && (str[end - 1] == ' ' || str[end - 1] == '\t')) {
        end--;
    }
    return str.substr(0, end);
}

// Функция для удаления пробелов 3 (первые две части были слишком хороши)
std::string trim(const std::string& str) {
    return trimLeft(trimRight(str));
}

// Функция ввода с проверкой (делал через нейронку, но с set'ом тоже ок)
std::string inputValidName(const std::string& prompt) {
    std::string input;
    bool valid = false;
    
    while (!valid) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        input = trim(input); // -пробелы (они нам не нужны)
        
        if (isValidLatinName(input)) {
            valid = true;
        } else {
            std::cout << "Error! Only Latin letters and hyphen are allowed.\n";
            std::cout << "Try again.\n\n";
        }
    }
    
    return capitalizeFirst(input);
}

int main() {
    std::cout << "Allowed characters: Latin letters and hyphen\n";
    std::cout << "Enter data one by one, multiple words separated by spaces = error\n";
    std::cout << "First letter is automatically capitalized!\n\n";
    
    std::string lastName = inputValidName("Enter last name: ");
    std::string firstName = inputValidName("Enter first name: ");
    std::string middleName = inputValidName("Enter middle name: ");
    
    std::cout << "\n ~~~ Input Result ~~~ \n";
    std::cout << "Last name: " << lastName << std::endl;
    std::cout << "First name: " << firstName << std::endl;
    std::cout << "Middle name: " << middleName << std::endl;
    std::cout << "Full name: " << lastName << " " 
              << firstName << " " << middleName << std::endl;
    
    return 0;
}