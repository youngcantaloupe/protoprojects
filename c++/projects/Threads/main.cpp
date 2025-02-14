#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex m;
std::ofstream outFile;
int totalPrimes = 0;
int threadPrimes[4] = {0, 0, 0, 0};
int currNum = 2;

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

void findPrimes(int threadNum) {
    while (true) {
        int num;

        {
            std::lock_guard<std::mutex> lock(m);
            if (currNum > 1000000) {
                break;
            }
            num = currNum++;
        }
        if (isPrime(num)) {
            {
                std::lock_guard<std::mutex> lock(m);
                outFile << num << std::endl;
                totalPrimes++;
                threadPrimes[threadNum]++;
            }
        }
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    outFile.open("primes.dat", std::ios::out);

    std::thread t1{findPrimes, 0};
    std::thread t2{findPrimes, 1};
    std::thread t3{findPrimes, 2};
    std::thread t4{findPrimes, 3};

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "Total primes found: " << totalPrimes << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << "Thread " << i + 1 << " found " << threadPrimes[i] << " prime numbers."
                  << std::endl;
    }

    outFile.close();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Execution time: " << duration.count() << " seconds." << std::endl;

    return 0;
}
