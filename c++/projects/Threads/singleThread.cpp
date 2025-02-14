#include <chrono>
#include <fstream>
#include <iostream>

std::ofstream outFile;
int totalPrimes = 0;
int currNum = 2;
int countTo = 1000000;

bool isPrime(int n) {
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    for (int i = 3; i <= n / 2; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

void findPrimes() {
    while (currNum <= countTo) {
        if (isPrime(currNum)) {
            outFile << currNum << std::endl;
            totalPrimes++;
        }
        currNum++;
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    outFile.open("singleThreadPrimes.dat", std::ios::out);

    findPrimes();
    std::cout << "Total primes found: " << totalPrimes << std::endl;

    outFile.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Execution time: " << duration.count() << " seconds." << std::endl;

    return 0;
}
