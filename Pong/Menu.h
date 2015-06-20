#include "Libraries.h"
using namespace std;
class Menu{
private:
	bool Good = true;
	bool Close();
	void Main_Menu();
	void Settings_Menu();
	void Single_Player_Menu();
	void Multi_Player_Menu_1();
	void Multi_Player_Menu_2();
public:
	Hephaestus H_Menu;
	GLFWwindow* W_Menu;
	void Run_Menu_Program(Hephaestus H, GLFWwindow* W);
};