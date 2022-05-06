#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void helpInfo(){
    cout << "Enter number 0-3 if you want its Vietnamese meaning, lose 10 percent of points." << endl;
    cout << "Enter number 4-6 if you want training wheels - taking one near miss character, lose 10 percent of points" << endl;
    cout << "Enter number 7-9 if you want the first unsolved letter off, lose 10 percent of points." << endl;
}

void inviteGuess(string& guess){
    cout << "Your guess: ";
    cin >> ws;
    getline(cin, guess);
}

bool meaningUsed = false;
bool nearMissUsed = false;
bool popLetterUsed = false;

void rejectOffer(){
    cout << "Sorry, you've already used this!" << endl;
}

void nearMiss(string word, string& guessedWord){
    if (nearMissUsed) {
        rejectOffer();
        return;
    }
    nearMissUsed = true;
    string guess;
    inviteGuess(guess);
    for (int i = 0; i < guessedWord.size(); i++){
        int distance = abs(guess[0] - word[i]);
        if (distance <= 2) {
            guessedWord[i] = word[i];
        }
        
    }
}

void popLetter(string word, string& guessedWord){
    if (popLetterUsed){
        rejectOffer();
        return;
    }
    popLetterUsed = true;
    for (int i = 0; i < guessedWord.size(); i++){
        if (guessedWord[i] == '-') {
            guessedWord[i] = word[i];
            return;
        }
    }
}

void giveMeaning(string meaning){
    if (meaningUsed){
        rejectOffer();
        return;
    }
    meaningUsed = true;
    cout << meaning << endl;
}

void help(string &guess, string word, string meaning, string& guessedWord){
    char c = guess[0];
    // vietnamese meaning
    if (guess[0] >= '0' && guess[0] <= '3'){
        giveMeaning(meaning);
    } //near miss
    else if (guess[0] >= '4' && guess[0] <= '6'){
        nearMiss(word, guessedWord);
    } else {
        popLetter(word, guessedWord);
    }
}



bool contains(char guess, string word){
    for (int i = 0; i < word.size(); i++){
        if (word[i] == guess) return true;
    }
    return false;
}

void update(string& guessedWord, string word, char guess){
    for (int i = 0; i < word.length(); i++){
        if (word[i] == guess) guessedWord[i] = guess;
    }
}


bool guessTheWordWhole(string word, string guess){
    if (word == guess) return true;
    return false;
}

void processGuess(string guess, string word, string meaning, string& guessedWord, int& badGuessCount, bool& ifCorrect){
    if (guess.size() > 1) ifCorrect = guessTheWordWhole(word, guess);
    else if (guess[0] >= '0' && guess[0] <= '9') {
        help(guess, word, meaning, guessedWord);
    }
    if (guess.size() > 1) ifCorrect = guessTheWordWhole(word, guess);
    else if (contains(guess[0], word)) {update(guessedWord, word, guess[0]);}
    else badGuessCount++;
}

void updateScoreByHelp(long long &maxScorePerPlay){
    int helpCount = 0;
    if (meaningUsed) helpCount += 1;
    if (popLetterUsed) helpCount += 1;
    if (nearMissUsed) helpCount += 1;
    maxScorePerPlay -= maxScorePerPlay * helpCount / 10;
}

void refreshTool(bool& meaningUsed, bool& nearMissUsed, bool& popLetterUsed){
    meaningUsed = false;
    nearMissUsed = false;
    popLetterUsed = false;
}