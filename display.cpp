#include <iostream>

using namespace std;

const string FIGURE[] = {
" ------------- \n"
" | \n"
" | \n"
" | \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" |           | \n"
" | \n"
" | \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" |           | \n"
" |           O \n"
" | \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" |           | \n"
" |           O \n"
" |           | \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" |           | \n"
" |           O \n"
" |          /| \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" |           | \n"
" |           O \n"
" |          /|\\ \n"
" | \n"
" | \n"
" ----- \n",
" ------------- \n"
" |           | \n"
" |           O \n"
" |          /|\\ \n"
" |          / \n"
" | \n"
" ----- \n",
" ------------- \n"
" |           | \n"
" |           O \n"
" |          /|\\ \n"
" |          / \\ \n"
" | \n"
" ----- \n",
};

void renderGame(string guessedWord, int badGuessCount){
    cout << FIGURE[badGuessCount];
    cout << guessedWord << endl;
}
