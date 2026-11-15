# CS0053-TN33 — Personal Expense Tracker
**Group:** GIT-me-baby-one-more-time  
**Section:** TN33  
**Repository:** [CS0053-TN33-GIT-me-baby-one-more-time-Personal-Expense-Tracker](https://github.com/IceWater37/CS0053-TN33-GIT-me-baby-one-more-time-PersonalExpenseTracker)

## 1. Project Purpose
The **Personal Expense Tracker** is a console-based C++ application designed to help users record, manage, search, and analyze their daily financial expenses. All records are automatically saved to and loaded from a local `expenses.csv` file so data persists across sessions.

## 2. Key Features
1. **Add Expense:** Records a new expense with an auto-incremented ID, validated `YYYY-MM-DD` calendar date, category, comma-sanitized description, and validated PHP amount (`0.01` to `1,000,000.00`).
2. **View All Expenses:** Displays all stored expenses in a formatted, aligned console table.
3. **Search Expenses:** Filters records case-insensitively by category, description keyword, or date substring.
4. **Update Expense:** Modifies the date, category, description, and amount of an existing record by ID.
5. **Delete Expense:** Removes a target expense record by ID and updates the local CSV file.
6. **Generate Expense Summary:** Calculates total records, total amount spent, average expense, highest single expense, and a per-category subtotal and percentage share breakdown.
7. **Automatic CSV Persistence & Input Validation:** Loads `expenses.csv` on startup, saves after every change, and recovers cleanly from non-numeric or out-of-range inputs without infinite loops.

## 3. Required Tools & Compiler
* **Editor:** Visual Studio Code with the C/C++ Extension Pack
* **Compiler:** `g++` (GCC / MinGW-w64 / MSYS2) supporting **C++20** (`-std=c++20`)
* **Debugger:** GDB (`gdb`) integrated with VS Code
* **Formatter & Static Analysis:** `clang-format` and `cppcheck` / `clang-tidy`

## 4. Compilation and Execution Instructions

### Multi-File Build (Segmented Group Modules)
Open the VS Code terminal in the project folder and run:
```bash
g++ -std=c++20 -Wall -Wextra -g main.cpp storage_validation.cpp core_logic.cpp summary_search.cpp -o tracker
./tracker
```

### Single-File Build (Standalone Testing)
If testing the consolidated single-file version (`expense_tracker.cpp`):
```bash
g++ -std=c++20 -Wall -Wextra -g expense_tracker.cpp -o tracker
./tracker
```
*(On Windows Command Prompt or PowerShell, run `.\tracker.exe` instead of `./tracker`.)*

## 5. Sample Input and Output

```text
[Info] Loaded 2 record(s) from expenses.csv.

========================================
        PERSONAL EXPENSE TRACKER        
========================================
1. Add Expense
2. View All Expenses
3. Search Expenses
4. Update Expense
5. Delete Expense
6. Generate Expense Summary
7. Save & Exit
----------------------------------------
Select an option (1-7): abc
  [Error] Invalid numeric input. Please enter a whole number.
Select an option (1-7): 1

--- Add New Expense ---
Enter date (YYYY-MM-DD): 2026-11-15
Enter category (e.g., Food, Transport, Bills): Food
Enter description: Chicken meal
Enter amount (PHP): 185.50
  [Success] Expense ID #3 added successfully.

Select an option (1-7): 6

--- Expense Summary Report ---
Total Records   : 3
Total Spent     : PHP 455.50
Average Expense : PHP 151.83
Highest Expense : PHP 200.00 (Bus load reload on 2026-11-14)

Breakdown by Category:
Category            Subtotal (PHP)   Share (%)
--------------------------------------------
Food                        255.50      56.09%
Transport                   200.00      43.91%
```