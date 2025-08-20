# Flashcards

Learn vocabulary with Flashcards made in C++

# Description

Flashcards is a simple terminal app that allows you to practise vocabulary. The app asks you to enter translations for words stored in a file and checks whether they are correct. At the end, it shows the summary of the last learning session (guessed and missed words).

# Getting started
## For Linux
Installing make and g++
```
sudo apt update
sudo apt install build-essential
```

Running app
```
git clone https://github.com/PhilX15/CppFlashcards.git
cd CppFlashcards
make all
./main
```

# Usage
1. Add the words you want to learn to the words.txt file. **File format:**
```
original word - translation(s) (separated with commas)
original word - translation(s) (separated with commas)
...
```
**Exmaple:**
```
example ejemplo
file archivo,carpeta
```
2. Start the learning session in the app
3. The application will display words in the terminal. Type the correct translation. If there are multiple valid translations, you only need to provide **one** of them. 
4. At the end of the session, the app will display a summary

# To-Do List
- [ ] FEATURE: Vocabulary list editor in the app
- [ ] FEATURE: Setting the number of words in a single session
- [ ] FEATURE: Learned words sometimes appear among unknown words and can be marked as unknown again if the user enters an incorrect translation
- [ ] FIX: Translations containing spaces don't work correctly

