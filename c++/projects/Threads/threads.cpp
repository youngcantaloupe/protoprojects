#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex fileMutex;               // Mutex for file and counter protection
std::ofstream outfile;              // Global output file stream for writing primes
int totalPrimes = 0;                // Global counter for total primes found
int threadPrimes[4] = {0, 0, 0, 0}; // Array to track primes found by each thread
int currentNumber = 2;              // Shared counter for the next number to check

// Function to check if a number is prime
bool isPrime(int n) {
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false; // Skip even numbers
    for (int i = 3; i <= n / 2; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// Function to find primes and write them to the file
void findPrimes(int threadIndex) {
    while (true) {
        int num;

        {
            // Lock the shared counter to access and update it safely
            std::lock_guard<std::mutex> lock(fileMutex);
            if (currentNumber > 1000000) {
                break; // Exit if checked up to 1,000,000
            }
            num = currentNumber++; // Get next number to check and increment
        }

        if (isPrime(num)) {
            // Lock the file writing section
            {
                std::lock_guard<std::mutex> lock(fileMutex);
                outfile << num << std::endl; // Write prime to file
            }
            // Update the prime counters
            {
                std::lock_guard<std::mutex> lock(fileMutex);
                totalPrimes++;
                threadPrimes[threadIndex]++; // Increment the prime count for
                                             // this thread
            }
        }
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    // Open file for writing primes
    outfile.open("threadPrimes.dat", std::ios::out);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Create 4 threads to find primes
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.push_back(std::thread(findPrimes, i));
    }

    // Join all threads
    for (auto &t : threads) {
        t.join();
    }

    // Print the total primes found
    std::cout << "Total primes found: " << totalPrimes << std::endl;

    // Print the number of primes found by each thread
    for (int i = 0; i < 4; ++i) {
        std::cout << "Thread " << i + 1 << " found " << threadPrimes[i] << " primes." << std::endl;
    }

    // Close the file
    outfile.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds." << std::endl;
    return 0;
}
