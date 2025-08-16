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
  cout << endl;
  cout << "  " << text << endl;
  cout << border << endl;

}

int main() {
  // Date and Time Logic
  time_t timestamp;
  time(&timestamp);

  cout << "\n";
  cout << "====================" << endl;
  cout << "Welcome to Todo List" << endl;
  cout << "====================" << endl;
  cout << "\n";

  // cout << " " << ctime(&timestamp);
  printWithBorder(ctime(&timestamp));

  cout << "\n";
  int userInput = 0;
  vector<Todo> todoList;
  // todoList.push_back({1, "Buy milk", "From the grocery store", false, timestamp});
  // cout << endl;
  // for (const auto &t : todoList) {
  //   cout << t.serialNo << ". " << t.title << " - " << t.description << " - "
  //        << (t.isDone ? "Done" : "Not Done") << " - " << ctime(&t.timestamp)
  //        << endl;
  // }

  bool flag = true;
  int count = 0;

  while (true) {
    if (count > 0) {
      flag = false;
    }

    if (flag) {
      cout << "\nEnter 1 to add a Todo";
      cout << "\nEnter 2 to delete a Todo";
      cout << "\nEnter 3 to edit a Todo";
      cout << "\nEnter 4 to clear Todo List";
      cout << endl;
    }
    flag = false;

    cout << "\nEnter choice: ";

    if (!(cin >> userInput)) { // if extraction fails
      if (cin.eof()) {         // Ctrl+Z or EOF
        cout << "\nExiting...\n";
        break;
      }
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n'); // discard invalid input
      cout << "Please enter a number.\n";
      continue; // retry input
    }
    cout << "You entered: " << userInput << endl;

    switch (userInput) {
    case 1:
      addTodo(todoList);
      break; 

    case 2:
      removeTodo(todoList);
      break; 

    case 3:
      editTodo(todoList);
      break;

    case 4:
      clearTodoList(todoList);
      break;

    default:
      break;
    }

    for (const auto &t : todoList) {
      cout << t.serialNo << ". " << t.title << " - " << t.description << " - "
           << (t.isDone ? "Done" : "Not Done") << " - " << ctime(&t.timestamp)
           << endl;
    }

    if (!(count < 1)) {
      count++;
    }
  }

  return 0;
}
