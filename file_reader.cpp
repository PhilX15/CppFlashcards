#include "file_reader.h"

ifstream file_open(const char *filename) {
    ifstream f(filename);

    if (!f.is_open()) {
        cerr << "Couldn't open file";
        return f;
    }

    return f;
}