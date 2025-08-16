#include "todo_functions.h"
#include <iostream>
#include <limits>
#include <vector>
#include "todo.h"
#include <ctime>

using namespace std;

void addTodo(vector<Todo>& vec) { 
    time_t timestamp;
    time(&timestamp);
    cout << endl;
    cout << "Adding a Todo: " << endl; 
    cout << endl;
    string title, description;
    cout << "Enter a title of your todo: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // <--- fix
    getline(cin, title);
    cout << endl;
    cout << "Enter a description of your todo: ";
    getline(cin, description);
    cout << endl;
    vec.push_back({static_cast<int>(vec.size()) + 1, title, description, false, timestamp});
}

void removeTodo(vector<Todo>& vec) { 
    cout << "Removing a Todo: " << endl; 
    int todoNo;
    cout << "Enter the serial number of the todo you want to remove: ";
    cin >> todoNo; 
    vec.erase(vec.begin() + (todoNo - 1));
}

void editTodo(vector<Todo>& vec) { 
    cout << "Editing a Todo: " << endl; 
    int todoNo;
    cout << "Enter the serial number of the todo you want to edit: ";
    cin >> todoNo; 
    int choice;
    cout << "Choose an option:" << endl;
    cout << "1. Title" << endl;
    cout << "2. Description" << endl;
    cout << "3. Both" << endl;
    cout << "Enter your choice: ";

    cin >> choice;

    Todo& todo = vec[todoNo - 1];
    switch (choice) {
        case 1:
            cout << "Enter new title: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // <--- fix
            getline(cin, todo.title);
            break;
        case 2:
            cout << "Enter new description: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // <--- fix
            getline(cin, todo.description);
            break;
        case 3:
            cout << "Enter new title: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // <--- fix
            getline(cin, todo.title);
            cout << "Enter new description: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // <--- fix
            getline(cin, todo.description);
            break;
        default:
            cout << "Invalid choice." << endl;
    }
    cout << "Todo edited successfully." << endl;
}

void clearTodoList(vector<Todo>& vec) { 
    cout << "Clearing Todo List: " << endl; 
    vec.clear();
    cout << "Todo List cleared successfully." << endl;
}