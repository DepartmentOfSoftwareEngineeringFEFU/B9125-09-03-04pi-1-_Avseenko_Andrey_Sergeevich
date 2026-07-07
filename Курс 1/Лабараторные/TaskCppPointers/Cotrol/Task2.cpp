#include <iostream>
#include <unordered_set>
#include <ctime>   // для time()

//мощность множества (без повторений) выбирает пользователь
//множество без повторений

// us.find(5);               // итератор на элемент или us.end()
// us.count(5);              // 1 или 0
// us.contains(5);           // C++20
// us.empty();
// us.size();
// std::unordered_set<int> us;

// us.insert(5);
// us.insert({1, 2, 3});
// us.emplace(10);
// us.erase(5);
// us.erase(iterator);
// us.clear();

 // крайне оптимистичная функция
void deleteNegative(std::unordered_set<int> Set){ 

}

int RandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main(){
//для генератора
    srand(time(NULL)); // инициализация генератора текущим временем

    int card; //можщность множества 
    std::cout<<"Ведите мощость множества : \n";
    std::cin>>card;

    int high_border =  card / 2;
    int low_border;
    if(!card % 2){low_border = high_border * -1 +1;}else{low_border = high_border* -1;}; 

    std::unordered_set<int> Set;

    if(card <= 0){std::cout<<"Неверный размер множества !";}
    else{
        int i = low_border;
        while(i <= high_border){
        Set.insert(i);
        i++;
        }


    int rand = RandomInt(low_border, high_border);
    Set.erase(rand);

    
    std::cout << "Множество: "; //1 вывод
        for (auto i = Set.begin(); i != Set.end(); ++i){
            std::cout << *i << " ";}
    std::cout << "\n";    

    std::cout<<"Удаление отрицательных чисел\n";
            for (auto i = Set.begin(); i != Set.end(); ++i){
            if(*i < 0){std::cout << *i << " "; Set.erase(*i);}}

    std::cout << "\n"; //2 вывод
    std::cout << "Новое Множество: ";
    for (auto i = Set.begin(); i != Set.end(); ++i){
        std::cout << *i << " ";}
    std::cout << "\n";  

    }

}