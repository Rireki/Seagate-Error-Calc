/*
2024/Nov/11
    Riri Furikawa, commit 1.0 : First commit
    1.1 : Added error handling to prevent crashes from adding trailing spaces at input
    2.0 : Migrated from Codeblocks to Visual Studio 2008, added a clarifying statement for the result of the app.
2024/Nov/17:
	2.1 : Added a selection to make the program able to restart or to quit after output.
    */
// Seagate Calculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <conio.h> // For _kbhit() and _getch()

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

// Function to remove spaces from the input
std::string removeSpaces(const std::string& str) {
    std::string noSpaces = str;
    noSpaces.erase(std::remove(noSpaces.begin(), noSpaces.end(), ' '), noSpaces.end());
    return noSpaces;
}

// Function to categorize the error rate
std::string categorizeErrorRate(double errorRate) {
    if (errorRate >= 0.0001 && errorRate <= 0.001) {
        return "Negligible";
    }
    if (errorRate >= 0.005 && errorRate <= 0.01) {
        return "Warning";
    }
    if (errorRate >= 0.1 && errorRate <= 1.0) {
        return "Bad";
    }
    return "Normal"; // For other cases that don't fall within the above ranges
}

void generateAsciiTable(double errorRate) {
    std::cout << "\nPlease consider backing up all data from the hard disk because a non-zero error rate is a warning that the drive is failing.\n";
}


void calculateErrorRate(const std::string& rawInput) {
    std::string cleanedInput = removeSpaces(rawInput);

    if (cleanedInput.length() > 12) {
        std::cerr << "Error: Input too long. Please enter a 12-character or shorter hexadecimal string." << std::endl;
        return;
    }

    // Pad the input to ensure it has at least 12 characters (e.g., "000004D15578")
    std::string paddedInput = cleanedInput;
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
        } else {
            std::cout << "\n(Please consider backing up all data from the hard disk because a non-zero error rate is a warning that the drive is failing.)";
        }

        std::cout << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid input format. Please enter a hexadecimal string." << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Input value is out of range." << std::endl;
    }
}

// Function to display and handle the menu
void displayMenu() {
    int choice = 0;  // 0 for Recalculate, 1 for Exit
    const int totalChoices = 2;

    while (true) {
        // Display menu
        std::cout << "\nSelect an option:" << std::endl;
        std::cout << (choice == 0 ? "> Recalculate (R)" : "  Recalculate (R)") << std::endl;
        std::cout << (choice == 1 ? "> Exit (Q/Esc)" : "  Exit (Q/Esc)") << std::endl;

        // Wait for key press
        char key = _getch();

        if (key == 27 || key == 'q' || key == 'Q') {  // Exit
            std::cout << "\nExiting program..." << std::endl;
            exit(0);  // Exit the program
        }
        else if (key == 'r' || key == 'R') {  // Recalculate
            break;
        }
        else if (key == 224) {  // Arrow keys (special key code)
            key = _getch();  // Capture the actual key after the arrow key
            if (key == 72) {  // Up arrow
                choice = (choice > 0) ? choice - 1 : totalChoices - 1;
            }
            else if (key == 80) {  // Down arrow
                choice = (choice + 1) % totalChoices;
            }
        }
    }
}

void inputAndCalculate() {
    std::string rawInput;

    // Get the raw input from the user
    std::cout << "Enter the RAW error rate value (e.g., 000007C4F4C2): ";
    std::getline(std::cin, rawInput);

    // Trim the input to remove leading and trailing spaces
    rawInput = trim(rawInput);

    // Calculate the error rate and display results
    calculateErrorRate(rawInput);

    // Inform the user to press enter before navigating
    std::cout << "\nPress Enter if you're done with analyzing the output...";

    // Wait for Enter key to proceed to the menu (only one Enter press required now)
    std::cin.get();  // Wait for user to press Enter
}

int main() {
    while (true) {
        inputAndCalculate();

        // Display menu with options for the user to choose
        displayMenu();
    }

    return 0;
}
