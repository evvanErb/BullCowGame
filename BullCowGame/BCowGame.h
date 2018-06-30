#pragma once
#include <string>
#include <vector>

//struct to see how many bulls and cows in a guess
struct BCowCount{
    int Bulls = 0;
    int Cows = 0;
};

//enum for errors for invalid guesses
enum class EError{
    OK,
    Not_Isogram,
    Wrong_Length
};

//class to keep track of the game being played
class BCowGame{
    private:
        int GamesPlayed;
        int CurrentTry;
        std::vector<std::string> Dictionary;
        std::string SecretWord;
        //check if a string is isogram
        bool IsIsogram(std::string toCheck) const;
        //check if guess is proper length
        bool IsProperLen(std::string toCheck) const;
        //initialize the dictionary of isograms
        void FillDictionary();
        //generate a new word for this iteration
        std::string GenerateWord();
        //get a guess
        std::string GetGuess() const;
        //check if guess is valid
        EError IsValid(std::string toCheck) const;

    public:
        //constructor
        BCowGame();
        //destructor
        ~BCowGame();
        //get a valid guess
        std::string GetValidGuess() const;
        //get total games played
        int GetGamesPlayed() const;
        //get the length of the secret word
        int GetWordLength() const;
        //reset the game
        void Reset();
        //how many tries the user has left
        int TriesLeft() const;
        //how many tries the user has total relative to secret word length
        int GetMaxTries() const;
        //check if guess correct and get counts of bulls and cows in guess
        BCowCount Compare(std::string toCompare);
        //print victory or defeat
        void PrintOutcome(bool victory) const;
};
