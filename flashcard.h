#include <string>
#include <ostream>
#include <vector>
#include "print_utils.h"

using namespace std;

enum word_type_t {
    ORIGINAL,
    TRANSLATED
};

enum flag_t {
    NOT_TRAINED,
    GUESSED,
    MISSED,
    GUESSED_AFTER_ATTEMPTS
};

class Flashcard {
public:
    string original_word;
    vector<string> translated_words;
    flag_t flag;

    Flashcard(string original, string translated) : original_word(original), flag(NOT_TRAINED) {
        translated_words.push_back(translated);
    }

    void display(enum word_type_t word_type) const {
        switch (word_type) {
            case ORIGINAL:
                print_frame(original_word.c_str());
                break;
            case TRANSLATED:
                string translations;
                for (int i = 0; i < translated_words.size(); i++) {
                    translations.append(translated_words[i]);
                    if (i != translated_words.size() - 1) {
                        translations.append(" / ");
                    }
                }
                print_frame(translations.c_str());
                break;
        }
    }

    void add_translation(string translation) {
        translated_words.push_back(translation);
    }

    bool operator==(Flashcard& fc) {
        return (original_word == fc.original_word);
    }
};