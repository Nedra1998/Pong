#include "Libraries.h"
#include "Logging.h"
#include "Hephaestus.h"
#include "Game.h"
using namespace std;
void Game::Run_Game_Program(int mode, Hephaestus H, GLFWwindow* W, bool Mouse, int difficulty){
	H_Game = H;
	W_Game = W;
	H_Game.Clear_All_Layers();
	H_Game.Create_New_Layer();
	H_Game.Layers[1]->Initilize_Object(6);
	H_Game.Layers[1]->Physics_Objects[0]->New_Color_Physics_Object(4, 0.01, 0.01, 1.0, 1.0, 1.0, 1.0, 1);
	H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Reflection(105);
	Mode = mode;
	Difficulty = difficulty;
	Pre_Game();
	while (Game_Good == 0){
		Every_Turn();
		if (Mouse == false){
			if (glfwGetKey(W_Game, GLFW_KEY_W) || glfwGetKey(W_Game, GLFW_KEY_UP)){
				H_Game.Layers[1]->Colored_Objects[0]->Move_Object(0.0, Paddle_Speed, 0.0, 0, 0.1);
			}
			if (glfwGetKey(W_Game, GLFW_KEY_S) || glfwGetKey(W_Game, GLFW_KEY_DOWN)){
				H_Game.Layers[1]->Colored_Objects[0]->Move_Object(0.0, -Paddle_Speed, 0.0, 0, 0.1);
			}
		}
		else if (Mouse == true){
			double XP, YP;
			float Y, Distance;
			int YR, XR;
			glfwGetCursorPos(W_Game, &XP, &YP);
			Y = H_Game.Layers[1]->Colored_Objects[0]->Return_Float_Value(3);
			H_Game.Win.Window_Res(XR, YR);
			if (Y > (((YP / (YR / 2)) - 1) * -1) + 0.005){
				Distance = (Y - (((YP / (YR / 2)) - 1) * -1));
				if (Distance < Paddle_Speed){
					H_Game.Layers[1]->Colored_Objects[0]->Move_Object(0.0, -Distance, 0.0, 0, 0.1);
				}
				else{
					H_Game.Layers[1]->Colored_Objects[0]->Move_Object(0.0, -Paddle_Speed, 0.0, 0, 0.1);
				}
			}
			else if (Y < (((YP / (YR / 2)) - 1) * -1) - 0.005){
				Distance = Y - (((YP / (YR / 2)) - 1) * -1);
				if (-Distance < Paddle_Speed){
					H_Game.Layers[1]->Colored_Objects[0]->Move_Object(0.0, -Distance, 0.0, 0, 0.1);
				}
				else{
					H_Game.Layers[1]->Colored_Objects[0]->Move_Object(0.0, Paddle_Speed, 0.0, 0, 0.1);
				}
			}
		}
		float paddle, ball, Distance;
		paddle = H_Game.Layers[1]->Colored_Objects[1]->Return_Float_Value(3);
		ball = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(3);
		if (paddle > ball + 0.005){
			Distance = (paddle - ball);
			if (Distance < Paddle_Speed_2){
				H_Game.Layers[1]->Colored_Objects[1]->Move_Object(0.0, -Distance, 0.0, 0, 0.1);
			}
			else{
				H_Game.Layers[1]->Colored_Objects[1]->Move_Object(0.0, -Paddle_Speed_2, 0.0, 0, 0.1);
			}
		}
		else if (paddle < ball - 0.005){
			Distance = (paddle - ball);
			if (-Distance < Paddle_Speed_2){
				H_Game.Layers[1]->Colored_Objects[1]->Move_Object(0.0, -Distance, 0.0, 0, 0.1);
			}
			else{
				H_Game.Layers[1]->Colored_Objects[1]->Move_Object(0.0, Paddle_Speed_2, 0.0, 0, 0.1);
			}
		}

		Score();
		Collision = H_Game.Layers[1]->Run_All_Physics();
		if (Collision == 1){
			Paddle_Speed = Paddle_Speed + (Paddle_Speed * .05);
			Paddle_Speed_2 = Paddle_Speed_2 + (Paddle_Speed_2 * .05);
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
			VX = H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(1);
			VY = H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(2);
			VY = VY + (VX * Y_Ball) * 10;
			H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Physics_Object(VX, VY, 0.0);
		}


		H_Game.Display_All_Layers();
		H_Game.Frame();
	}
	End_Screen();
}
void Game::Pre_Game(){
	if (Mode == 1){
		Classic();
		H_Game.Layers[1]->Physics_Objects[0]->Set_Collsion_Objects(H_Game.Layers[1]->Colored_Objects, 0, -1);
		H_Game.Layers[1]->Colored_Objects[0]->Set_Collision_Set(H_Game.Layers[1]->Physics_Objects, 0, -1);
		H_Game.Layers[1]->Colored_Objects[1]->Set_Collision_Set(H_Game.Layers[1]->Physics_Objects, 0, -1);
		H_Game.Layers[1]->Colored_Objects[0]->Set_Collision_Set(H_Game.Layers[1]->Colored_Objects, 2, 0);
		H_Game.Layers[1]->Colored_Objects[1]->Set_Collision_Set(H_Game.Layers[1]->Colored_Objects, 2, 1);
		if (Difficulty == 0){
			Paddle_Speed_2 = Paddle_Speed_2 * 2;
			Ball_Speed = Ball_Speed * 2;
		}
		if (Difficulty == 1){
			Paddle_Speed_2 = Paddle_Speed_2 * 2;
		}
		if (Difficulty == 3){
			Paddle_Speed_2 = Paddle_Speed_2 / 2;
		}
	}
	if (Mode == 2){
		Timed();
		H_Game.Layers[1]->Physics_Objects[0]->Set_Collsion_Objects(H_Game.Layers[1]->Colored_Objects, 0, -1);
		H_Game.Layers[1]->Colored_Objects[0]->Set_Collision_Set(H_Game.Layers[1]->Physics_Objects, 0, -1);
		H_Game.Layers[1]->Colored_Objects[1]->Set_Collision_Set(H_Game.Layers[1]->Physics_Objects, 0, -1);
		H_Game.Layers[1]->Colored_Objects[0]->Set_Collision_Set(H_Game.Layers[1]->Colored_Objects, 2, 0);
		H_Game.Layers[1]->Colored_Objects[1]->Set_Collision_Set(H_Game.Layers[1]->Colored_Objects, 2, 1);
		if (Difficulty == 0){
			H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Reflection(125);
			Paddle_Speed_2 = Paddle_Speed_2 * 2;
			Ball_Speed = Ball_Speed * 2;
		}
		if (Difficulty == 1){
			H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Reflection(115);
			Paddle_Speed_2 = Paddle_Speed_2 * 2;
		}
		if (Difficulty == 3){
			H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Reflection(100);
			Paddle_Speed_2 = Paddle_Speed_2 / 2;
		}
		time(&Start);
	}
	if (Mode == 3){
		Special();
		H_Game.Layers[1]->Physics_Objects[0]->Set_Collsion_Objects(H_Game.Layers[1]->Colored_Objects, 0, -1);
		H_Game.Layers[1]->Colored_Objects[0]->Set_Collision_Set(H_Game.Layers[1]->Physics_Objects, 0, -1);
		H_Game.Layers[1]->Colored_Objects[1]->Set_Collision_Set(H_Game.Layers[1]->Physics_Objects, 0, -1);
		H_Game.Layers[1]->Colored_Objects[0]->Set_Collision_Set(H_Game.Layers[1]->Colored_Objects, 2, 0);
		H_Game.Layers[1]->Colored_Objects[1]->Set_Collision_Set(H_Game.Layers[1]->Colored_Objects, 2, 1);
		if (Difficulty == 0){
			Paddle_Speed_2 = Paddle_Speed_2 * 2;
			Ball_Speed = Ball_Speed * 2;
		}
		if (Difficulty == 1){
			Paddle_Speed_2 = Paddle_Speed_2 * 2;
		}
		if (Difficulty == 3){
			Paddle_Speed_2 = Paddle_Speed_2 / 2;
		}
		time(&Start);
		H_Game.Create_New_Layer();
	}
	if (Mode == 4){
		Arena();
	}

	Base_2 = Paddle_Speed_2;
	H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Physics_Object(-Ball_Speed, 0.0, 0.0);
	Game_Good = 0;
}
void Game::Every_Turn(){
	if (Mode == 1){
		if (Score_1 == 10){
			Game_Good = 1;
		}
		if (Score_2 == 10){
			Game_Good = 2;
		}
	}
	if (Mode == 2){
		int Last = Seconds;
		time(&End);
		Seconds = Seconds + End - Start;
		if (Seconds > 60){
			Seconds - 60;
			Minutes++;
		}
		if (Seconds != Last){
			H_Game.Layers[0]->Button_Objects[0]->Edit_Button_Object(to_string(Minutes) + ":" + to_string(Seconds));
		}
		time(&Start);
	}
	if (Mode == 3){
		if (Score_1 == 10){
			Game_Good = 1;
		}
		if (Score_2 == 10){
			Game_Good = 2;
		}
		int Last = Seconds;
		time(&End);
		Seconds = Seconds + End - Start;
		int Size = Power_Ups.size();
		cout << Size << endl;
		if (Seconds != Last){
			for (unsigned i = 0; i < Size; i++){
				Power_Ups[i].Life--;
				if (i == 0){
					//cout << Power_Ups[i].Life << endl;
				}
				if (Power_Ups[i].Life == 0){
					if (i == 0){
						cout << "-----\n";
					}
					Size--;
					cout << "A";
					H_Game.Layers[2]->Textured_Objects.erase(H_Game.Layers[2]->Textured_Objects.begin(), H_Game.Layers[2]->Textured_Objects.begin()+Power_Ups[i].Index + 1);
					Power_Ups.erase(Power_Ups.begin(), Power_Ups.begin() + i);
					cout << "B";
					for (int a = i; a < Power_Ups.size(); a++){
						Power_Ups[a].Index--;
					}
					cout << "C\n";
				}
			}
			int Spawn = (10 / (Paddle_Speed * 50));
			if (Spawn > 15){
				Spawn = 15;
			}
			if ((rand() % Spawn) == 0 && Size < 5){
				int Power = (rand() % 6);
				float x, y = 0.0;
				x = (float)(rand() % 160) / (float)(100);
				x = x - 1;
				y = (float)(rand() % 200) / (float)(100);
				y = y - 1;
				Power_Up power_up;
				power_up.Power = Power;
				power_up.Life = 5;
				power_up.Index = H_Game.Layers[2]->Textured_Objects.size();
				H_Game.Layers[2]->Initilize_Object(2);
				Power_Ups.push_back(power_up);
				if (Power == 0){
					H_Game.Layers[2]->Textured_Objects[power_up.Index]->New_Textured_Object("Textures/Game/Larger Ball", 4, 0.05, 0.05, 0);
				}
				if (Power == 1){
					H_Game.Layers[2]->Textured_Objects[power_up.Index]->New_Textured_Object("Textures/Game/Smaller Ball", 4, 0.05, 0.05, 0);
				}
				if (Power == 2){
					H_Game.Layers[2]->Textured_Objects[power_up.Index]->New_Textured_Object("Textures/Game/Larger Paddle", 4, 0.05, 0.05, 0);
				}
				if (Power == 3){
					H_Game.Layers[2]->Textured_Objects[power_up.Index]->New_Textured_Object("Textures/Game/Smaller Paddle", 4, 0.05, 0.05, 0);
				}
				if (Power == 4){
					H_Game.Layers[2]->Textured_Objects[power_up.Index]->New_Textured_Object("Textures/Game/Super Ball", 4, 0.05, 0.05, 0);
				}
				if (Power == 5){
					H_Game.Layers[2]->Textured_Objects[power_up.Index]->New_Textured_Object("Textures/Game/Super Paddle", 4, 0.05, 0.05, 0);
				}
				H_Game.Layers[2]->Textured_Objects[power_up.Index]->Translate_Object(x, y, 0.0);
			}
		}
		time(&Start);
	}
}
void Game::Score(){
	Point = Check_For_Point();
	if (Point != 0){
		float x, y;
		if (Mode == 1){
			if (Point == 1){
				Score_1++;
				H_Game.Layers[0]->Button_Objects[0]->Edit_Button_Object(to_string(Score_1));
				H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Physics_Object(-Ball_Speed, 0.0, 0.0);
			}
			if (Point == 2){
				Score_2++;
				H_Game.Layers[0]->Button_Objects[1]->Edit_Button_Object(to_string(Score_2));
				H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Physics_Object(Ball_Speed, 0.0, 0.0);
			}
			x = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2);
			y = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(3);
			H_Game.Layers[1]->Physics_Objects[0]->Physics->Translate_Object(-x, -y, 0.0);
			Paddle_Speed = Base_1;
			Paddle_Speed_2 = Base_2;
		}
		if (Mode == 2){
			if (Point == 1){
				Score_1++;
				H_Game.Layers[0]->Button_Objects[1]->Edit_Button_Object(to_string(Score_1));
				H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Physics_Object(-H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(1), 0.0, 0.0);
				x = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2);
				y = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(3);
				H_Game.Layers[1]->Physics_Objects[0]->Physics->Translate_Object(-x, -y, 0.0);
			}
			if (Point == 2){
				Game_Good = 1;
			}
		}
		if (Mode == 3){
			if (Point == 1){
				Score_1++;
				H_Game.Layers[0]->Button_Objects[0]->Edit_Button_Object(to_string(Score_1));
				H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Physics_Object(-Ball_Speed, 0.0, 0.0);
			}
			if (Point == 2){
				Score_2++;
				H_Game.Layers[0]->Button_Objects[1]->Edit_Button_Object(to_string(Score_2));
				H_Game.Layers[1]->Physics_Objects[0]->Set_Velocity_Physics_Object(Ball_Speed, 0.0, 0.0);
			}
			x = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2);
			y = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(3);
			H_Game.Layers[1]->Physics_Objects[0]->Physics->Translate_Object(-x, -y, 0.0);
			Paddle_Speed = Base_1;
			Paddle_Speed_2 = Base_2;
			for (unsigned a = 0; a < Power_Ups.size(); a++){
				Power_Ups[a].Life = 1;
			}
		}
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
	if (Mode == 2){
		if (H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2) < -1){
			return(2);
		}
		if (H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2) > 1){
			return(1);
		}
	}
	if (Mode == 3){
		if (H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2) < -1){
			return(2);
		}
		if (H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2) > 1){
			return(1);
		}
	}
	return(0);
}
void Game::End_Screen(){
	int Layer = -1, Button = -1, Action = -1, Delay = 10;
	H_Game.Clear_All_Layers();
	H_Game.Create_New_Layer();
	H_Game.Layers[1]->Initilize_Object(4);
	H_Game.Layers[1]->Button_Objects[0]->New_Button_Object("RETURN TO MENU", "Textures/Buttons/Selection", "Basic/White", 0.5, 0.1);
	H_Game.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, -0.5, 0.0);
	if (Mode == 1){
		if (Game_Good == 1){
			H_Game.Layers[0]->Initilize_Object(4);
			H_Game.Layers[0]->Button_Objects[0]->New_Button_Object("YOU WIN", "Textures/Buttons/Transparent", "Basic/White", 1.0, 0.5);
			H_Game.Layers[0]->Button_Objects[0]->Translate_Button_Object(0.0, 0.5, 0.0);
		}
		else{
			H_Game.Layers[0]->Initilize_Object(4);
			H_Game.Layers[0]->Button_Objects[0]->New_Button_Object("YOU LOSE", "Textures/Buttons/Transparent", "Basic/White", 1.0, 0.5);
			H_Game.Layers[0]->Button_Objects[0]->Translate_Button_Object(0.0, 0.5, 0.0);
		}
	}
	if (Mode == 2){
		H_Game.Layers[0]->Initilize_Object(4);
		H_Game.Layers[0]->Button_Objects[0]->New_Button_Object("YOU LOSE", "Textures/Buttons/Transparent", "Basic/White", 1.0, 0.5);
		H_Game.Layers[0]->Button_Objects[0]->Translate_Button_Object(0.0, 0.5, 0.0);
		H_Game.Layers[0]->Initilize_Object(4);
		H_Game.Layers[0]->Button_Objects[1]->New_Button_Object(to_string(Minutes) + ":" + to_string(Seconds), "Textures/Buttons/Transparent", "Basic/White", 0.5, 0.2);
		H_Game.Layers[0]->Button_Objects[1]->Translate_Button_Object(0.0, 0.0, 0.0);
		H_Game.Layers[0]->Initilize_Object(4);
		H_Game.Layers[0]->Button_Objects[2]->New_Button_Object(to_string(Score_1), "Textures/Buttons/Transparent", "Basic/White", 0.5, 0.2);
		H_Game.Layers[0]->Button_Objects[2]->Translate_Button_Object(0.0, -0.2, 0.0);
	}
	while (Game_Good != 0){
		if (Delay > 0){
			Delay--;
			H_Game.Set_Mouse(-1, -1);
			Layer = -1;
		}
		else{
			H_Game.Check_All_Buttons(Layer, Button, Action);
		}
		if (Layer == 1 && Button == 0){
			Game_Good = 0;
		}
		H_Game.Display_All_Layers();
		H_Game.Frame();
	}
}

int Game::Classic(){
	Score_1 = 0;
	Score_2 = 0;
	Paddle_Speed = 0.01;
	Paddle_Speed_2 = 0.01;
	Base_1 = 0.01;
	Base_2 = 0.01;
	Ball_Speed = 0.5;
	H_Game.Layers[0]->Initilize_Object(2);
	H_Game.Layers[0]->Textured_Objects[0]->New_Textured_Object("Textures/Game/Dividing Line", 4, 0.005, 1, 0);
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
	Score_1 = 0;
	Minutes = 0;
	Seconds = 0;
	Paddle_Speed = 0.01;
	Paddle_Speed_2 = 0.01;
	Base_1 = 0.01;
	Base_2 = 0.01;
	Ball_Speed = 0.5;
	H_Game.Layers[0]->Initilize_Object(2);
	H_Game.Layers[0]->Textured_Objects[0]->New_Textured_Object("Textures/Game/Dividing Line", 4, 0.005, 1, 0);
	H_Game.Layers[0]->Initilize_Object(4);
	H_Game.Layers[0]->Button_Objects[0]->New_Button_Object(to_string(Minutes) + ":" + to_string(Seconds), "Textures/Buttons/Transparent", "Basic/White", 0.3, 0.3);
	H_Game.Layers[0]->Button_Objects[0]->Translate_Button_Object(-0.5, 0.7, 0.0);
	H_Game.Layers[0]->Initilize_Object(4);
	H_Game.Layers[0]->Button_Objects[1]->New_Button_Object(to_string(Score_1), "Textures/Buttons/Transparent", "Basic/White", 0.3, 0.3);
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
int Game::Special(){
	Score_1 = 0;
	Score_2 = 0;
	Paddle_Speed = 0.01;
	Paddle_Speed_2 = 0.01;
	Base_1 = 0.01;
	Base_2 = 0.01;
	Ball_Speed = 0.5;
	H_Game.Layers[0]->Initilize_Object(2);
	H_Game.Layers[0]->Textured_Objects[0]->New_Textured_Object("Textures/Game/Dividing Line", 4, 0.005, 1, 0);
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
int Game::Arena(){
	cout << "D";
	return(0);
}