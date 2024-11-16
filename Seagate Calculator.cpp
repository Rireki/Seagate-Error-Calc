/*2024/Nov/11
    Riri Furikawa, commit 1.0 : First commit
    1.1 : Added error handling to prevent crashes from adding trailing spaces at input
    2.0 : Migrated from Codeblocks to Visual Studio 2008, added a clarifying statement for the result of the app.
    */
// Seagate Calculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm> // for std::remove_if

unsigned long hexToDecimal(const std::string& hexStr) {
    unsigned long decimalValue;
    std::stringstream ss;
    ss << std::hex << hexStr;
    ss >> decimalValue;
    return decimalValue;
}

// Function to trim leading and trailing whitespace
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

void calculateErrorRate(const std::string& rawInput) {
    if (rawInput.length() > 12) {
        std::cerr << "Error: Input too long. Please enter a 12-character or shorter hexadecimal string." << std::endl;
        return;
    }

    // Pad the input to ensure it has at least 12 characters (e.g., "000004D15578")
    std::string paddedInput = rawInput;
    while (paddedInput.length() < 12) {
        paddedInput = "0" + paddedInput;
    }

    // Extract numerator and denominator in hexadecimal
    std::string numeratorHex = paddedInput.substr(0, 4);
    std::string denominatorHex = paddedInput.substr(4, 8);

    try {
        // Convert to decimal
        unsigned long numerator = hexToDecimal(numeratorHex);
        unsigned long denominator = hexToDecimal(denominatorHex);

        // Calculate error rate
        double errorRate = (denominator == 0) ? 0.0 : (static_cast<double>(numerator) / denominator) * 100;

        // Calculate "operations per 1 error"
        unsigned long operationsPerError = (numerator == 0) ? 0 : static_cast<unsigned long>(denominator / static_cast<double>(numerator));

        // Output results
        std::cout << "Decimal -> " << hexToDecimal(rawInput) << std::endl;
        std::cout << "Hexadecimal -> " << paddedInput.substr(0, 4) << " " << paddedInput.substr(4, 8) << std::endl;
        std::cout << "True error rate: " << numerator << " / " << denominator << " = " 
                  << std::fixed << std::setprecision(8) << errorRate << "%";

        if (numerator == 0) {
            std::cout << " (No errors were ever seen.)";
        }

        std::cout << std::endl;

        if (numerator > 0) {
            std::cout << "1 error out of approximately " << operationsPerError << " operations." << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid input format. Please enter a hexadecimal string." << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Input value is out of range." << std::endl;
    }
}

int main() {
    std::string rawInput;
    std::cout << "Enter the RAW error rate value (e.g., 130348226 or 000007C4F4C2): ";
    std::getline(std::cin, rawInput);

    // Trim the input to remove leading and trailing spaces
    rawInput = trim(rawInput);

    calculateErrorRate(rawInput);

    std::cout << "Press Enter to exit...";
    std::cin.ignore();
    std::cin.get();  // Wait for user to press Enter

    return 0;
}
