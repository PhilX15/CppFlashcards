CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20
OBJ = main.o print_utils.o file_handler.o input_utils.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ)

main.o: main.cpp flashcard.h session.h file_handler.h input_utils.h
	$(CXX) $(CXXFLAGS) -c main.cpp

print_utils.o: print_utils.cpp print_utils.h
	$(CXX) $(CXXFLAGS) -c print_utils.cpp

file_handler.o: file_handler.cpp file_handler.h flashcard.h doubly_linked_list.h
	$(CXX) $(CXXFLAGS) -c file_handler.cpp

inpout_utils.o: input_utils.cpp input_utils.h
	$(CXX) $(CXXFLAGS) -c input_utils.cpp

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean