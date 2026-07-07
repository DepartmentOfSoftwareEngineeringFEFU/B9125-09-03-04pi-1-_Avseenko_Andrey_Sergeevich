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
    // Заглавные буквы
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'
};

const std::set<char> Signs = {
    // Заглавные буквы
    '+', '-', '*'
};

struct Result{
    int a, b, c; // Буквы на всякий, Цифры, Знаки
};

bool StringValidation(std::string str){

bool result = false;

for(int i =0; i< str.length(); i++){
    if(Signs.find(str[i])!= Signs.end()){result = true;}
    else if(Numbers.find(str[i])!=Numbers.end()){result = true;}
    else if(LatinLetters.find(str[i])!=LatinLetters.end()){result = true;};
}

return result;

}

Result Counter(std::string str){

    int Letters = 0;
    int Numberss = 0;
    int Signss = 0;

    for(int i =0; i< str.length(); i++){
        if(LatinLetters.find(str[i])!=LatinLetters.end()){Letters++;};
        if(Numbers.find(str[i])!=Numbers.end()){Numberss++;};
        if(Signs.find(str[i])!=Signs.end()){Signss++;};
    }

    return {Letters, Numberss, Signss};
}

int main(){

std::string testString = "x1+y2-z3*4a5b6c7d8e9f0+hello-world*test+42-17*3\n";

char yn;
std::string StringMain = "";

std::cout<< "Хотим использовать встроенную тестовую строку ? y/n \n";
std::cin >> yn;
std::cin.ignore();

switch (yn)
{
case 'y':{ //y
    std::cout<<"Тестовая строка:\n x1+y2-z3*4a5b6c7d8e9f0+hello-world*test+42-17*3 \n";
    StringMain = testString;
    break;
}
case 'n':{ //n
    std::string UserString;
    bool Correct = false;
    while(!Correct){
    std::cout<<"ВВедите вашу стркоку: (Строка должна состоять из Латинских букв, цифр, знаков * + - и пробела) \n";
    std::getline(std::cin, UserString);
    if(StringValidation(UserString)){Correct = true; StringMain = UserString;};
    }
    break;
}
default:{//shit
    std::cout<<"И не y и не n! Ошибка!\n"<<"Выбираем мою\n";
    StringMain = testString;
    break;}
}

//считаемs

Result REsult = Counter(StringMain);

std::cout<< REsult.b<<" <- Количество цифр в строке \n"<<REsult.c << " <- Количестов знаков в строке\n";

return 0;
}