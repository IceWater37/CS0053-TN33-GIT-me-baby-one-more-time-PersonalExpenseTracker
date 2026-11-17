#include "expense.h"
#include <iostream>
#include <vector>

void displayMenu() {
    std::cout << "\n========================================\n"
              << "        PERSONAL EXPENSE TRACKER        \n"
              << "========================================\n"
              << "1. Add Expense\n"
              << "2. View All Expenses\n"
              << "3. Search Expenses\n"
              << "4. Update Expense\n"
              << "5. Delete Expense\n"
              << "6. Generate Expense Summary\n"
              << "7. Save & Exit\n"
              << "----------------------------------------\n";
}

int main() {
    std::vector<Expense> expenses;
    if (loadFromFile(DEFAULT_DATA_FILE, expenses)) {
        std::cout << "[Info] Loaded " << expenses.size()
                  << " record(s) from " << DEFAULT_DATA_FILE << ".\n";
    } else {
        std::cout << "[Info] No existing data file found. Starting with a new record list.\n";
    }

    bool running = true;
    while (running) {
        displayMenu();
        int choice = getValidInt("Select an option (1-7): ", 1, 7);

        switch (choice) {
            case 1:
                addExpense(expenses);
                saveToFile(DEFAULT_DATA_FILE, expenses);
                break;
            case 2:
                viewExpenses(expenses);
                break;
            case 3:
                searchExpenses(expenses);
                break;
            case 4:
                updateExpense(expenses);
                saveToFile(DEFAULT_DATA_FILE, expenses);
                break;
            case 5:
                deleteExpense(expenses);
                saveToFile(DEFAULT_DATA_FILE, expenses);
                break;
            case 6:
                generateSummary(expenses);
                break;
            case 7:
                if (saveToFile(DEFAULT_DATA_FILE, expenses)) {
                    std::cout << "[Info] Changes saved to " << DEFAULT_DATA_FILE << ". Goodbye!\n";
                } else {
                    std::cout << "[Error] Failed to save records to " << DEFAULT_DATA_FILE << ".\n";
                }
                running = false;
                break;
        }
    }
    return 0;
}