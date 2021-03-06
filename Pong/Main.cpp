#include "Libraries.h"
#include "Hephaestus.h"
#include "Logging.h"
#include "Menu.h"
using namespace std;
Hephaestus H;
GLFWwindow* W;
Menu M;
void Key_Call(GLFWwindow* Win, int key, int scancode, int action, int mods){
	H.Key_Call_Back(Win, key, scancode, action, mods);
	M.H_Menu.Key_Call_Back(Win, key, scancode, action, mods);
}
void Mouse_Call(GLFWwindow* Win, int button, int action, int mods){
	H.Mouse_Call_Back(Win, button, action, mods);
	M.H_Menu.Mouse_Call_Back(Win, button, action, mods);
	M.Mouse_Call(Win, button, action, mods);
}
void Window_Call(GLFWwindow* Win, int width, int hight){
	glfwSetWindowSize(Win, width, hight);
}
int main(){
	W = H.Full_Setup();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetKeyCallback(W, Key_Call);
	glfwSetMouseButtonCallback(W, Mouse_Call);
	glfwSetWindowSizeCallback(W, Window_Call);
	srand(time(NULL));
	/*>>>>>Place Before Start Code Here<<<<<*/
	M.Run_Menu_Program(H, W);
	H.Terminate_Log();
	return(0);
}