#include "Libraries.h"
#include "Logging.h"
#include "Hephaestus.h"
#include "Game.h"
using namespace std;
void Game::Run_Game_Program(int mode, Hephaestus H, GLFWwindow* W){
	int Collision = 0;
	H_Game = H;
	W_Game = W;
	H_Game.Clear_All_Layers();
	H_Game.Create_New_Layer();
	H_Game.Layers[1]->Initilize_Object(6);
	H_Game.Layers[1]->Physics_Objects[0]->New_Color_Physics_Object(4, 0.01, 0.01, 1.0, 1.0, 1.0, 1.0, 1);
	H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Physics_Object(-0.5, 0.0, 0.0);
	H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Reflection(105);
	Mode = mode;
	if (mode == 1){
		Classic();
		H_Game.Layers[1]->Physics_Objects[0]->Set_Collsion_Objects(H_Game.Layers[1]->Colored_Objects, 0, -1);
		H_Game.Layers[1]->Colored_Objects[0]->Set_Collision_Set(H_Game.Layers[1]->Physics_Objects, 0, -1);
		H_Game.Layers[1]->Colored_Objects[1]->Set_Collision_Set(H_Game.Layers[1]->Physics_Objects, 0, -1);
		H_Game.Layers[1]->Colored_Objects[0]->Set_Collision_Set(H_Game.Layers[1]->Colored_Objects, 2, 0);
		H_Game.Layers[1]->Colored_Objects[1]->Set_Collision_Set(H_Game.Layers[1]->Colored_Objects, 2, 1);
	}
	if (mode == 2){
		Timed();
	}
	if (mode == 3){
		Special();
	}
	if (mode == 4){
		Arena();
	}
	Game_Good = 1;
	
	
	
	while (Game_Good == 1){
		if (Mode == 1){
			if (glfwGetKey(W_Game, GLFW_KEY_W) || glfwGetKey(W_Game, GLFW_KEY_UP)){
				H_Game.Layers[1]->Colored_Objects[0]->Move_Object(0.0, Paddle_Speed, 0.0, 0, 0.1);
			}
			if (glfwGetKey(W_Game, GLFW_KEY_S) || glfwGetKey(W_Game, GLFW_KEY_DOWN)){
				H_Game.Layers[1]->Colored_Objects[0]->Move_Object(0.0, -Paddle_Speed, 0.0, 0, 0.1);
			}
		}

		Point = Check_For_Point();
		if (Point != 0){
			float x, y;
			if (Mode == 1){
				if (Point == 1){
					Score_1++;
					H_Game.Layers[0]->Button_Objects[0]->Edit_Button_Object(to_string(Score_1));
					H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Physics_Object(-0.5, 0.0, 0.0);
				}
				if (Point == 2){
					Score_2++;
					H_Game.Layers[0]->Button_Objects[1]->Edit_Button_Object(to_string(Score_2));
					H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Physics_Object(0.5, 0.0, 0.0);
				}
			}
			x = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2);
			y = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(3);
			H_Game.Layers[1]->Physics_Objects[0]->Physics->Translate_Object(-x, -y, 0.0);
		}
		Collision = H_Game.Layers[1]->Run_All_Physics();
		if (Collision == 1){
			float  Y_Paddle, Y_Ball, VY, VX;
			Collision = 0;
			Y_Ball = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(3);
			if (H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2) > 0){
				Y_Paddle = H_Game.Layers[1]->Colored_Objects[1]->Return_Float_Value(3);
			}
			if (H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2) < 0){
				Y_Paddle = H_Game.Layers[1]->Colored_Objects[0]->Return_Float_Value(3);
			}
			Y_Ball = Y_Ball - Y_Paddle;
			if (Y_Ball < 0){
				Y_Ball = Y_Ball * -1;
			}
			cout << Y_Ball;
			VX = H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(1);
			VY = H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(2);
			cout << ":" << VX << endl;
			VY = VY + (VX * Y_Ball) * 20;
			VX = VX - (VX * Y_Ball) * 10;
			H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Physics_Object(VX, VY, 0.0);
			cout << VY << "::" << VX << endl;
		}
		H_Game.Display_All_Layers();
		H_Game.Frame();
	}
}
int Game::Check_For_Point(){
	if (Mode == 1){
		if (H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2) < -1){
			return(2);
		}
		if (H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2) > 1){
			return(1);
		}
	}
	return(0);
}
int Game::Classic(){
	Paddle_Speed = 0.01;
	H_Game.Layers[0]->Initilize_Object(2);
	H_Game.Layers[0]->Textured_Objects[0]->New_Textured_Object("Textures/Game/Dividing Line", 4, 0.1, 1.3, 0);
	H_Game.Layers[0]->Initilize_Object(4);
	H_Game.Layers[0]->Button_Objects[0]->New_Button_Object(to_string(Score_1), "Textures/Buttons/Transparent", "Basic/White", 0.3, 0.3);
	H_Game.Layers[0]->Button_Objects[0]->Translate_Button_Object(-0.5, 0.7, 0.0);
	H_Game.Layers[0]->Initilize_Object(4);
	H_Game.Layers[0]->Button_Objects[1]->New_Button_Object(to_string(Score_2), "Textures/Buttons/Transparent", "Basic/White", 0.3, 0.3);
	H_Game.Layers[0]->Button_Objects[1]->Translate_Button_Object(0.5, 0.7, 0.0);
	H_Game.Layers[1]->Initilize_Object(1);
	H_Game.Layers[1]->Colored_Objects[0]->New_Colored_Object(4, 0.01, 0.1, 1.0, 1.0, 1.0, 1.0, 1);
	H_Game.Layers[1]->Colored_Objects[0]->Translate_Object(-0.9, 0.0, 0.0);
	H_Game.Layers[1]->Initilize_Object(1);
	H_Game.Layers[1]->Colored_Objects[1]->New_Colored_Object(4, 0.01, 0.1, 1.0, 1.0, 1.0, 1.0, 1);
	H_Game.Layers[1]->Colored_Objects[1]->Translate_Object(0.9, 0.0, 0.0);
	H_Game.Layers[1]->Initilize_Object(1);
	H_Game.Layers[1]->Colored_Objects[2]->New_Colored_Object(4, 2, 0.1, 1.0, 1.0, 1.0, 1.0, 1);
	H_Game.Layers[1]->Colored_Objects[2]->Translate_Object(0.0, 1.1, 0.0);
	H_Game.Layers[1]->Initilize_Object(1);
	H_Game.Layers[1]->Colored_Objects[3]->New_Colored_Object(4, 2, 0.1, 1.0, 1.0, 1.0, 1.0, 1);
	H_Game.Layers[1]->Colored_Objects[3]->Translate_Object(0.0, -1.1, 0.0);

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