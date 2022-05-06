#pragma once

#ifndef CHOOSEWORD_H_
#define CHOOSEWORD_H_

#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int chooseDifficulty();
void chooseWord(int level, string &word, string &meaning);

#endif /* CHOOSEWORD_H_ */