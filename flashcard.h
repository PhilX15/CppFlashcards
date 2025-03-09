#include <string>

using namespace std;

class Flashcard {
private:
    string original_word;
    string translated_word;
public:
    Flashcard(string original, string translated) : original_word(original), translated_word(translated) {}
};