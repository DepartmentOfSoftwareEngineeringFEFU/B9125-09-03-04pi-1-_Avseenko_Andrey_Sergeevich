#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

struct Date {
    int day;
    std::string month;
    int year;
};

int monthToNumber(const std::string& month) {
    if (month == "январь" || month == "января") return 1;
    if (month == "февраль" || month == "февраля") return 2;
    if (month == "март" || month == "марта") return 3;
    if (month == "апрель" || month == "апреля") return 4;
    if (month == "май" || month == "мая") return 5;
    if (month == "июнь" || month == "июня") return 6;
    if (month == "июль" || month == "июля") return 7;
    if (month == "август" || month == "августа") return 8;
    if (month == "сентябрь" || month == "сентября") return 9;
    if (month == "октябрь" || month == "октября") return 10;
    if (month == "ноябрь" || month == "ноября") return 11;
    if (month == "декабрь" || month == "декабря") return 12;
    return 0;
}

bool isValidDate(int day, const std::string& month, int year) {
    if (year < 2000 || year > 2025) return false;
    
    int monthNum = monthToNumber(month);
    if (monthNum == 0) return false;
    
    if (day < 1 || day > 31) return false;
    
    if ((monthNum == 4 || monthNum == 6 || monthNum == 9 || monthNum == 11) && day > 30) {
        return false;
    }
    
    if (monthNum == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeapYear && day > 29) return false;
        if (!isLeapYear && day > 28) return false;
    }
    
    return true;
}

int main() {
    Date DATA;
    
    std::string inputDate;
    bool correctInput = false;
    
    std::cout << "--- ВВОД ДАТЫ ---\n";
    std::cout << "Введите дату в формате: ДЕНЬ МЕСЯЦ ГОД\n";
    std::cout << "Пример: 1 января 2024\n";
    std::cout << "День - число от 1 до 31\n";
    std::cout << "Месяц - слово (январь, февраля, март, марта, ...)\n";
    std::cout << "Год - число от 2000 до 2025\n\n";
    
    while (!correctInput) {
        std::cout << "Введите дату: ";
        std::getline(std::cin, inputDate);
        
        std::stringstream ss(inputDate);
        std::string dayStr, monthStr, yearStr;
        
        if (ss >> dayStr >> monthStr >> yearStr) {
            try {
                int day = std::stoi(dayStr);
                int year = std::stoi(yearStr);
                
                if (isValidDate(day, monthStr, year)) {
                    DATA.day = day;
                    DATA.month = monthStr;
                    DATA.year = year;
                    correctInput = true;
                } else {
                    std::cout << "Ошибка! Некорректная дата. Попробуйте снова, хотя у вас все равно не получится.\n\n";
                }
            } catch (...) {
                std::cout << "Ошибка! Неверный формат чисел. Попробуйте снова, хотя у вас все равно не получится.\n\n";
            }
        } else {
            std::cout << "Ошибка! Введите дату в формате: день месяц год\n\n";
        }
    }
    
    std::cout << "\nВВЕДЁННАЯ ДАТА:\n";
    std::cout << "День: " << DATA.day << "\n";
    std::cout << "Месяц: " << DATA.month << "\n";
    std::cout << "Год: " << DATA.year << "\n";
    
    int monthNum = monthToNumber(DATA.month);
    
    std::cout << "\n ФОРМАТИРОВАННЫЙ ВЫВОД\n";
    std::cout << DATA.year << ":"
              << std::setw(2) << std::setfill('0') << monthNum << ":"
              << std::setw(2) << std::setfill('0') << DATA.day;
    
    return 0;
}