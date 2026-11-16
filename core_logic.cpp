#include "expense.h"
#include <iomanip>
#include <iostream>

void addExpense(std::vector<Expense>& expenses) {
    std::cout << "\n--- Add New Expense ---\n";

    Expense expense{};
    expense.id = getNextId(expenses);
    expense.date = getValidDate("Enter date (YYYY-MM-DD): ");
    expense.category =
        getNonEmptyString("Enter category (e.g., Food, Transport, Bills): ");
    expense.description = getNonEmptyString("Enter description: ");
    expense.amount = getValidDouble(
        "Enter amount (PHP): ",
        MIN_EXPENSE_AMOUNT,
        MAX_EXPENSE_AMOUNT
    );

    expenses.push_back(expense);

    std::cout << "  [Success] Expense ID #" << expense.id
              << " added successfully.\n";
}

void viewExpenses(const std::vector<Expense>& expenses) {
    std::cout << "\n--- All Recorded Expenses ---\n";

    if (expenses.empty()) {
        std::cout << "  No expense records found.\n";
        return;
    }

    std::cout << std::left
              << std::setw(6) << "ID"
              << std::setw(12) << "Date"
              << std::setw(16) << "Category"
              << std::setw(28) << "Description"
              << std::right << std::setw(12) << "Amount (PHP)"
              << '\n';

    std::cout << std::string(74, '-') << '\n';
    std::cout << std::fixed << std::setprecision(2);

    for (const auto& expense : expenses) {
        std::cout << std::left
                  << std::setw(6) << expense.id
                  << std::setw(12) << expense.date
                  << std::setw(16) << expense.category.substr(0, 14)
                  << std::setw(28) << expense.description.substr(0, 26)
                  << std::right << std::setw(12) << expense.amount
                  << '\n';
    }
}