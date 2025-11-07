#include "ExpenseManager.h"
#include <iostream>
#include <string>
#include <cstdlib>

void printUsage() {
    std::cout << "Expense Tracker - Command Line Application\n";
    std::cout << "Usage:\n";
    std::cout << "  expense-tracker <command> [options]\n\n";
    std::cout << "Commands:\n";
    std::cout << "  add --description <desc> --amount <amt>\n";
    std::cout << "      Add a new expense with description and amount.\n";
    std::cout << "  list\n";
    std::cout << "      List all expenses.\n";
    std::cout << "  update --id <id> [--description <desc>] [--amount <amt>]\n";
    std::cout << "      Update an expense's description and/or amount by ID.\n";
    std::cout << "  delete --id <id>\n";
    std::cout << "      Delete an expense by ID.\n";
    std::cout << "  summary [--month <m>]\n";
    std::cout << "      Show total expenses. If --month is provided, show summary for that month (1-12).\n";
    std::cout << "  --help\n";
    std::cout << "      Show this help message.\n\n";
    std::cout << "Examples:\n";
    std::cout << "  expense-tracker add --description \"Lunch\" --amount 20\n";
    std::cout << "  expense-tracker list\n";
    std::cout << "  expense-tracker update --id 1 --amount 25\n";
    std::cout << "  expense-tracker delete --id 2\n";
    std::cout << "  expense-tracker summary --month 8\n";
}

int main(int argc, char* argv[]) {
    ExpenseManager manager("expenses.csv");

    if (argc < 2) {
        printUsage();
        return 1;
    }
    std::string cmd = argv[1];

    if (cmd == "add") {
        std::string description;
        double amount = -1;
        for (int i = 2; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--description" && i + 1 < argc) {
                description = argv[++i];
            }
            else if (arg == "--amount" && i + 1 < argc) {
                amount = std::stod(argv[++i]);
            }
        }
        manager.addExpense(description, amount);
    }
    else if (cmd == "list") {
        manager.listExpenses();
    }
    else if (cmd == "delete") {
        int id = -1;
        for (int i = 2; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--id" && i + 1 < argc) {
                id = std::stoi(argv[++i]);
            }
        }
        if (id < 0) {
            std::cout << "Invalid input. Usage: delete --id <id>\n";
            return 1;
        }
        manager.deleteExpense(id);
    }
    else if (cmd == "update") {
        int id = -1;
        std::string description;
        double amount = -1;
        bool updateDesc = false, updateAmt = false;
        for (int i = 2; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--id" && i + 1 < argc) {
                id = std::stoi(argv[++i]);
            }
            else if (arg == "--description" && i + 1 < argc) {
                description = argv[++i];
                updateDesc = true;
            }
            else if (arg == "--amount" && i + 1 < argc) {
                amount = std::stod(argv[++i]);
                updateAmt = true;
            }
        }
        if (id < 0) {
            std::cout << "Invalid input. Usage: update --id <id> [--description <desc>] [--amount <amt>]\n";
            return 1;
        }
        manager.updateExpense(id, description, amount, updateDesc, updateAmt);
    }
    else if (cmd == "summary") {
        int month = 0;
        for (int i = 2; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--month" && i + 1 < argc) {
                month = std::stoi(argv[++i]);
            }
        }
        manager.summary(month);
    }
    else {
        std::cout << "Unknown command.\n";
        printUsage();
        return 1;
    }
    return 0;
}
