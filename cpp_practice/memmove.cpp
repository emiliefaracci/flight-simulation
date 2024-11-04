#include<iostream>
#include<cstring>

//memmove(void * destination, void * source, size_t size);

int main() {
    int arr[6] = {1,2,3,4,5,6}; 

    for (int i=0; i < 6; i++) {
        std::cout << arr[i] << " ";
    }

    std::memmove(&arr[0], &arr[2], 3*sizeof(arr[0])); 

    std::cout << "\n";
    for (int i=0; i < 6; i++) {
        std::cout << arr[i] << " ";
    }
    return 0; 
}