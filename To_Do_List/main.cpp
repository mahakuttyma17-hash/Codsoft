#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Task {
public:
    string name;
    bool completed;
};
int main() {
    vector<Task> todoList; 
    int choice;
    while (true) {
        cout << "\n========== TO-DO LIST (CLASS VERSION) ==========\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Remove Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            Task t;
            cin.ignore();
            cout << "Enter Task: ";
            getline(cin, t.name);
            t.completed = false;
            todoList.push_back(t); 
            cout << "Task Added Successfully!\n";
            break;
        }
        case 2: {
            if (todoList.empty()) {
                cout << "No tasks available.\n";
            }
            else {
                cout << "\n------ Task List ------\n";
                for (int i = 0; i < todoList.size(); i++) {
                    cout << i + 1 << ". "
                        << todoList[i].name
                        << " ["
                        << (todoList[i].completed ? "Completed" : "Pending")
                        << "]\n";
                }
            }
            break;
        }
        case 3: {
            int index;
            cout << "Enter task number to mark as completed: ";
            cin >> index;
            if (index >= 1 && index <= todoList.size()) {
                todoList[index - 1].completed = true;
                cout << "Task Marked as Completed!\n";
            }
            else {
                cout << "Invalid Task Number!\n";
            }
            break;
        }
        case 4: {
            int index;
            cout << "Enter task number to remove: ";
            cin >> index;
            if (index >= 1 && index <= todoList.size()) {
                todoList.erase(todoList.begin() + index - 1);
                cout << "Task Removed Successfully!\n";
            }
            else {
                cout << "Invalid Task Number!\n";
            }
            break;
        }
        case 5:
            cout << "Thank you for using To-Do List!\n";
            return 0;

        default:
            cout << "Invalid Choice! Try Again.\n";
        }
    }

    return 0;
}