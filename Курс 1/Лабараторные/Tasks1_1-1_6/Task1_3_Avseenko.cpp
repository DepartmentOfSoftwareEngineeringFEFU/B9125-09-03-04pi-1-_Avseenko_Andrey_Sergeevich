#include <iostream>
#include <string>
#include <set>

const std::set<char> LatinLetters = {
    // Заглавные буквы
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
    // Строчные буквы
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',' '
};

const std::set<char> Numbers = {
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'
};

const std::set<char> Signs = {
    '+', '-', '*', '/', '=', '_',
    '!', '?', '.', ',', ':', ';',
    '"', '\'', '(', ')', '[', ']',
    '{', '}', '<', '>', '&', '|',
    '^', '~', '`', '@', '#', '$',
    '%'
};

// Множество гласных букв
const std::set<char> Vowels = {
    'A', 'E', 'I', 'O', 'U', 'Y',
    'a', 'e', 'i', 'o', 'u', 'y'
};

// Множество согласных букв
const std::set<char> Consonants = {
    'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M',
    'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z',
    'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',
    'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z'
};

struct Result {
    int a, b, c; // Буквы, Цифры, Знаки
};

struct LetterStats {
    int vowels;      // гласные
    int consonants;  // согласные
};

bool StringValidation(std::string str) {
    bool result = false;
    
    for (int i = 0; i < str.length(); i++) {
        if (Signs.find(str[i]) != Signs.end()) { result = true; }
        else if (Numbers.find(str[i]) != Numbers.end()) { result = true; }
        else if (LatinLetters.find(str[i]) != LatinLetters.end()) { result = true; }
    }
    
    return result;
}

Result Counter(std::string str) {
    int Letters = 0;
    int Numberss = 0;
    int Signss = 0;
    
    for (int i = 0; i < str.length(); i++) {
        if (LatinLetters.find(str[i]) != LatinLetters.end()) { Letters++; }
        if (Numbers.find(str[i]) != Numbers.end()) { Numberss++; }
        if (Signs.find(str[i]) != Signs.end()) { Signss++; }
    }
    
    return {Letters, Numberss, Signss};
}

LetterStats CountVowelsAndConsonants(std::string str) {
    int vowels = 0;
    int consonants = 0;
    
    for (int i = 0; i < str.length(); i++) {
        if (Vowels.find(str[i]) != Vowels.end()) {
            vowels++;
        }
        else if (Consonants.find(str[i]) != Consonants.end()) {
            consonants++;
        }
    }
    
    return {vowels, consonants};
}

std::set<char> GetPunctuationMarks(std::string str) {
    std::set<char> punctuationMarks;
    
    for (int i = 0; i < str.length(); i++) {
        if (Signs.find(str[i]) != Signs.end()) {
            punctuationMarks.insert(str[i]);
        }
    }
    
    return punctuationMarks;
}

int main() {
    std::string testString ="Hello, World! How are you? I'm fine... (really!) Let's test: a+b=c; x*y=z. [2024] {test} #cool @user & me | you <3 >_<";
    
    char yn;
    std::string StringMain = "";
    
    std::cout << "Хотим использовать встроенную тестовую строку? y/n: ";
    std::cin >> yn;
    std::cin.ignore();
    
    switch (yn) {
        case 'y': {
            std::cout << "Тестовая строка:\n" << testString << "\n";
            StringMain = testString;
            break;
        }
        case 'n': {
            std::string UserString;
            bool Correct = false;
            while (!Correct) {
                std::cout << "Введите вашу строку: (Строка должна состоять из Латинских букв, цифр, знаков * + - и пробела)\n";
                std::getline(std::cin, UserString);
                if (StringValidation(UserString)) {
                    Correct = true;
                    StringMain = UserString;
                } else {
                    std::cout << "Ошибка! Недопустимые символы. Попробуйте снова.\n";
                }
            }
            break;
        }
        default: {
            std::cout << "И не y и не n! Ошибка!\nВыбираем мою строку.\n";
            StringMain = testString;
            break;
        }
    }
    
    // Считаем общую статистику
    Result REsult = Counter(StringMain);
    
    std::cout << "ОБЩАЯ СТАТИСТИКА:\n";
    std::cout << REsult.b << " <- Количество цифр в строке\n";
    std::cout << REsult.a << " <- Количество букв в строке\n";
    std::cout << REsult.c << " <- Количество знаков в строке\n";

    std::cout << "\nЗАДАНИЕ 1: ЧЕГО БОЛЬШЕ?\n";
    if (REsult.b > REsult.a) {
        std::cout << "Цифр больше, чем букв! (" << REsult.b << " > " << REsult.a << ")\n";
    } else if (REsult.a > REsult.b) {
        std::cout << "Букв больше, чем цифр! (" << REsult.a << " > " << REsult.b << ")\n";
    } else {
        std::cout << "Цифр и букв поровну! (" << REsult.b << " = " << REsult.a << ")\n";
    }
    
    LetterStats stats = CountVowelsAndConsonants(StringMain);
    
    std::cout << "\nЗАДАНИЕ 2: ГЛАСНЫЕ И СОГЛАСНЫЕ \n";
    std::cout << "Гласных букв: " << stats.vowels << "\n";
    std::cout << "Согласных букв: " << stats.consonants << "\n";
    std::cout << "Всего букв: " << (stats.vowels + stats.consonants) << "\n";
    
    std::set<char> punctMarks = GetPunctuationMarks(StringMain);
    
    std::cout << "\nЗАДАНИЕ 3: МНОЖЕСТВО ЗНАКОВ ПРЕПИНАНИЯ\n";
    if (punctMarks.empty()) {
        std::cout << "Знаков препинания не найдено!\n";
    } else {
        std::cout << "Найденные знаки препинания: ";
        for (char mark : punctMarks) {
            std::cout << "'" << mark << "' ";
        }
        std::cout << "\nВсего различных знаков: " << punctMarks.size() << "\n";
    }
    
    return 0;
}