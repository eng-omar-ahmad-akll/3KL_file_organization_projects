#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
using namespace std;

const int BUFFER_SIZE = 1024;

int main() {
    char buffer1[BUFFER_SIZE] = { 0 };
    char buffer2[BUFFER_SIZE] = { 0 };

   
    string fileName1;
    cout << "Enter the first file path: ";
    getline(cin, fileName1);

    
    const char* sampleData = "This is test data to demonstrate how to split it into two buffers";
    size_t size = strlen(sampleData);
    size_t halfSize = size / 2;

    cout << "\n--- Splitting data into two buffers ---" << endl;
    memcpy(buffer1, sampleData, halfSize);
    memcpy(buffer2, sampleData + halfSize, size - halfSize);

    cout << "First part stored in buffer1: " << buffer1 << endl;
    cout << "Second part stored in buffer2: " << buffer2 << endl;

    // First file processing
    ifstream file1(fileName1, ios::binary | ios::ate);
    if (!file1) {
        cerr << "Error: Could not open first file!" << endl;
        return 1;
    }

    size_t fileSize1 = file1.tellg();
    file1.seekg(0, ios::beg);

    size_t halfFileSize1 = fileSize1 / 2;
    file1.read(buffer1, min(halfFileSize1, (size_t)BUFFER_SIZE));
    file1.read(buffer2, min(fileSize1 - halfFileSize1, (size_t)BUFFER_SIZE));

    cout << "\n--- Loading first file into buffers ---" << endl;
    cout << "First half of first file loaded into buffer1" << endl;
    cout << "Second half of first file loaded into buffer2" << endl;

    cout << "\nContent of buffer1: " << buffer1 << endl;
    cout << "Content of buffer2: " << buffer2 << endl;

    // Get second file path from user
    string fileName2;
    cout << "\nEnter the second file path: ";
    getline(cin, fileName2);

    // Second file processing
    ifstream file2(fileName2, ios::binary | ios::ate);
    if (!file2) {
        cerr << "Error: Could not open second file!" << endl;
        return 1;
    }

    size_t fileSize2 = file2.tellg();
    file2.seekg(0, ios::beg);

    // Determine which buffer has more space and load the second file into it
    if (strlen(buffer1) < strlen(buffer2)) {
        file2.read(buffer1, min(fileSize2, (size_t)BUFFER_SIZE - strlen(buffer1)));
        cout << "\nSecond file loaded into buffer1" << endl;
    }
    else {
        file2.read(buffer2, min(fileSize2, (size_t)BUFFER_SIZE - strlen(buffer2)));
        cout << "\nSecond file loaded into buffer2" << endl;
    }

    cout << "\nFinal Content of buffer1: " << buffer1 << endl;
    cout << "Final Content of buffer2: " << buffer2 << endl;

    return 0;
}
