#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct Avto
{
    int number;
    std::string fio;
    std::string mark;
};

bool wordExists(const std::string& text, const std::string& word)
{
    int textLen = text.length();
    int wordLen = word.length();
    
    if (wordLen > textLen) return false;
    
    for (int i = 0; i <= textLen - wordLen; i++)
    {
        bool match = true;
        
        for (int j = 0; j < wordLen; j++)
        {
            if (text[i + j] != word[j])
            {
                match = false;
                break;
            }
        }
        
        if (match)
        {
            bool leftOk = (i == 0) || (text[i - 1] == ' ');
            bool rightOk = (i + wordLen == textLen) || (text[i + wordLen] == ' ');
            
            if (leftOk && rightOk) return true;
        }
    }
    
    return false;
}

void addWord(std::string& text, const std::string& word)
{
    if (text.length() > 0)
    {
        text += " ";
    }
    text += word;
}

int main()
{
    std::cout<<"Формат файла: 7913 Petrova Polina Pavlovna Kia - разделитель ПРОБЕЛ\n";
    std::ifstream file("AvseenkoTests1.txt");
    if (!file)
    {
        std::cout << "Ошибка открытия файла!\n";
        return 1;
    }
    
    std::string line;
    Avto a;
    int lineNumber = 0;
    bool fileValid = true;
    
    while (std::getline(file, line))
    {
        lineNumber++;
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        std::string word1, word2, word3, extra;
        
        if (!(iss >> a.number >> word1 >> word2 >> word3 >> a.mark)){fileValid = false; continue;}
        
        bool validFio = true;
        a.fio = word1 + " " + word2 + " " + word3;
        
        for (int i = 0; i < word1.length(); i++) 
            if (!isalpha(word1[i])) validFio = false;
        for (int i = 0; i < word2.length(); i++) 
            if (!isalpha(word2[i])) validFio = false;
        for (int i = 0; i < word3.length(); i++) 
            if (!isalpha(word3[i])) validFio = false;
        
        bool validNumber = (a.number >= 1000 && a.number <= 9999);
        
        if (!validFio || !validNumber)
        {
            fileValid = false;
            continue;
        }
        
        if (iss >> extra){fileValid = false; continue;}
    }
    
    file.close();
    
    if (!fileValid)
    {std::cout << "Файл содержит ошибки\n"; return 1;}
    
    file.open("AvseenkoTests1.txt");
    
    std::string allMarks = "";
    
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        
        std::istringstream iss(line); //берем и переводим линию в класс строки
        std::string word1, word2, word3; //для проверки 
        iss >> a.number >> word1 >> word2 >> word3 >> a.mark;//проверяем на типы и кол-ов слов
        
        if (!wordExists(allMarks, a.mark))
        {addWord(allMarks, a.mark);}
    }
    
    file.close();
    
    int start = 0; //позиция марки с которой читаем строку allMarks
    int len = allMarks.length(); //длина строки с марками
    
    for (int i = 0; i <= len; i++){
        if (i == len || allMarks[i] == ' '){
            if (i > start){
                std::string currentMark = "";
                for (int j = start; j < i; j++){
                    currentMark += allMarks[j];}
                
                file.open("AvseenkoTests1.txt");
                
                int count = 0; //счетчик марки
                
                while (std::getline(file, line)){
                    if (line.empty()) continue;
                    
                    std::istringstream iss(line); //аналогичная схема первому чтению но тут нам только марка нужна
                    std::string w1, w2, w3, mark;
                    int num;
                    iss >> num >> w1 >> w2 >> w3 >> mark;
                    
                    if (mark == currentMark) count++;}
                
                file.close();
                
                std::cout << currentMark << ": " << count << "\n";
            }
            start = i + 1;//идем со следующей марки в строке тип
        }
    }
    
    return 0;
}