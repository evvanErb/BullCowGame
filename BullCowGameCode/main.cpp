#include <iostream>
#include <string>
#include "BCowGame.h"
#include "main.h"

//global game object
BCowGame TheGame;

int main(){
    bool running = true;

    do{
        //reset the game
        TheGame.Reset();
        //introduce the game
        PrintIntro();
        //launch an iteration of the game
        PlayGame();
        //see if user wants to play again
        running = KeepPlaying();
    }while(running);

    return 0;
}

void PrintIntro(){
    //welcome player
    std::cout << "Welcome to the Bulls and Cows, a fun word game!" << std::endl;
    std::cout << "Can you guess the " << TheGame.GetWordLength() << " letter isogram I\'m thingking of?\n" << std::endl;
    return;
}

void PlayGame(){
    std::string TheGuess;
    BCowCount BullsCows;
    //run 10 guesses
    for(int i = 0; i < TheGame.GetMaxTries(); i++){
        //wait to get valid guess
        TheGuess = TheGame.GetValidGuess();
        //see bulls and cows
        BullsCows = TheGame.Compare(TheGuess);
        std::cout << "You have " << BullsCows.Bulls << " Bulls and " << BullsCows.Cows << " Cows" << std::endl;
        //if all letters correct tell user they won and return
        if(BullsCows.Bulls == TheGame.GetWordLength()){
            TheGame.PrintOutcome(true);
            return;
        }
        std::cout << "You have " << TheGame.TriesLeft() << " tries left!\n" << std::endl;
    }
    TheGame.PrintOutcome(false);
    return;
}

bool KeepPlaying(){
    //ask player if they want to play again and get response
    std::cout << "Would you like to play again?\n>>> ";
    std::string check;
    std::getline(std::cin, check);
    std::cout << std::endl;
    //if yes return true else return false
    return(check == "y" || check == "yes");
}
