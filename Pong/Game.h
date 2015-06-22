#include "Libraries.h"
using namespace std;
class Game{
private:
	int Classic();
	int Timed();
	int Special();
	int Arena();
	int Check_For_Point();
	void End_Screen();
	int Mode;
	int Game_Good;
	int Score_1, Score_2, Point;
	int Minutes, Seconds;
	float Paddle_Speed, Paddle_Speed_2, Ball_Speed;
	float Base_1, Base_2;
public:
	Hephaestus H_Game;
	GLFWwindow* W_Game;
	void Run_Game_Program(int mode, Hephaestus H, GLFWwindow* W, bool Mouse, int Difficulty);
};