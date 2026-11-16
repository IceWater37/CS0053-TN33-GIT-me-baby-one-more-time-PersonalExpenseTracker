#include "expense.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

static std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

int getValidInt(const std::string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (value >= minVal && value <= maxVal) {
                return value;
            }
            std::cout << "  [Error] Please enter a number between "
                      << minVal << " and " << maxVal << ".\n";
        } else {
            std::cout << "  [Error] Invalid numeric input. Please enter a whole number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

double getValidDouble(const std::string& prompt, double minVal, double maxVal) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (value >= minVal && value <= maxVal) {
                return value;
            }
            std::cout << "  [Error] Amount must be between "
                      << minVal << " and " << maxVal << ".\n";
        } else {
            std::cout << "  [Error] Invalid amount. Please enter a valid number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string getNonEmptyString(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        input = trim(input);
        // Replace commas to keep CSV format intact
        std::replace(input.begin(), input.end(), ',', ';');
        if (!input.empty()) {
            return input;
        }
        std::cout << "  [Error] This field cannot be empty.\n";
    }
}

std::string getValidDate(const std::string& prompt) {
    while (true) {
        std::string date = getNonEmptyString(prompt);
        if (date.length() == 10 && date[4] == '-' && date[7] == '-') {
            bool digitsOk = true;
            for (size_t i = 0; i < date.length(); ++i) {
                if (i == 4 || i == 7) continue;
                if (!std::isdigit(static_cast<unsigned char>(date[i]))) {
                    digitsOk = false;
                    break;
                }
            }
            if (digitsOk) {
                int month = std::stoi(date.substr(5, 2));
                int day = std::stoi(date.substr(8, 2));
                if (month >= 1 && month <= 12 && day >= 1 && day <= 31) {
                    return date;
                }
            }
        }
        std::cout << "  [Error] Invalid date. Use YYYY-MM-DD (e.g., 2026-11-15).\n";
    }
}

int getNextId(const std::vector<Expense>& expenses) {
    int maxId = 0;
    for (const auto& exp : expenses) {
        if (exp.id > maxId) {
            maxId = exp.id;
        }
    }
    return maxId + 1;
}

bool loadFromFile(const std::string& filename, std::vector<Expense>& expenses) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return false; // File may not exist on first run
    }
    expenses.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        if (trim(line).empty()) continue;
        std::stringstream ss(line);
        std::string idStr, date, category, description, amountStr;

        if (std::getline(ss, idStr, ',') &&
            std::getline(ss, date, ',') &&
            std::getline(ss, category, ',') &&
            std::getline(ss, description, ',') &&
            std::getline(ss, amountStr)) {
            try {
                Expense exp;
                exp.id = std::stoi(trim(idStr));
                exp.date = trim(date);
                exp.category = trim(category);
                exp.description = trim(description);
                exp.amount = std::stod(trim(amountStr));
                expenses.push_back(exp);
            } catch (...) {
                // Skip malformed CSV line safely
            }
        }
    }
    return true;
}

bool saveToFile(const std::string& filename, const std::vector<Expense>& expenses) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        return false;
    }
    for (const auto& exp : expenses) {
        outFile << exp.id << ","
                << exp.date << ","
                << exp.category << ","
                << exp.description << ","
                << exp.amount << "\n";
    }
    return true;
}