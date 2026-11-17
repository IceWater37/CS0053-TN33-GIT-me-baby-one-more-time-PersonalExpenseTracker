#include "expense.h"
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

using namespace std;

string toLowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(),
              [](unsigned char c) {
                  return static_cast<char>(tolower(c));
              });

    return text;
}

void displaySearchResults(const vector<Expense>& results) {

    if (results.empty()) {
        cout << "\n[Info] No matching expenses found.\n";
        return;
    }

    cout << "\n================ SEARCH RESULTS ================\n";

    cout << left
         << setw(6) << "ID"
         << setw(14) << "Date"
         << setw(18) << "Category"
         << setw(30) << "Description"
         << right << setw(12) << "Amount"
         << '\n';

    cout << string(80, '-') << '\n';

    for (const Expense& expense : results) {

        cout << left
             << setw(6) << expense.id
             << setw(14) << expense.date
             << setw(18) << expense.category
             << setw(30) << expense.description
             << right << "PHP "
             << fixed << setprecision(2)
             << setw(10) << expense.amount
             << '\n';
    }

    cout << string(80, '-') << '\n';

    cout << "Total Matches: " << results.size() << '\n';
}

void searchExpenses(const vector<Expense>& expenses) {

    if (expenses.empty()) {
        cout << "\n[Info] No expenses available to search.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "           SEARCH EXPENSES\n";
    cout << "========================================\n";

    cout << "1. Search by Category\n";
    cout << "2. Search by Description\n";
    cout << "3. Search by Date\n";

    int choice;

    while (true) {

        cout << "Select search type (1-3): ";

        if (cin >> choice && choice >= 1 && choice <= 3) {
            break;
        }

        cout << "[Error] Invalid choice. Enter 1-3.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string keyword;

    do {
        cout << "Enter search keyword: ";
        getline(cin, keyword);

        if (keyword.find_first_not_of(" \t\r\n") ==
            string::npos) {
            cout << "[Error] Search keyword cannot be empty.\n";
            keyword.clear();
        }

    } while (keyword.empty());

    string searchKey = toLowerCase(keyword);

    vector<Expense> matches;

    for (const Expense& expense : expenses) {

        string target;

        switch (choice) {

            case 1:
                target = expense.category;
                break;

            case 2:
                target = expense.description;
                break;

            case 3:
                target = expense.date;
                break;
        }

        target = toLowerCase(target);

        if (target.find(searchKey) != string::npos) {
            matches.push_back(expense);
        }
    }

    displaySearchResults(matches);
}


void generateSummary(const vector<Expense>& expenses) {

    cout << "\n========================================\n";
    cout << "         EXPENSE SUMMARY REPORT\n";
    cout << "========================================\n";

    if (expenses.empty()) {
        cout << "[Info] No expense records available.\n";
        return;
    }

    double totalAmount = 0.0;
    double highestAmount = expenses[0].amount;

    Expense highestExpense = expenses[0];

    map<string, double> categoryTotals;

    // Calculate totals and highest expense.
    for (const Expense& expense : expenses) {

        totalAmount += expense.amount;

        categoryTotals[expense.category] += expense.amount;

        if (expense.amount > highestAmount) {
            highestAmount = expense.amount;
            highestExpense = expense;
        }
    }

    double averageAmount =
        totalAmount / static_cast<double>(expenses.size());

    cout << fixed << setprecision(2);

    cout << "Total Records   : " << expenses.size() << '\n';

    cout << "Total Spent     : PHP "
         << totalAmount << '\n';

    cout << "Average Expense : PHP "
         << averageAmount << '\n';

    cout << "Highest Expense : PHP "
         << highestAmount << '\n';

    cout << "  Description   : "
         << highestExpense.description << '\n';

    cout << "  Date          : "
         << highestExpense.date << '\n';

    cout << "\nBreakdown by Category:\n";

    cout << left
         << setw(22) << "Category"
         << right
         << setw(18) << "Subtotal (PHP)"
         << setw(15) << "Share (%)"
         << '\n';

    cout << string(55, '-') << '\n';

    for (const auto& category : categoryTotals) {

        double percentage =
            (category.second / totalAmount) * 100.0;

        cout << left
             << setw(22) << category.first
             << right
             << setw(18) << category.second
             << setw(14) << percentage << "%"
             << '\n';
    }

    cout << string(55, '-') << '\n';

    cout << "[Success] Expense summary generated.\n";
}
