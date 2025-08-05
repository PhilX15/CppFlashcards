#include "file_handler.h"

optional<List<Flashcard>> file_read(ifstream &file) {
    if (!file.is_open()) {
        return nullopt;
    }

    List<Flashcard> flashcards;

    string line;
    while (getline(file, line)) {
        std::stringstream line_stream(line);
        string original;
        if (!getline(line_stream, original, ' ')) {
            return nullopt;
        }

        uint translation_counter = 0;
        string translation;
        while (getline(line_stream, translation, ',')) {
            translation_counter++;
            add_flashcard_to_list(flashcards, Flashcard(original, translation));
        }

        if (!translation_counter) {
            return nullopt;
        }
    }

    return flashcards;
}

void add_flashcard_to_list(List<Flashcard>& list, const Flashcard& new_flashcard) {
    Node<Flashcard>* existing_node = list.find(new_flashcard);
    if (existing_node != nullptr) {
        for (const string& translation : new_flashcard.translated_words) {
            auto& existing_translations = existing_node->data.translated_words;
            if (std::find(existing_translations.begin(), existing_translations.end(), translation) == existing_translations.end()) {
                existing_node->data.add_translation(translation);
            }
        }
    } else {
        list.push_back(new_flashcard);
    }
}