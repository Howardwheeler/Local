#include "hashtable.h"

int menu(){
    int choice;

    std::cout << "Pick your choices!" << std::endl;
    std::cout << "1. Insert " << std::endl;
    std::cout << "2. Remove " << std::endl;
    std::cout << "3. Print" << std::endl;
    std::cout << "Anything else to quit" << std::endl;
    std::cin >> choice;
    return choice;
}

int main(){
    int menu_choice;
    string word;
    int index;
    hashtable table;
    
    do{
        menu_choice = menu();
        if(menu_choice == 1){
            std::cout << "Enter word to insert: " << std::endl;
            std::cin >> word;
            table.insert(word);
        } else if(menu_choice == 2){
            std::cout << "Enter word to remove: " << std::endl;
            std::cin >> word;
            table.remove(word);
        } else if(menu_choice == 3){
            std::cout << "Enter index to print:" << std::endl;
            std::cin >> index;
            table.printIndex(index);
            std::cout << std::endl;
        }
    } while(menu_choice >= 1 && menu_choice <= 3);


    return 0;
}