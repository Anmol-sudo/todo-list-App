#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <winsock2.h> 
#include "todo_functions.h"
#include <iostream>
#include <curl/curl.h>
#include <sstream>
#include <iomanip>
#include <limits>
#include <nlohmann/json.hpp> 
using json = nlohmann::json;
using namespace std;


#ifdef max
#undef max
#endif


size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


string getNonEmptyInput(const string& prompt, bool clearBuffer) {
    string input;
    if (clearBuffer) cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!input.empty()) return input;
        cout << "Input cannot be empty.\n";
    }
}

int getValidIndex(const vector<Todo>& vec, const string& action) {
    int todoNo;
    while (true) {
        cout << "Enter the number of the todo to " << action << ": ";
        if (cin >> todoNo && todoNo > 0 && todoNo <= (int)vec.size()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return todoNo - 1;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number. Try again.\n";
    }
}


void addTodoToFirebase(const Todo& todo, const string& firebaseUrl) {
    CURL* curl = curl_easy_init();
    if (!curl) return; // Fixed: Replaced ifsparql_endpoint_url with if

    string url = firebaseUrl;
    json j;
    j["title"] = todo.title;
    j["description"] = todo.description;
    j["isDone"] = todo.isDone;
    j["timestamp"] = todo.timestamp;

    string jsonStr = j.dump();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, nullptr);

    string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) cout << "Error adding todo: " << curl_easy_strerror(res) << endl;

    curl_easy_cleanup(curl);
}

vector<Todo> getAllTodosFromFirebase(const string& firebaseUrl) {
    vector<Todo> todos;
    CURL* curl = curl_easy_init();
    if (!curl) return todos;

    string url = firebaseUrl;
    string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cout << "Error fetching todos: " << curl_easy_strerror(res) << endl;
        curl_easy_cleanup(curl);
        return todos;
    }

    curl_easy_cleanup(curl);

    if (response.empty() || response == "null") return todos;

    auto j = json::parse(response);
    for (auto& [key, value] : j.items()) {
        Todo t;
        t.id = key;
        t.title = value["title"].get<std::string>();
        t.description = value["description"].get<std::string>();
        t.isDone = value["isDone"].get<bool>();
        t.timestamp = value["timestamp"].get<time_t>();
        todos.push_back(t);
    }
    return todos;
}

void removeTodoFromFirebase(const string& todoId, const string& firebaseUrl) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        cout << "Error initializing CURL for deletion" << endl;
        return;
    }

    // Correct URL: Use base URL up to the last '/' and append /todos/<todoId>.json
    string baseUrl = firebaseUrl.substr(0, firebaseUrl.find(".json")) + "/";
    string url = baseUrl + todoId + ".json";
    
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cout << "Error deleting todo: " << curl_easy_strerror(res) << endl;
        cout << "Response: " << response << endl;
    } else {
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        if (http_code == 200) {
            cout << "Todo deleted successfully" << endl;
        } else {
            cout << "Failed to delete todo. HTTP Code: " << http_code << ", Response: " << response << endl;
        }
    }

    curl_easy_cleanup(curl);
}

void editTodoInFirebase(const Todo& todo, const string& firebaseUrl) {
    CURL* curl = curl_easy_init();
    if (!curl) return;

    string baseUrl = firebaseUrl.substr(0, firebaseUrl.find(".json"));
    string url = baseUrl + "/" + todo.id + ".json";
    
    json j;
    j["title"] = todo.title;
    j["description"] = todo.description;
    j["isDone"] = todo.isDone;
    j["timestamp"] = todo.timestamp;

    string jsonStr = j.dump();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());

    string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}

void markTodoDoneInFirebase(const string& todoId, bool isDone, const string& firebaseUrl) {
    CURL* curl = curl_easy_init();
    if (!curl) return;

    string baseUrl = firebaseUrl.substr(0, firebaseUrl.find(".json"));
    string url = baseUrl + '/' + todoId + ".json"; 
    json j;
    j["isDone"] = isDone;
    string jsonStr = j.dump();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());

    string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
}