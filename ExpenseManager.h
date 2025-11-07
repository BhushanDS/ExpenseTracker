#pragma once
#include "Expense.h"
#include <vector>
#include <string>
#include "Expense.h"
#include <vector>
#include <string>
using namespace std;

class ExpenseManager {
public :
	ExpenseManager(const std::string& filename);
	void addExpense(const std::string& description, double amount);
	void updateExpense(int id, const std::string& description, double amount, bool updateDesc, bool updateAmt);
	void deleteExpense(int id);
	void listExpenses() const;
	void summary(int month = 0) const;
private:
	std::string dataFile;
	std::vector<Expense> expenses;
	void loadExpenses();
	void saveExpenses() const;
	int getNextId() const;
	std::string getTodayDate() const;
};
