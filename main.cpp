// main.cpp
#include "todo_functions.h"
#include "todo.h"
#include <iostream>
#include <limits>
#include <ctime>
#include <vector>
using namespace std;

void printWithBorder(const string &text) {
    int length = text.length();
    string border = "+" + string(length + 2, '-') + "+";

    cout << border << endl;
    cout << "  " << text << endl;
    cout << border << endl;
}

void printMenu() {
    cout << "\n====== MENU ======" << endl;
    cout << "1. Add a Todo" << endl;
    cout << "2. Delete a Todo" << endl;
    cout << "3. Edit a Todo" << endl;
    cout << "4. Clear Todo List" << endl;
    cout << "5. Mark a Todo as done/undone" << endl;
    cout << "6. Exit" << endl;
    cout << "==================" << endl;
    cout << "Enter choice: ";
}

// safe integer input
int getIntInput(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        }
        if (cin.eof()) {
            cout << "\nExiting...\n";
            exit(0);
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
    }
}

int main() {
    // Date and Time
    time_t timestamp;
    time(&timestamp);

    cout << "\n====================" << endl;
    cout << "Welcome to Todo List" << endl;
    cout << "====================" << endl;
    printWithBorder(ctime(&timestamp));
    cout << "\n";

    vector<Todo> todoList;

    while (true) {
        printMenu();
        int userInput = getIntInput("");

        switch (userInput) {
            case 1:
                addTodo(todoList);
                break;
            case 2:
                if (todoList.empty()) cout << "No todos to delete.\n";
                else removeTodo(todoList);
                break;
            case 3:
                if (todoList.empty()) cout << "No todos to edit.\n";
                else editTodo(todoList);
                break;
            case 4:
                if (todoList.empty()) cout << "List is already empty.\n";
                else clearTodoList(todoList);
                break;
             case 5:
                if (todoList.empty()) cout << "List is already empty.\n";
                else markTodoDone(todoList);
                break;
            case 6:
                cout << "Exiting... Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                
        }

        // Display current todos
        if (!todoList.empty()) {
            cout << "\nCurrent Todo List:\n";
            for (const auto &t : todoList) {
                cout << t.serialNo << ". " << t.title 
                     << " - " << t.description 
                     << " - " << (t.isDone ? "Done" : "Not Done")
                     << " - " << ctime(&t.timestamp);
            }
        }
        cout << endl;
    }
}
