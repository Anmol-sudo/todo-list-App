#include "todo_functions.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const string FIREBASE_URL = getenv("FIREBASE_URL") ? getenv("FIREBASE_URL") : "";

void printWithBorder(const string &text) {
    int length = text.length();
    string border = "+" + string(length + 2, '-') + "+";
    cout << border << endl;
    cout << "  " << text << endl;
    cout << border << endl;
}

void printMenu() {
    cout << "\n====== MENU ======\n";
    cout << "1. Add a Todo\n";
    cout << "2. Delete a Todo\n";
    cout << "3. Edit a Todo\n";
    cout << "4. Clear Todo List\n";
    cout << "5. Mark a Todo as done/undone\n";
    cout << "6. Exit\n";
    cout << "==================\n";
    cout << "Enter choice: ";
}

int main() {
    cout << "\n====================\n";
    cout << "Welcome to Todo List\n";
    cout << "====================\n";

    time_t timestamp;
    time(&timestamp);
    printWithBorder(ctime(&timestamp));

    while (true) {
        vector<Todo> todoList = getAllTodosFromFirebase(FIREBASE_URL);

      
        if (!todoList.empty()) {
            cout << "\nCurrent Todo List:\n";
            int idx = 1;
            for (auto &t : todoList) {
                cout << idx++ << ". " << t.title 
                     << " - " << t.description 
                     << " - " << (t.isDone ? "Done" : "Not Done")
                     << " - " << ctime(&t.timestamp);
            }
        }

        printMenu();
        int userInput;
        cin >> userInput;
        

        switch (userInput) {
            case 1: {
                Todo t;
                t.title = getNonEmptyInput("Enter title: ", true);
                t.description = getNonEmptyInput("Enter description: ");
                t.isDone = false;
                t.timestamp = time(nullptr);
                addTodoToFirebase(t, FIREBASE_URL);
                break;
            }
            case 2: {
                if (todoList.empty()) { cout << "No todos to delete.\n"; break; }
                int idx = getValidIndex(todoList, "delete");
                removeTodoFromFirebase(todoList[idx].id, FIREBASE_URL);
                break;
            }
            case 3: {
                if (todoList.empty()) { cout << "No todos to edit.\n"; break; }
                int idx = getValidIndex(todoList, "edit");
                Todo t = todoList[idx];
                t.title = getNonEmptyInput("New title: ");
                t.description = getNonEmptyInput("New description: ");
                editTodoInFirebase(t, FIREBASE_URL);
                break;
            }
            case 4: {
                cout << "Clearing all todos...\n";
                for (auto &t : todoList)
                    removeTodoFromFirebase(t.id, FIREBASE_URL);
                break;
            }
            case 5: {
                if (todoList.empty()) { cout << "No todos to mark.\n"; break; }
                int idx = getValidIndex(todoList, "mark");
                bool newStatus = !todoList[idx].isDone;
                markTodoDoneInFirebase(todoList[idx].id, newStatus, FIREBASE_URL);
                break;
            }
            case 6:
                cout << "Exiting... Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}