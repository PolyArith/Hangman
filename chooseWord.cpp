#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//let player choose their difficulty
int chooseDifficulty(){
    int level = -1;
    // only take in acceptable input
    while (level < 1 || level > 3){
        cout << "Choose your level of difficulty (1-3):" << endl;
        cin >> level;
    }
    return level;
}

//1: asia, 2: fruits, 3: jobs
//4 - 5: easy, 6 - 7: medium, >= 8: hard


void chooseThemedWord(string &word, string &meaning, int theme){
    vector<string> wordList;
    vector<string> wordMeaningList;
    string fileName;
    //choose lib by theme
    if (theme == 1) {
        fileName = "asia.txt";
    } else if (theme == 2){
        fileName = "fruits.txt";
    } else fileName = "jobs.txt";
    //store word list
    ifstream inWord(fileName);
    if (inWord.is_open()){
        string s;
        while (getline(inWord, s)) wordList.push_back(s);
        inWord.close();
    }
    
    word = "";
    //save the index to find later in meaning lib
    int savedIndex;
    if (wordList.size() > 0){
        
        srand(time(NULL));
        int randomIndex = rand() % wordList.size();
        word = wordList[randomIndex];
        savedIndex = randomIndex;
        
        
    }
    
    if (theme == 1){
        meaning = "Not for this one!";
        return;
    } else if (theme == 2) {
        fileName = "fruitsMeaning.txt";
    } else {
        fileName = "jobsMeaning.txt";
    }
    //taking in meaning lib
    ifstream inMeaning(fileName);
    if (inMeaning.is_open()){
        string s;
        while (getline(inMeaning, s)) wordMeaningList.push_back(s);
        inMeaning.close();
    }
    meaning = wordMeaningList[savedIndex];

}

void chooseWord(int level, string &word, string &meaning){
    vector<string> wordList;
    vector<string> wordMeaningList;
    string fileName;
    if (level == 1){
        fileName = "easyWordList.txt";
    } else if (level == 2){
        fileName = "mediumWordList.txt";
    } else fileName = "hardWordList.txt";
    ifstream inWord(fileName);
    if (inWord.is_open()){
        string s;
        while (getline(inWord, s)){
           wordList.push_back(s);
        }
        inWord.close();
    }
    if (level == 1){
        fileName = "easyMeaning.txt";
    } else if (level == 2){
        fileName = "mediumMeaning.txt";
    } else fileName = "hardMeaning.txt";
    ifstream inMeaning(fileName);
    if (inMeaning.is_open()){
        string s;
        while (getline(inMeaning, s)){
           wordMeaningList.push_back(s);
        }
        inMeaning.close();
    }
    //level is defined by word length, <= 4 is easy, 5-6 is medium, >6 is hard
    if (wordList.size() > 0){
        srand(time(NULL));
        int randomIndex = rand() % wordList.size();
        word = wordList[randomIndex];
        meaning = wordMeaningList[randomIndex];
        //int randomIndex = rand() % wordList.size();
    }
}
