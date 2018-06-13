/* This is the console executable, that makes use of BullCow class
 This acts as the view in an MVC pattern, and is responsivle for all
 user interaction. For game logic see the FBullCowGame class.
 */

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//To make syntax easy to read
using FText = std::string;
using int32 = int;

//Function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //Instantiate a new game

//The main entry point for our application
int main()
{
    //While the response is yes, the user will continue to play
    bool bPlayAgain = false;
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } while (bPlayAgain);
    
    return 0;  //Exit the application
}

void PrintIntro()
{
    //Printing the intro of the game
    std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    return;
}

void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    //loop for the number of turns asking for guesses
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();
        
        //Submit valid guess to the game, and receive counts
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        //Print the number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    }
    
    PrintGameSummary();
    return;
}

//Loop continually until the user gives a valid guess
FText GetValidGuess()
{
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";
    do {
        //Get a guess from the user
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << "Try " << CurrentTry << ": Enter your guess: ";
        std::getline(std::cin, Guess);
        
        //Check the status and give feedback
        Status = BCGame.CheckGuessValidity(Guess);
        switch(Status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter a word in lower case letters\n";
                break;
            default:
                //assume the guess is valid
                break;
        }
    } while (Status != EGuessStatus::OK); //Keep looping till we get no errors
    return Guess;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again? (y/n) ";
    FText Response = "";
    getline(std::cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "WELL DONE - YOU WIN!\n";
    }
    else
    {
        std::cout << "Better luck next time!\n";
    }
}
