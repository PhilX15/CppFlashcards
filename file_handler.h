#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <optional>
#include "doubly_linked_list.h"
#include "flashcard.h"

using namespace std;

/*
FILE FORMAT: <original_word> <translations>
*/

optional<List<Flashcard>> file_read(ifstream &file);
void file_write(ifstream &file, const List<Flashcard>& list);

void add_flashcard_to_list(List<Flashcard>& list, const Flashcard& new_flashcard);

#endif