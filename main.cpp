#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>

unsigned long hexToDecimal(const std::string& hexStr) {
    unsigned long decimalValue;
    std::stringstream ss;
    ss << std::hex << hexStr;
    ss >> decimalValue;
    return decimalValue;
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

        // Output results
        std::cout << "Decimal -> " << hexToDecimal(rawInput) << std::endl;
        std::cout << "Hexadecimal -> " << paddedInput.substr(0, 4) << " " << paddedInput.substr(4, 8) << std::endl;
        std::cout << "True error rate: " << numerator << " / " << denominator << " = "
                  << std::fixed << std::setprecision(8) << errorRate << "%";

        if (numerator == 0) {
            std::cout << " (No errors were ever seen.)";
        }

        std::cout << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid input format. Please enter a hexadecimal string." << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Input value is out of range." << std::endl;
    }
}

int main() {
    std::string rawInput;
    std::cout << "Enter the RAW error rate value (e.g., 130348226 or 000007C4F4C2): ";
    std::cin >> rawInput;

    calculateErrorRate(rawInput);

    std::cout << "Press Enter to exit...";
    std::cin.ignore();
    std::cin.get();  // Wait for user to press Enter

    return 0;
}
