/* cpp file which implements the functions/code
 */

#include "FBullCowGame.h"
#include <map>

//To make syntax easy to read
#define TMap std::map
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } //default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
    TMap<int32, int32> WordLengthToMaxTries { {3,5}, {4,5}, {5,5}, {6,5}};
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess)) //If the guess is not an isogram
    {
        return EGuessStatus::Not_Isogram;
    }
    else if(!IsLowerCase(Guess)) //If the guess isn't all lowercase
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if(Guess.length() != GetHiddenWordLength()) //If the guess length is wrong
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    }
}

//Receives a VALID guess, increments turn, and returns the counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    //increment the turn number
    MyCurrentTry++;
    
    //setup a return variable
    FBullCowCount BullCowCount;
    
    int32 WordLength = MyHiddenWord.length();
    //loop through all letters in the guess
    for (int32 i = 0; i < WordLength; i++) {
        //compare letters against the hidden word
        for (int32 j = 0; j < WordLength; j++) {
            //if they match then
            if (Guess[i] == MyHiddenWord[j]) {
                //if they're in the same space
                if (i == j) {
                    BullCowCount.Bulls++;
                } else
                {
                    BullCowCount.Cows++;
                }
               
            }
        }
    }
    if (BullCowCount.Bulls == WordLength) {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram (FString Word) const
{
    //treat 0 and 1 letter words as isograms
    if (Word.length() <= 1) { return true; }
    
    TMap<char, bool> LetterSeen; //setup our map
    for (auto Letter : Word)     //for all letters of the word
    {
        Letter = tolower(Letter); //handle mixed case
        if (LetterSeen[Letter]) {
            return false;  //we do NOT have an isogram
        } else {
            LetterSeen[Letter] = true;
        }
    }
    return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
    for (auto Letter : Word)
    {
        if (!islower(Letter)) //If not a lower case letter
        {
            return false;
        }
    } return true;
}
