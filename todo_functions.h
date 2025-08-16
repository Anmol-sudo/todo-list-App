#ifndef TODO_FUNCTIONS_H
#define TODO_FUNCTIONS_H
#include "todo.h"
#include <vector>  
using namespace std; 

void addTodo(vector<Todo>& vec);
void removeTodo(vector<Todo>& vec);
void editTodo(vector<Todo>& vec);
void clearTodoList(vector<Todo>& vec);

#endif // !TODO_FUNCTIONS_H
