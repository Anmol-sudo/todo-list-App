#ifndef TODO_H
#define TODO_H

#include <string>
#include <ctime>

struct Todo {
    std::string id;
    std::string title;
    std::string description;
    bool isDone;
    time_t timestamp; // Removed invalid initialization
};

#endif