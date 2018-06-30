//main manages game and calls / uses BullCow class object for game logic

#include <string>

//introduce player to game
void PrintIntro();
//run iteration of game
void PlayGame();
//check if player wants to keep playing
bool KeepPlaying();
//get a valid guess from player
std::string GetGuess();
