#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
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

void ifThemed(bool& themedGameplay, int& theme){
    cout << "Would you like your gameplay to be themed as: \n"
    << "(0) Nothing. \n"
    << "(1) Asian countries. \n"
    << "(2) Fruits. \n"
    << "(3) Jobs. \n";
    cin >> theme;
    if (theme != 0) themedGameplay = true;

}


//notice beforehand all the options and help that can be used
void introduction();

void play(long long &score){
    //pick its theme, if needed
    long long maxScorePerPlay;
    bool themedGameplay = false;
    int theme;
    int level;
    ifThemed(themedGameplay, theme);
    // start play, choose difficulty
    if (!themedGameplay){
        level = chooseDifficulty();
        // use 1 - 2 - 5 like money
        pickMaxScore(level, maxScorePerPlay);
        
    }
    helpInfo();
    
    
    // pick word and its meaning
    string word;
    string meaning;
    if (themedGameplay){
        chooseThemedWord(word, meaning, theme);
    } else chooseWord(level, word, meaning);
    if (themedGameplay) maxScorePerPlay = 750 * word.length();
    cout << "Your maximum score this play is: " << maxScorePerPlay << ", doubled if guessed whole." << endl;
    //set up guess
    string guessedWord = string(word.size(), '-');
    for (int i = 0; i < word.size(); i++){
        if (word[i] == ' ') guessedWord[i] = ' ';
    }
    int badGuessCount = 0;
    //ifCorrect used to check user's whole word guess
    bool ifCorrect = false;
    //start the timer, end will be defined by timer.cpp
    chrono::time_point<chrono::system_clock> start;
    start = chrono::system_clock::now();
    bool stillPlaying;
    // refresh help function
    refreshTool(meaningUsed, nearMissUsed, popLetterUsed);
    // let the games begin
    do {
        //start with display
        renderGame(guessedWord, badGuessCount);
        //take in and process player's guess
        string guess;
        inviteGuess(guess);
        processGuess(guess, word, meaning, guessedWord, badGuessCount, ifCorrect);
        //see if time has run out
        stillPlaying = checkTime(start, maxScorePerPlay);
    } while (badGuessCount < 7 && guessedWord != word && !ifCorrect && stillPlaying); // check when to stop
    // increase points twice if guessed whole
    if (ifCorrect) maxScorePerPlay = maxScorePerPlay * 2;
    //updateScore
    double elapsed_seconds;
    updateScoreByTime(start, maxScorePerPlay, elapsed_seconds);
    updateScoreByHelp(maxScorePerPlay);
    //the appearence
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
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;
    sleep_until(system_clock::now() + seconds(10));
}


//added replay feature

int main(){
    gameplayRepeat();
    return 0;

}
