#include "Libraries.h"
using namespace std;
class Menu{
private:
	bool Good = true;
	bool Close();
	void Main_Menu();
	void Settings_Menu();
	void Single_Player_Menu_1();
	void Single_Player_Menu_2();
	void Multi_Player_Menu_1();
	void Multi_Player_Menu_2();
	int Mode, Difficulty, Control;
	bool Mouse;
public:
	Hephaestus H_Menu;
	GLFWwindow* W_Menu;
	void Run_Menu_Program(Hephaestus H, GLFWwindow* W);
	void Mouse_Call(GLFWwindow* Win, int button, int action, int mods);
};