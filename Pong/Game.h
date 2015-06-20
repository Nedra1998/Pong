#include "Libraries.h"
using namespace std;
class Game{
private:
	int Classic();
	int Timed();
	int Special();
	int Arena();
public:
	void Run_Game_Program(int Mode);
};