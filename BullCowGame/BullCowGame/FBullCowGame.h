/* The game logic (no view code or direct user interaction)
 The game is a simple guess the word game
 */

#pragma once
#include <string>

//To make syntax easy to read
using FString = std::string;
using int32 = int;

//All values initialized to 0
struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
    
};

enum class EGuessStatus {
  Invalid_Status,
  OK,
  Not_Isogram,
  Wrong_Length,
  Not_Lowercase
};


class FBullCowGame {
public:
    FBullCowGame(); //Constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset();
    //Counts Bulls and Cows, and increases try # assuming valid guess
    FBullCowCount SubmitValidGuess(FString);
    
private:
    //See constructor for initialization values
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
    
    bool IsIsogram(FString) const;
    bool IsLowerCase(FString) const;
};

