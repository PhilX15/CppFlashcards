#ifndef SESSION_H
#define SESSION_H

#include <queue>
#include <algorithm>
#include "flashcard.h"
#include "doubly_linked_list.h"
#include "file_handler.h"

using namespace std;

class Session {
private:
    List<Flashcard> flashcards;
    queue<Flashcard> flashcard_queue;
    unsigned int total_words;
    unsigned int guessed;
    unsigned int missed;

    void draw_words() {
        for (size_t i = 0; i < total_words && !flashcards.is_empty(); i++) {
            int random = rand() % flashcards.size();
            Flashcard flashcard = flashcards.pop(random);
            flashcard_queue.push(flashcard);
        }
    }

    string get_word_input() {
        cout << "Enter translation: ";
        string translation;
        cin >> translation;

        return translation;
    }

    void wait_for_input() {
        cout << "Press ENTER to continue...";
        getchar();
    }
public:
    Session() : total_words(5), guessed(0), missed(0) {
        ifstream file("words.txt");
        if (!file.is_open()) {
            cerr << "Could not open file" << endl;
            return;
        }
        auto maybe_flashcards = file_read(file);
        if (!maybe_flashcards) {
            cerr << "Failed to read file" << endl;
        } else {
            flashcards = *maybe_flashcards;
        }
    }

    void guessing() {
        draw_words();

        while (!flashcard_queue.empty()) {
            Flashcard flashcard = flashcard_queue.front();
            flashcard_queue.pop();

            clear_scr();
            flashcard.display(ORIGINAL);

            string translation = get_word_input();

            clear_scr();
            flashcard.display(TRANSLATED);

            if (find(flashcard.translated_words.begin(), flashcard.translated_words.end(), translation) != flashcard.translated_words.end()) {
                cout << "Correct!" << endl;
                if (flashcard.flag == NOT_TRAINED) {
                    guessed++;
                    flashcard.flag = GUESSED;
                } else {
                    flashcard.flag = GUESSED_AFTER_ATTEMPTS;
                }
            } else {
                cout << "Incorrect!" << endl;
                if (flashcard.flag == NOT_TRAINED) {
                    missed++;
                    flashcard.flag = MISSED;
                }
                flashcard_queue.push(flashcard);
            }

            while (getchar() != '\n');
            wait_for_input();
        }

        clear_scr();
        display_stats();
        wait_for_input();
    }

    void display_stats() {
        cout << "TOTAL WORDS: " << total_words << "\nGUESSED (IN THE FIRST ATTEMPT): " << guessed << "\nMISSED: " << missed << endl;
    }
};

#endif