#include <iostream>
#include <string>

// #include <algorithm>

enum Level {
    LOW = 1,
    MEDIUM = 10,
    HIGH = 75
}; 


int practiceSwitch(int value) {
    switch(value) {
        case 1: 
            return 1; 
            // break; 
        case 10: 
            return 10; 
            // break; 
        default: 
            return 0; 
            // break;
    }
}

void iterate_through(std::string str) {
    
    for (int i=0; i < str.size(); i++) {
        std::cout << str[i]; 
    }
}

void iterate(char* array) {
    
    for (int i=0; array[i] != '\0'; i++) {
        std::cout << array[i]; 
        //not using std::endl doesn't flush the buffer. 
    }
}

int main() {

    int val = 10; 
    int result = practiceSwitch(val);
    std::cout << result << std::endl; 

    enum Level newEnum = HIGH; 
    std::cout << newEnum << std::endl; 
    int new_res = practiceSwitch(newEnum);
    std::cout << new_res << std::endl; 

    std::string str = "HELLO";
    iterate_through(str);

    char array[6] = "hello";
    iterate(array);

    return 0; 
}
