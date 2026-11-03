# Secure Software Development 
## Data Integrity Verification Tool (C++)

### Project Overview
This project implements a Data Integrity service using a custom hash-based verification mechanism in C++. The program reads a target file in binary mode and computes a unique cryptographic-style fingerprint (hash) to ensure that no tampering or unauthorized modifications have occurred[cite: 2, 3].

### Project Files
- `Secure7thproject.cpp`: The main C++ source code file containing the file-reading and hashing algorithms.
- `test.txt`: The target text file verified by the application.

### System Requirements
- Microsoft Visual Studio (with C++ desktop development workload installed).

### How to Run and Test
1. **Open the Project:** Open Visual Studio and load the `Secure7thproject` solution.
2. **Build and Execute:** Click the green **Local Windows Debugger** button or press **Ctrl + F5**.
3. **Automatic Sample Creation:** On the first run, the program will automatically generate a sample file named `test.txt` if it does not exist, compute its hash, and display the verification status.
4. **Testing Tampering:** Open `test.txt`, modify any character or word, save the file, and re-run the program to observe how the hash value changes and detects the integrity violation.