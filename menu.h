#ifndef MENU_H
#define MENU_H

#include <queue>
#include <algorithm>
#include <limits>
#include "flashcard.h"
#include "doubly_linked_list.h"
#include "file_handler.h"
#include "session.h"

using namespace std;

enum option_t {
    LEARNING,
    LIST,
    MODIFY,
    EXIT
};

class Menu {
private:
public:
    void display_menu() {
        cout << "[0] Start learning session" << endl;
        cout << "[1] Words list" << endl;
        cout << "[2] Modify words list" << endl;
        cout << "[3] Exit" << endl;
    }

    option_t get_option() {
        int option;
        while (1) {
            cout << "Enter option: ";
            cin >> option;
            if (cin.fail() || option < 0 || option > 3) {
                cerr << "Incorrect option" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }
        return static_cast<option_t>(option);
    }
};

#endif