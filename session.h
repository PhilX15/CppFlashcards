#ifndef SESSION_H
#define SESSION_H

#include <queue>
#include <algorithm>
#include "flashcard.h"
#include "doubly_linked_list.h"
#include "file_handler.h"
#include "input_utils.h"

using namespace std;

class Session {
private:
    List<Flashcard> flashcards;
    queue<Flashcard> flashcard_queue;
    unsigned int total_words;
    unsigned int guessed;
    unsigned int missed;

    void draw_words() {
        List<Flashcard> flashcards_copy = flashcards;
        for (size_t i = 0; i < total_words && !flashcards_copy.is_empty(); i++) {
            int random = rand() % flashcards_copy.size();
            Flashcard flashcard = flashcards_copy.pop(random);
            flashcard_queue.push(flashcard);
        }
    }

    string get_word_input() {
        cout << "Enter translation: ";
        string translation;
        cin >> translation;

        return translation;
    }
public:
    Session() : total_words(0), guessed(0), missed(0) {}

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

    void set_flashcards(List<Flashcard> flashcards) {
        this->flashcards = flashcards;
        total_words = flashcards.size();
    }

    bool has_flashcards() {
        return !flashcards.is_empty();
    }

    void display_stats() {
        cout << "TOTAL WORDS: " << total_words << "\nGUESSED (IN THE FIRST ATTEMPT): " << guessed << "\nMISSED: " << missed << endl;
    }
};

#endif