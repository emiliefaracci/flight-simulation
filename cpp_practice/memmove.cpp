#include<iostream>
#include<cstring>

//memmove(void * destination, void * source, size_t size);

// int useMemmove() {
//     int arr[6] = {1,2,3,4,5,6}; 

//     for (int i=0; i < 6; i++) {
//         std::cout << arr[i] << " ";
//     }

//     std::memmove(&arr[0], &arr[2], 3*sizeof(arr[0])); 

//     std::cout << "\n";
//     for (int i=0; i < 6; i++) {
//         std::cout << arr[i] << " ";
//     }
//     return 0; 
// }

void* myMemcopy(void* destination, const void* source, std::size_t size) {

    char *dataS = (char *)source;
    char *dataD = (char *)destination; 

    for (int i=0; i < size; i++) {
        dataD[i] = dataS[i];
    }
    return destination; 
}

void* myMemmove(void* destination, const void* source, size_t size) {
    
    char *dataS = (char *)source; 
    char *dataD = (char *)destination; 
    char *temp = new char[size];

    for (int i=0; i < size; i++) {
        temp[i] = dataS[i];
    }

    for (int i=0; i < size; i++) {
        dataD[i] = temp[i];
    }
    delete[] temp;
    return destination; 

}

int main() {

    const char dataS[] = "hello";
    char dataD[100];

    myMemcopy(dataD, dataS, 5*sizeof(dataS[0]));
    std::cout << "After myMemcopy: " << dataD << std::endl;

    const char new_dataS[] = "hello";
    char new_dataD[] = "Omgggggggggg";
    
    myMemmove(new_dataD, new_dataS, 3*sizeof(dataS[0]));
    std::cout << "After myMemcopy: " << new_dataD << std::endl;

    return 0;
}