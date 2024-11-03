#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <ctime>
#include <sstream>
#include <iomanip>

struct GPSData {
    double latitude; 
    double longitude; 
    double altitude; 
    std::string timestamp; 

    std::string toCSV() const {
        std::ostringstream oss; 
        oss << std::fixed << std::setprecision(6) << latitude << "," << longitude << "," << timestamp; 
        return oss.str();
    }
};

void generateGPSData(GPSData &gpsData) {
    gpsData.latitude = (rand() % 18000 - 9000) / 1000.0; //Latitude range: -90.0 to 90.0
    gpsData.longitude = (rand() % 3600 - 1800) / 1000.0; // range: -180.0 to 180.0
    gpsData.altitude = static_cast<double>(rand() % 5000); //0-5000 meters

    time_t now = time(0);
    gpsData.timestamp = std::string(std::ctime(&now)); 
    gpsData.timestamp.pop_back(); // remove newline char
}

void logGPSData(const std::string &filename, const GPSData &gpsData) {
    //ofstream => output file stream, used to create files and write data to them
    std::ofstream dataFile(filename, std::ios::app);
    if (dataFile.is_open()) {
        dataFile << gpsData.toCSV() << "\n";
        dataFile.close();
    } else {
        std::cerr << "Unable to open file for writing!" << std::endl; 
    }
}

void simulateGPSLogging (const std::string &filename, int numEntries) {
    //++i is pre-increment
    for (int i = 0; i < numEntries; ++i) {
        GPSData gpsData; 
        generateGPSData(gpsData);
        logGPSData(filename, gpsData);
        std::cout << "Logged Entry " << (i + 1) << ": " << gpsData.toCSV() << std::endl;
    }
}

void parseGPSData(const std::string &filename) {
    std::ifstream dataFile(filename);
    std::string line; 
    if (dataFile.is_open()) {
        while (std::getline(dataFile, line)) {
            std::cout << "Parsed Data: " << line << std::endl; 
        }
        dataFile.close();
    } else {
        std::cerr << "Unable to open" << filename << std::endl; 
    }
}

int main() {
    std::srand(std::time(0));
    const std::string filename = "gps_data.csv"; 

    int numEntries = 10; 
    simulateGPSLogging(filename, numEntries);

    std::cout << "\nReading back logged data:\n";
    parseGPSData(filename);

    return 0; 

}