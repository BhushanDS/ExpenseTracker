#include "ExpenseManager.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <algorithm>

ExpenseManager::ExpenseManager(const std::string& filename) : dataFile(filename)
{
    loadExpenses();
}

void ExpenseManager::loadExpenses()
{
    std::ifstream file(dataFile);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << dataFile << std::endl;
        return;
    }
	std::string line;
    expenses.clear();

    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            std::stringstream ss(line);
            std::string item;
            Expense e;
            std::getline(ss, item, ','); e.id = std::stoi(item);
            std::getline(ss, e.date, ',');
            std::getline(ss, e.description, ',');
            std::getline(ss, item, ','); e.amount = std::stod(item);
            expenses.push_back(e);
        }
    }
}

void ExpenseManager::saveExpenses() const
{
	std::ofstream file(dataFile);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << dataFile << std::endl;
		return;
	}
	for (const auto& e : expenses)
	{
		file << e.id << "," << e.date << "," << e.description << "," << e.amount << "\n";
	}
}

int ExpenseManager::getNextId() const
{
	int maxId = 0;
	for (const auto& e : expenses)
	{
		if (e.id > maxId)
			maxId = e.id;
	}
	return maxId + 1;
}

std::string ExpenseManager::getTodayDate() const  
{  
   std::time_t t = std::time(nullptr);  
   std::tm tm;  
   localtime_s(&tm, &t); // Replacing std::localtime_S with localtime_s for compatibility and safety  
   std::ostringstream oss;  
   oss << std::put_time(&tm, "%Y-%m-%d");  
   return oss.str();  
}

void ExpenseManager::addExpense(const std::string& description, double amount)
{
	Expense e;
	e.id = getNextId();
	e.date = getTodayDate();
	e.description = description;
	e.amount = amount;
	expenses.push_back(e);
	saveExpenses();
}


void ExpenseManager::updateExpense(int id, const std::string& description, double amount, bool updateDesc, bool updateAmt) {
	bool found = false;
	for (auto& e : expenses) {
		if (e.id == id) {
			if (updateDesc) e.description = description;
			if (updateAmt) e.amount = amount;
			found = true;
			break;
		}
	}
	if (!found) {
		std::cout << "Expense ID not found.\n";
		return;
	}
	saveExpenses();
	std::cout << "Expense updated successfully\n";
}

void ExpenseManager::deleteExpense(int id) {
    auto it = std::remove_if(expenses.begin(), expenses.end(), [id](const Expense& e) { return e.id == id; });
    if (it == expenses.end()) {
        std::cout << "Expense ID not found.\n";
        return;
    }
    expenses.erase(it, expenses.end());
    saveExpenses();
    std::cout << "Expense deleted successfully\n";
}

void ExpenseManager::listExpenses() const {
    std::cout << "ID  Date        Description      Amount\n";
    for (const auto& e : expenses) {
        std::cout << e.id << "   " << e.date << "  " << std::setw(12) << std::left << e.description
            << "  $" << std::fixed << std::setprecision(2) << e.amount << '\n';
    }
}

void ExpenseManager::summary(int month) const {
    double total = 0;
    std::string label = "Total expenses";
    if (month > 0) {
        time_t t = time(nullptr);
        tm now;
        
        localtime_s(&now, &t);
        int year = now.tm_year + 1900;
        for (const auto& e : expenses) {
            int y, m, d;
            if (sscanf_s(e.date.c_str(), "%d-%d-%d", &y, &m, &d) == 3) {
                if (y == year && m == month)
                    total += e.amount;
            }
        }
        std::cout << label << " for " << std::setfill('0') << std::setw(2) << month << ": $" << total << '\n';
    }
    else {
        for (const auto& e : expenses) total += e.amount;
        std::cout << label << ": $" << total << '\n';
    }
}