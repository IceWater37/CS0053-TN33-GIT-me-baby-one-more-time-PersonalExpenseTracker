#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <vector>

// Constants for input validation boundaries
constexpr double MIN_EXPENSE_AMOUNT = 0.01;
constexpr double MAX_EXPENSE_AMOUNT = 1000000.00;
const std::string DEFAULT_DATA_FILE = "expenses.csv";

struct Expense {
    int id;
    std::string date;        // Format: YYYY-MM-DD
    std::string category;    // e.g., Food, Transport, Utilities, School
    std::string description; // Brief note
    double amount;
};

// Member 3: Input Validation & File Storage (storage_validation.cpp)
int getValidInt(const std::string& prompt, int minVal, int maxVal);
double getValidDouble(const std::string& prompt, double minVal, double maxVal);
std::string getNonEmptyString(const std::string& prompt);
std::string getValidDate(const std::string& prompt);
bool loadFromFile(const std::string& filename, std::vector<Expense>& expenses);
bool saveToFile(const std::string& filename, const std::vector<Expense>& expenses);
int getNextId(const std::vector<Expense>& expenses);

// Member 2: Core CRUD Features (core_logic.cpp)
void addExpense(std::vector<Expense>& expenses);
void viewExpenses(const std::vector<Expense>& expenses);
void updateExpense(std::vector<Expense>& expenses);
void deleteExpense(std::vector<Expense>& expenses);

// Member 4: Search & Summary Analytics (summary_search.cpp)
void searchExpenses(const std::vector<Expense>& expenses);
void generateSummary(const std::vector<Expense>& expenses);

#endif // EXPENSE_H