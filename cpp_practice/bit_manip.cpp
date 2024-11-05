
#include<iostream>
#include<bit>

template <typename T>
void SwapEnd(T& var)
{
    // static_assert(std::is_pod<T>::value, "Type must be POD type for safety");

    std::array<char, sizeof(T)> varArray;

    std::memcpy(varArray.data(), &var, sizeof(T));

    for(int i = 0; i < static_cast<int>(sizeof(var)/2); i++) {
         std::swap(varArray[sizeof(var) - 1 - i],varArray[i]);
    }

    std::memcpy(&var, varArray.data(), sizeof(T));
}


int main() {
    int value = 0x12345678;

    if(*(int *)&value == 0x12345678)
    {
        std::cout << "\nLittle-Endian\n" << std::endl;
    }
    else
    {
        std::cout << "\nBig-Endian\n" << std::endl;
    }

    SwapEnd(value);

    std::cout << "Original value: " << std::hex << value << std::endl;

    return 0; 

}
    
