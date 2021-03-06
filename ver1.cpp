#include <iostream>
#include <time.h>
#include <string>
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

string WORD_LIST[] = {
"angle", "ant", "apple", "arch", "arm", "army",
"baby", "bag", "ball", "band", "basin", "basket", "bath", "bed", "bee", "bell", "berry",
"bird", "blade", "board", "boat", "bone", "book", "boot", "bottle", "box", "boy",
"brain", "brake", "branch", "brick", "bridge", "brush", "bucket", "bulb", "button",
"cake", "camera", "card", "cart", "carriage", "cat", "chain", "cheese", "chest",
"chin", "church", "circle", "clock", "cloud", "coat", "collar", "comb", "cord",
"cow", "cup", "curtain", "cushion",
"dog", "door", "drain", "drawer", "dress", "drop", "ear", "egg", "engine", "eye",
"face", "farm", "feather", "finger", "fish", "flag", "floor", "fly",
"foot", "fork", "fowl", "frame", "garden", "girl", "glove", "goat", "gun",
"hair", "hammer", "hand", "hat", "head", "heart", "hook", "horn", "horse",
"hospital", "house", "island", "jewel", "kettle", "key", "knee", "knife", "knot",
"leaf", "leg", "library", "line", "lip", "lock",
"map", "match", "monkey", "moon", "mouth", "muscle",
"nail", "neck", "needle", "nerve", "net", "nose", "nut",
"office", "orange", "oven", "parcel", "pen", "pencil", "picture", "pig", "pin",
"pipe", "plane", "plate", "plow", "pocket", "pot", "potato", "prison", "pump",
"rail", "rat", "receipt", "ring", "rod", "roof", "root",
"sail", "school", "scissors", "screw", "seed", "sheep", "shelf", "ship", "shirt",
"shoe", "skin", "skirt", "snake", "sock", "spade", "sponge", "spoon", "spring",
"square", "stamp", "star", "station", "stem", "stick", "stocking", "stomach",
"store", "street", "sun", "table", "tail", "thread", "throat", "thumb", "ticket",
"toe", "tongue", "tooth", "town", "train", "tray", "tree", "trousers", "umbrella",
"wall", "watch", "wheel", "whip", "whistle", "window", "wire", "wing", "worm",
};




void renderGame(string guessedWord, int badGuessCount){
    cout << FIGURE[badGuessCount];
    cout << guessedWord << endl;
}


//ver 1.0

string chooseWord(){
    srand(time(NULL));
    int index = rand() % 200;
    return WORD_LIST[index];
}

void update(string& guessedWord, string word, char guess){
    for (int i = 0; i < word.length(); i++){
        if (word[i] == guess) guessedWord[i] = guess;
    }
}

bool contains(char guess, string word){
    for (int i = 0; i < word.size(); i++){
        if (word[i] == guess) return true;
    }
    return false;
}


int main(){
    string word = chooseWord();
    string guessedWord = string(word.size(), '-');
    int badGuessCount = 0;
    do {
        renderGame(guessedWord, badGuessCount);
        char guess;
        cout << "Your guess: ";
        cin >> guess;
        if (contains(guess, word)) {update(guessedWord, word, guess);}
        else badGuessCount++;
    } while (badGuessCount < 7 && guessedWord != word);
    renderGame(guessedWord, badGuessCount);
    if (badGuessCount < 7) cout << "Congrats! You've won!" << endl;
    else cout << "Whoops! You lost! The correct word was '" << word << "'" << endl;
    

}

