#include <time.h>
#include <chrono>
using namespace std;

bool checkTime(chrono::time_point<chrono::system_clock> start, long long maxScorePerPlay){
    double maxTime = maxScorePerPlay / 10;
    chrono::time_point<chrono::system_clock> tempEnd = chrono::system_clock::now();
    chrono::duration<double> secondsPassed = tempEnd - start;
    if (secondsPassed.count() > maxTime) return false;
    return true;
}

void updateScoreByTime(chrono::time_point<chrono::system_clock> start, long long& maxScorePerPlay, double& elapsed_seconds){
    chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
    chrono::duration<double> elapsed = end - start;
    if (elapsed.count() * 10 > maxScorePerPlay){
        maxScorePerPlay = 0;
    } else maxScorePerPlay -= elapsed.count() * 10;
    elapsed_seconds = elapsed.count();
}