#ifndef TODO_FUNCTIONS_H
#define TODO_FUNCTIONS_H

#include "todo.h"
#include <string>
#include <vector>

using namespace std;

// Firebase operations
void addTodoToFirebase(const Todo& todo, const string& firebaseUrl);
void removeTodoFromFirebase(const string& todoId, const string& firebaseUrl); // Fixed typo: firebaseUrln -> firebaseUrl
void editTodoInFirebase(const Todo& todo, const string& firebaseUrl);
void markTodoDoneInFirebase(const string& todoId, bool isDone, const string& firebaseUrl);
vector<Todo> getAllTodosFromFirebase(const string& firebaseUrl);

// Helpers
string getNonEmptyInput(const string& prompt, bool clearBuffer = false);
int getValidIndex(const vector<Todo>& vec, const string& action);

#endif