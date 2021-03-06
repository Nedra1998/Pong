#include "Libraries.h"
using namespace std;
class Game{
private:
	void Pre_Game();
	void Every_Turn();
	void Score();

	int Classic();
	int Timed();
	int PowerUP();
	int Arena();
	int OneVAll();
	int Check_For_Point();
	void End_Screen();
	bool Close();
	int Mode, Difficulty;
	int Game_Good;
	int Score_1, Score_2, Score_3, Score_4, Point;
	int Minutes, Seconds;
	int Collision = 0, Total = 0;
	int Last_Hit;
	time_t Start, End;
	struct Power_Up
	{
		bool Active;
		bool Left;
		int Life;
		int Power;
		int Index;
	};
	vector<Power_Up> Pick_Ups;
	vector<Power_Up> Power_Ups;
	bool BL, BS, BP, PL, PS, PP;
	float Paddle_Speed, Paddle_Speed_2, Ball_Speed;
	float Base_1, Base_2;
public:
	Hephaestus H_Game;
	GLFWwindow* W_Game;
	void Run_Game_Program_Single_Player(int mode, Hephaestus H, GLFWwindow* W, bool Mouse, int difficulty);
	void Run_Game_Program_Multi_Player(int mode, Hephaestus H, GLFWwindow* W);
};