#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include "BCowGame.h"

BCowGame::BCowGame(){
    std::srand(time(NULL));
    CurrentTry = 0;
    GamesPlayed = 0;
    FillDictionary();
    SecretWord = GenerateWord();
    return;
}

BCowGame::~BCowGame(){}

bool BCowGame::IsIsogram(std::string toCheck) const{
    std::map<char, bool> LetterSeen;
    //for each loop over
    for(char Letter : toCheck){
        //if letter already seen return false else set that char's val in map to true
        if(LetterSeen[Letter]){
            return(false);
        }
        LetterSeen[Letter] = true;
    } 
    return (true);
}

bool BCowGame::IsProperLen(std::string toCheck) const{
    if(toCheck.length() == GetWordLength()){
        return(true);
    }
    return(false);
}

void BCowGame::FillDictionary(){
    //dictionary of words
    Dictionary.push_back("space");
    Dictionary.push_back("love");
    Dictionary.push_back("mind");
    Dictionary.push_back("heart");
    Dictionary.push_back("think");
    Dictionary.push_back("weight");
}

std::string BCowGame::GenerateWord(){
    //get random word out of dictionary
    int RandIndex = std::rand() % Dictionary.size();
    return(Dictionary[RandIndex]);
}

std::string BCowGame::GetGuess() const{
    std::cout << "Enter a guess\n>>> ";
    std::string guess;
    std::getline(std::cin, guess);
    std::cout << std::endl;
    //make guess all lower case
    std::transform(guess.begin(), guess.end(), guess.begin(), ::tolower);
    return(guess);
}

EError BCowGame::IsValid(std::string toCheck) const{
    if(!BCowGame::IsProperLen(toCheck)){
        return(EError::Wrong_Length);
    }
    else if(!BCowGame::IsIsogram(toCheck)){
        return(EError::Not_Isogram);
    }
    return(EError::OK);
}

std::string BCowGame::GetValidGuess() const{
    //get guess
    std::string TheGuess = GetGuess();
    //check if valid
    EError ValidGuess = IsValid(TheGuess);
    //if guess not valid keep trying till valid guess input
    while(ValidGuess != EError::OK){
        if(ValidGuess == EError::Wrong_Length){
            std::cout << "[!] Please enter a " << GetWordLength() << " letter word!\n" << std::endl;
        }
        else{
            std::cout << "[!] Guess is not an isogram please enter a valid entry!\n" << std::endl;
        }
        TheGuess = GetGuess();
        ValidGuess = IsValid(TheGuess);
    }
    return(TheGuess);
}

int BCowGame::GetGamesPlayed() const{
    return(GamesPlayed);
}

int BCowGame::GetWordLength() const{
    return(SecretWord.length());
}

void BCowGame::Reset(){
    CurrentTry = 0;
    GamesPlayed++;
    SecretWord = GenerateWord();
    return;
}

int BCowGame::TriesLeft() const{
    return(GetMaxTries() - CurrentTry);
}

int BCowGame::GetMaxTries() const{
    int WordLen = SecretWord.length();
    int UserTries;
    switch(WordLen){
        case 1 : case 2 : case 3:
            UserTries = 4;
            break;
        case 4:
            UserTries = 5;
            break;
        case 5:
            UserTries = 10;
            break;
        case 6:
            UserTries = 16;
            break;
        default:
            UserTries = 20;
    }
    return(UserTries);
}

BCowCount BCowGame::Compare(std::string toCompare){
    BCowCount TheCount;
    //loop over guess to see what are similar and get bulls and cows
    for(int i = 0; i < GetWordLength(); i++){
        //bulls
        if(SecretWord[i] == toCompare[i]){
            TheCount.Bulls++;
        }
        //cows
        else{
            //search word for this letter
            for(int j = 0; j < GetWordLength(); j++){
                if(SecretWord[j] == toCompare[i]){
                    TheCount.Cows++;
                }
            }
        }
    }
    CurrentTry++;
    return(TheCount);
}

void BCowGame::PrintOutcome(bool victory) const{
    if(victory){
        std::cout << "Congrats! You won!\n" << std::endl;
    }
    else{
        std::cout << "you lost! :(\n" << std::endl;
    }
    return;
}
