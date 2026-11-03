
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
    string hashFile = "hash.txt";

    vector<unsigned char> fileData = readBinaryFile(filename);

    if (fileData.empty()) {
        cout << "[!] File not found or empty. Creating sample file..." << endl;

        ofstream outFile(filename);
        outFile << "Hello, this is a secure message for Data Integrity!";
        outFile.close();

        fileData = readBinaryFile(filename);
    }

    string currentHash = calculateSimpleHash(fileData);

    ifstream hashInput(hashFile);

    if (!hashInput.is_open()) {
        ofstream hashOutput(hashFile);
        hashOutput << currentHash;
        hashOutput.close();

        cout << "[+] Original Hash saved successfully!" << endl;
        cout << "[*] Original Hash: " << currentHash << endl;
        cout << "[+] File Integrity Verified!" << endl;
    }
    else {
        string originalHash;
        hashInput >> originalHash;
        hashInput.close();

        cout << "[*] Original Hash: " << originalHash << endl;
        cout << "[*] Current Hash: " << currentHash << endl;

        if (currentHash == originalHash) {
            cout << "[+] Status: File is clean and unmodified!" << endl;
        }
        else {
            cout << "[!] WARNING: File has been modified!" << endl;
            cout << "[!] Data Tampering Detected!" << endl;
        }
    }

    return 0;
}
