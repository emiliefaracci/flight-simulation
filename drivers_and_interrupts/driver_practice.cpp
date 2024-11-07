#include <iostream> 
#include <cstring> 

using namespace std; 

//what are things we need to be able to do? 
//send and receive information, like for example, retrieve and populate data array

class SimpleDevice {
public:
    //initialise
    SimpleDevice() {
        cout << "Initializing Device" << endl;
        strcpy(data, "Hello Device!");
    }

    //given an empty buffer and the size of read, update the buffer and return size
    //ssize_t can be negative to indicate an error 
    ssize_t read_data (char* buffer, size_t size) {

        //if size you want to read is larger, make it smaller 
        if (size > sizeof(data)) {
            size = sizeof(data);
        }
        //copy data onto buffer for that size
        memcpy(buffer, data, size);
        return size;  
        
    }

    ssize_t write_data (const char* buffer, size_t size) {
        //copy buffer (src) on data (dest)
        //if size is larger, it'll just copy the first onto there (?)
        //if size is smaller, that'll be the new size 
        memcpy(data, buffer, size);
        return size; 
    }

private: 
    char data[256]; 

}; 


class deviceDriver {
public: 

    deviceDriver () :  myDevice(nullptr) {}

    ~deviceDriver() {
        cout << "Bye Bye device driver!";
        if (myDevice) {
            //safety - check you're not removing a nullptr already
            delete myDevice; 
        }
    }

    int init_device () {
        myDevice = new SimpleDevice; 
        return 0; 
    }
    
    int open_device () {
        if (!myDevice) {
            return -1; 
        }
        //simulate 
        cout << "Opening Device...";
        //success
        return 0; 
    }

    ssize_t read_device (char* buffer, size_t size) {
        if (!myDevice) {
            return -1; 
        }

        myDevice->read_data(buffer, size);

        return 0; 
    }

    ssize_t write_device (const char* buffer, size_t size) {
        if (!myDevice) {
            return -1; 
        }

        //if, instead, we initialised myDevice not as pointer, we could do myDevice.write_data - would that be valid too?
        myDevice->write_data(buffer, size);

        return 0; 
    }

    int close_device () {
        if (!myDevice) {
            return -1; 
        }
        //simulation of close
        cout << "Closing device...";
        //success
        return 0; 
    }


private: 
    //because this is a pointer, we need the pointer destruction call, which is automatically called when main stops executing (no need to do it manually)
    SimpleDevice *myDevice; 
};



int main() {
    
    //the idea is that we don't have to interact with the device direclty – everything is abstracted
    deviceDriver myDriver; 

    myDriver.init_device();
    myDriver.open_device();


    char buffer[256];
    ssize_t bytes = myDriver.read_device(buffer, sizeof(buffer));
    if (bytes < 0) {
        cerr << "issue reading\n";
        return -1; 
    } else {
        cout << "\nReading now: " << buffer << endl; 
    }

    char array[2] = "O";
    ssize_t byteswritten = myDriver.write_device(array, sizeof(array));
    if (byteswritten < 0) {
        cout << "init device first";
        return -1; 
    } 
    
    ssize_t bytes_updated = myDriver.read_device(buffer, sizeof(buffer));
    if (bytes_updated < 0) {
        cerr << "issue reading\n";
        return -1; 
    } else {
        cout << "Reading updated now: " << buffer << endl; 
    }

    myDriver.close_device();

    return 0; 
}