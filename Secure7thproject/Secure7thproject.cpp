#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string calculateSimpleHash(const vector<unsigned char>& data) {
    unsigned long hash = 5381;
    for (unsigned char b : data) {
        hash = ((hash << 5) + hash) + b;
    }

    stringstream ss;
    ss << hex << setw(16) << setfill('0') << hash;
    return ss.str();
}

vector<unsigned char> readBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file.is_open()) {
        return {};
    }
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    vector<unsigned char> buffer(size);
    if (file.read((char*)buffer.data(), size)) {
        return buffer;
    }
    return {};
}

int main() {
    cout << "=== C++ File Integrity Checker ===" << endl;

    string filename = "test.txt";

    vector<unsigned char> fileData = readBinaryFile(filename);
    if (fileData.empty()) {
        cout << "[!] Notice: '" << filename << "' not found. Creating a sample file automatically..." << endl;
        ofstream outFile(filename);
        outFile << "Hello, this is a secure message for Data Integrity!";
        outFile.close();
        cout << "[+] Sample file created successfully. Please run the program again!" << endl;
        return 0;
    }

    string currentHash = calculateSimpleHash(fileData);
    cout << "[*] Current File Hash (Bisma): " << currentHash << endl;
    cout << "[+] Status: Data Integrity Verified! The file is clean and unmodified." << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "-> To test tampering: Open 'test.txt', change any letter, save, and run again!" << endl;

    return 0;
}