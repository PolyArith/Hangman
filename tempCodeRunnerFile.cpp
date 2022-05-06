#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include "chooseWord.cpp"
#include "display.cpp"
#include "timer.cpp"
#include "processGuess.cpp"
using namespace std;


//all fixes to the gameplay will now be moved to play function

void pickMaxScore(const int& level, long long& maxScorePerPlay){
    switch(level) {
        case 1: 
            maxScorePerPlay = 1000;
            break;
        case 2:
            maxScorePerPlay = 2000;
            break;
        case 3:
            maxScorePerPlay = 5000;
            break;
    }
}

void loserScore(string guessedWord, long long& maxScorePerPlay){
    int wordLength = guessedWord.size();
    int correctGuesses = 0;
    for (int i = 0; i < wordLength; i++){
        if (guessedWord[i] != '-') correctGuesses++;
    }
    maxScorePerPlay = maxScorePerPlay * correctGuesses / (wordLength *2);
}


//notice beforehand all the options and help that can be used
void introduction();

void play(long long &score){
    // start play, choose difficulty
    int level = chooseDifficulty();
    long long maxScorePerPlay;
    // use 1 - 2 - 5 like money
    pickMaxScore(level, maxScorePerPlay);
    cout << "Your maximum score this play is: " << maxScorePerPlay << ", doubled if guessed whole." << endl;
    helpInfo();
    // pick word and its meaning
    string word;
    string meaning;
    chooseWord(level, word, meaning);
    //set up guess
    string guessedWord = string(word.size(), '-');
    int badGuessCount = 0;
    //ifCorrect used to check user's whole word guess
    bool ifCorrect = false;
    //start the timer, end will be defined by timer.cpp
    chrono::time_point<chrono::system_clock> start;
    start = chrono::system_clock::now();
    bool stillPlaying;
    // refresh help function
    meaningUsed = false;
    nearMissUsed = false;
    popLetterUsed = false;
    do {
        renderGame(guessedWord, badGuessCount);
        string guess;
        inviteGuess(guess);
        processGuess(guess, word, meaning, guessedWord, badGuessCount, ifCorrect);
        stillPlaying = checkTime(start, maxScorePerPlay);
    } while (badGuessCount < 7 && guessedWord != word && !ifCorrect && stillPlaying); // check when to stop
    // increase points twice if guessed whole
    if (ifCorrect) maxScorePerPlay = maxScorePerPlay * 2;
    double elapsed_seconds;
    updateScoreByTime(start, maxScorePerPlay, elapsed_seconds);
    updateScoreByHelp(maxScorePerPlay);
    renderGame(guessedWord, badGuessCount);
    //check if player won (seeing if time had run out and if the guess is legit)
    if (badGuessCount < 7 && stillPlaying) {
        cout << "Congrats! You've won!" << endl;
        cout << "The correct word was '" << word << "'" << endl;
        cout << "It took you: " << elapsed_seconds << "s." << endl;
        score += maxScorePerPlay;
    }
    else {
        cout << "Whoops! You lost! The correct word was '" << word << "'" << endl;
        loserScore(guessedWord, maxScorePerPlay);
    }
    //keeping records
    cout << "Your total score is: " << score << endl;
    
}


void gameplayRepeat(){
    bool play_again = true;
    long long score = 0;
    while (play_again){
        play(score);
        char ifPlayAgain;
        
        ifPlayAgain = '1';
        while (ifPlayAgain != 'y' && ifPlayAgain != 'n'){
            cout << "Would you like to play again? (y/n)" << endl;
            cin >> ifPlayAgain;
            if (ifPlayAgain == 'y'){
                continue;
            } else if (ifPlayAgain == 'n') play_again = false;
        }
    }
    cout << "Hope you enjoyed your time!" << endl;
    return;
}


//added replay feature

int main(){
    gameplayRepeat();
    return 0;

}
