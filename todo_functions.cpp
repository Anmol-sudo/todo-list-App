// todo_functions.cpp
#include "todo_functions.h"
#include <iostream>
#include <limits>
#include <vector>
#include "todo.h"
#include <ctime>

using namespace std;

// --- Generic Input Helpers ---
string getNonEmptyInput(const string& prompt, bool clearBuffer = false) {
    string input;
    if (clearBuffer) cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!input.empty()) return input;
        cout << "Input cannot be empty. Please try again.\n";
    }
}

int getValidIndex(const vector<Todo>& vec, const string& action) {
    int todoNo;
    while (true) {
        cout << "Enter the serial number of the todo to " << action << ": ";
        if (cin >> todoNo && todoNo > 0 && todoNo <= (int)vec.size()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return todoNo - 1; // return as index
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number. Try again.\n";
    }
}

// --- Operations ---
void addTodo(vector<Todo>& vec) { 
    time_t timestamp; time(&timestamp);
    cout << "\nAdding a Todo:\n\n";

    string title = getNonEmptyInput("Enter a title: ", true);
    string description = getNonEmptyInput("Enter a description: ");

    vec.push_back({static_cast<int>(vec.size()) + 1, title, description, false, timestamp});
    cout << "Todo added successfully!\n";
}

void removeTodo(vector<Todo>& vec) {
    cout << "\nRemoving a Todo:\n";
    int idx = getValidIndex(vec, "remove");
    vec.erase(vec.begin() + idx);
    cout << "Todo removed successfully!\n";
}

void editTodo(vector<Todo>& vec) {
    cout << "\nEditing a Todo:\n";
    int idx = getValidIndex(vec, "edit");

    int choice;
    cout << "Choose an option:\n1. Title\n2. Description\n3. Both\nChoice: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Todo& todo = vec[idx];
    if (choice == 1 || choice == 3)
        todo.title = getNonEmptyInput("Enter new title: ");
    if (choice == 2 || choice == 3)
        todo.description = getNonEmptyInput("Enter new description: ");

    cout << "Todo edited successfully!\n";
}

void clearTodoList(vector<Todo>& vec) { 
    cout << "\nClearing Todo List...\n";
    vec.clear();
    cout << "Todo List cleared successfully!\n";
}

void markTodoDone(vector<Todo>& vec) {
    if (vec.empty()) {
        cout << "No todos to mark.\n";
        return;
    }
    
    int num;
    cout << "Enter the serial number of the todo you want to toggle (done/undone): ";
    cin >> num;

    if (num < 1 || num > static_cast<int>(vec.size())) {
        cout << "Invalid serial number.\n";
        return;
    }

    Todo &t = vec[num - 1];
    t.isDone = !t.isDone; // Toggle between done/undone

    if (t.isDone) {
        cout << "Todo marked as DONE: " << t.title << "\n";
    } else {
        cout << "Todo marked as UNDONE: " << t.title << "\n";
    }
}
