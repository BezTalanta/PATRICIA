#include "patr.hpp"
#include <iostream>
#include <time.h>

int main(){
    patr test;
    std::string command;
    time_t start = clock();
    while(std::cin >> command && command != "\x4"){
        if(command == "+"){
            std::string key; std::cin >> key;
            int value; std::cin >> value;
            try{
                test.Add(key, value);
                std::cout << "\tSuccessfully!\n";
            }
            catch(const std::runtime_error& e){
                std::cout << e.what();
            }
        }
        else if(command == "-"){
            std::string key; std::cin >> key;
            try{
                test.Erase(key);
                std::cout << "\tSuccessfully!\n";
            }
            catch(const std::runtime_error& e){
                std::cout << e.what();
            }
        }
        else if(command == "clear" || command == "new"){
            test.Clear();
        }
        else if(command == "print" || command == "?"){
            test.Print();
        }
        else if(command == "get"){
            try{
                std::string key; std::cin >> key;
                std::cout << test.At(key) << '\n';
            }
            catch(const std::runtime_error& e){
                std::cout << e.what();
            }
        }
        else if(command != "\n"){
            std::cout << "\tCommand \"" + command + "\" isn't available\n";
        }
    }
    test.Clear();
    std::cout << "Time: " << (double)(clock() - start)/CLOCKS_PER_SEC << '\n';
    return 0;
}