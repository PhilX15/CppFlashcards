#ifndef FILE_READER_H
#define FILE_READER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <optional>
#include "doubly_linked_list.h"
#include "flashcard.h"

using namespace std;

optional<List<Flashcard>> file_read(ifstream &file);
void add_flashcard_to_list(List<Flashcard>& list, const Flashcard& new_flashcard);

#endif