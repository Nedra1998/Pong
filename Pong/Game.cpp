#include "Libraries.h"
#include "Logging.h"
#include "Hephaestus.h"
#include "Game.h"
using namespace std;
void Game::Run_Game_Program(int Mode){
	if (Mode == 1){
		Classic();
	}
	if (Mode == 2){
		Timed();
	}
	if (Mode == 3){
		Special();
	}
	if (Mode == 4){
		Arena();
	}
}
int Game::Classic(){
	cout << "A";
	return(0);
}
int Game::Timed(){
	cout << "B";
	return(0);
}
int Game::Special(){
	cout << "C";
	return(0);
}
int Game::Arena(){
	cout << "D";
	return(0);
}