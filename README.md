# ExpenseTracker
Track you Expense

## High-LEvel Design
### 1. Overview:
The Expense Manager is a command - line application that allows users to manage their personal expenses.
It supports adding, updating, deleting & listing and summaraising expenses.
Data is persisted in CSV.

### 2. Main Component
* Expense
* Expense MAnager
* Commandline Interface

### 3. Data Flow
* User enter CLI command
* CLI Parse and call the appropriate method in Expense Manager.
* Expanse MAnager load CSV file, perform the operation and saves the changes back to the file.
* Output is displayed to customer.

### Key Features:
* A, U, D, L, S
* View Total expense of Month.
* Data store in a CSV file for persistence.

## Low Level Design
## 1. Class Diagramme
```
+----------------+         +-------------------+
|   Expense      |         |  ExpenseManager   |
+----------------+         +-------------------+
| int id         |<>------>| vector<Expense>   |
| string date    |         | string dataFile   |
| string desc    |         +-------------------+
| double amount  |         | +addExpense()     |
+----------------+         | +updateExpense()  |
                           | +deleteExpense()  |
                           | +listExpenses()   |
                           | +summary()        |
                           | -loadExpenses()   |
                           | -saveExpenses()   |
                           | -getNextId()      |
                           | -getTodayDate()   |
                           +-------------------+
```
## 2. Class Details
### Expense
•	Fields:
•	int id — Unique identifier for the expense.
•	string date — Date in YYYY-MM-DD format.
•	string description — Description of the expense.
•	double amount — Amount spent.
### ExpenseManager
•	Fields:
  vector<Expense> expenses — In-memory list of expenses.
  string dataFile — Path to the CSV file.
•	Methods:
  ExpenseManager(const string& filename) — Constructor, loads expenses from file.
  void addExpense(const string& description, double amount)
  void updateExpense(int id, const string& description, double amount, bool updateDesc, bool updateAmt)
  void deleteExpense(int id)
  void listExpenses() const
  void summary(int month = 0) const
  void loadExpenses()
  void saveExpenses() const
  int getNextId() const
  string getTodayDate() const

## 3. File Structure
•	Expense.h — Defines the Expense struct.
•	ExpenseManager.h / ExpenseManager.cpp — Declares and implements the ExpenseManager class.
•	main.cpp — Handles command-line parsing and user interaction.

## 4. Persistence
•	Expenses are stored in a CSV file (expenses.csv).
•	Each line: id,date,description,amount

## 5. Error Handling
•	Input validation for negative amounts, missing fields, and invalid IDs.
•	Graceful handling of file I/O errors.
```
Example Flow
1.	Add Expense
•	User: expense-tracker add --description "Lunch" --amount 20
•	CLI parses and calls ExpenseManager::addExpense("Lunch", 20)
•	Expense is added, saved to file, and confirmation is shown.
2.	List Expenses
•	User: expense-tracker list
•	CLI calls ExpenseManager::listExpenses()
•	All expenses are displayed.
```
Summary:
•	HLD covers the overall structure and main components.
•	LLD details class members, methods, file structure, and data flow.
