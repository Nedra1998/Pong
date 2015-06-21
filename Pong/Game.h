#include "Libraries.h"
using namespace std;
class Game{
private:
	int Classic();
	int Timed();
	int Special();
	int Arena();
	int Check_For_Point();
	int Mode;
	int Game_Good;
	int Score_1, Score_2, Point;
	float Paddle_Speed;
public:
	Hephaestus H_Game;
	GLFWwindow* W_Game;
	void Run_Game_Program(int mode, Hephaestus H, GLFWwindow* W);
};