#ifndef APP_H
#define APP_H

#include <queue>
#include <algorithm>
#include "flashcard.h"
#include "doubly_linked_list.h"
#include "file_handler.h"
#include "session.h"
#include "menu.h"
#include "input_utils.h"

using namespace std;

class App {
private:
    List<Flashcard> flashcards;
    Session session;
public:
    void run() {
        load_words();

        Menu menu;

        while (true) {
            clear_scr();
            menu.display_menu();

            option_t option = menu.get_option();
            switch (option) {
                case LEARNING:
                    if (!session.has_flashcards()) {
                        clear_scr();
                        cerr << "No words available" << endl;

                        while (getchar() != '\n');
                        wait_for_input();
                    } else {
                        session.guessing();
                    }
                    break;
                case LIST:
                    clear_scr();
                    display_words();

                    while (getchar() != '\n');
                    wait_for_input();
                    break;
                case MODIFY:
                    break;
                case EXIT:
                    return;
            }
        }
    }

    void load_words() {
        ifstream file("words.txt");
        if (!file.is_open()) {
            cerr << "Could not open file" << endl;
            return;
        }
        auto maybe_flashcards = file_read(file);
        if (!maybe_flashcards) {
            cerr << "Failed to read file" << endl;
            return;
        }
        flashcards = *maybe_flashcards;

        if (!flashcards.is_empty()) {
            session.set_flashcards(flashcards);
        }
    }

    void display_words() {
        for (Flashcard flashcard : flashcards) {
            cout << flashcard;
        }
    }
};

#endif