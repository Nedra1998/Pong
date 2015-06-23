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
			float  Y_Paddle = 0.0, Y_Ball, VY, VX;
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
		PowerUP();
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
		time(&Start);
		float XB, YB, XP, YP;
		XB = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2);
		YB = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(3);
		for (unsigned a = 0; a < Pick_Ups.size(); a++){
			XP = H_Game.Layers[2]->Textured_Objects[Pick_Ups[a].Index]->Return_Float_Value(2);
			YP = H_Game.Layers[2]->Textured_Objects[Pick_Ups[a].Index]->Return_Float_Value(3);
			if (XB < XP + 0.05 && XB > XP - 0.05 && YB < YP + 0.05 && YB > YP - 0.05){
				Pick_Ups[a].Life = 10;
				H_Game.Layers[2]->Textured_Objects.erase(H_Game.Layers[2]->Textured_Objects.begin() + Pick_Ups[a].Index);
				Power_Ups.push_back(Pick_Ups[a]);
				Pick_Ups.erase(Pick_Ups.begin() + a);
				for (unsigned b = a; b < Pick_Ups.size(); b++){
					Pick_Ups[b].Index--;
				}
			}
		}

		for (unsigned a = 0; a < Power_Ups.size(); a++){
			if (Power_Ups[a].Power == 0 && Power_Ups[a].Active == false){
				Power_Ups[a].Active = true;
				float x, y, xp, yp;
				x = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(4);
				xp = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2);
				x = x * 2;
				y = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(5);
				yp = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(3);
				y = y * 2;
				H_Game.Layers[1]->Physics_Objects[0]->Translate_Physics_Object(-xp, -yp, 0.0);
				H_Game.Layers[1]->Physics_Objects[0]->Physics->New_Colored_Object(4, x, y, 1.0, 1.0, 1.0, 1.0, 1);
				H_Game.Layers[1]->Physics_Objects[0]->Translate_Physics_Object(xp, yp, 0.0);
			}
			if (Power_Ups[a].Power == 1 && Power_Ups[a].Active == false){
				Power_Ups[a].Active = true;
				float x, y, xp, yp;
				x = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(4);
				xp = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2);
				x = x / 2;
				y = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(5);
				yp = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(3);
				y = y / 2;
				H_Game.Layers[1]->Physics_Objects[0]->Translate_Physics_Object(-xp, -yp, 0.0);
				H_Game.Layers[1]->Physics_Objects[0]->Physics->New_Colored_Object(4, x, y, 1.0, 1.0, 1.0, 1.0, 1);
				H_Game.Layers[1]->Physics_Objects[0]->Translate_Physics_Object(xp, yp, 0.0);
			}
			if (Power_Ups[a].Power == 2 && Power_Ups[a].Active == false){
				Power_Ups[a].Active = true;
				if (H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(1) < 0){
					Power_Ups[a].Left = false;
				}
				else{
					Power_Ups[a].Left = true;
				}
				float y, xp, yp;
				int Object = 0;
				if (Power_Ups[a].Left == false){
					Object = 1;
				}
				xp = H_Game.Layers[1]->Colored_Objects[Object]->Return_Float_Value(2);
				y = H_Game.Layers[1]->Colored_Objects[Object]->Return_Float_Value(5);
				yp = H_Game.Layers[1]->Colored_Objects[Object]->Return_Float_Value(3);
				y = y * 1.5;
				H_Game.Layers[1]->Colored_Objects[Object]->Translate_Object(-xp, -yp, 0.0);
				H_Game.Layers[1]->Colored_Objects[Object]->New_Colored_Object(4, 0.01, y, 1.0, 1.0, 1.0, 1.0, 1);
				H_Game.Layers[1]->Colored_Objects[Object]->Translate_Object(xp, yp, 0.0);
			}
			if (Power_Ups[a].Power == 3 && Power_Ups[a].Active == false){
				Power_Ups[a].Active = true;
				if (H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(1) < 0){
					Power_Ups[a].Left = false;
				}
				else{
					Power_Ups[a].Left = true;
				}
				float y, xp, yp;
				int Object = 0;
				if (Power_Ups[a].Left == false){
					Object = 1;
				}
				xp = H_Game.Layers[1]->Colored_Objects[Object]->Return_Float_Value(2);
				y = H_Game.Layers[1]->Colored_Objects[Object]->Return_Float_Value(5);
				yp = H_Game.Layers[1]->Colored_Objects[Object]->Return_Float_Value(3);
				y = y / 1.5;
				H_Game.Layers[1]->Colored_Objects[Object]->Translate_Object(-xp, -yp, 0.0);
				H_Game.Layers[1]->Colored_Objects[Object]->New_Colored_Object(4, 0.01, y, 1.0, 1.0, 1.0, 1.0, 1);
				H_Game.Layers[1]->Colored_Objects[Object]->Translate_Object(xp, yp, 0.0);
			}
			if (Power_Ups[a].Power == 4 && Power_Ups[a].Active == false){
				Power_Ups[a].Active = true;
				float vx, vy;
				vx = H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(1);
				vy = H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(2);
				vx = vx / 2;
				vy = vy / 2;
				H_Game.Layers[1]->Physics_Objects[0]->Add_Velocity_Physics_Object(vx, vy, 0.0);
				vx = H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(1);
				vy = H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(2);
			}
			if (Power_Ups[a].Power == 5 && Power_Ups[a].Active == false){
				Power_Ups[a].Active = true;
				if (H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(1) < 0){
					Power_Ups[a].Left = false;
				}
				else{
					Power_Ups[a].Left = true;
				}
				if (Power_Ups[a].Left == false){
					Paddle_Speed_2 = Paddle_Speed_2 * 1.5;
				}
				if (Power_Ups[a].Left == true){
					Paddle_Speed = Paddle_Speed * 1.5;
				}
			}
		}
		if (Seconds != Last){
			for (unsigned a = 0; a <  Pick_Ups.size(); a++){
				Pick_Ups[a].Life--;
				if (Pick_Ups[a].Life == 0){
					H_Game.Layers[2]->Textured_Objects.erase(H_Game.Layers[2]->Textured_Objects.begin() + Pick_Ups[a].Index);
					Pick_Ups.erase(Pick_Ups.begin() + a);
					for (unsigned b = a; b < Pick_Ups.size(); b++){
						Pick_Ups[b].Index--;
					}
				}
			}
			for (unsigned a = 0; a < Power_Ups.size(); a++){
				Power_Ups[a].Life--;
				if (Power_Ups[a].Life == 0){
					if (Power_Ups[a].Power == 0){
						float x, y, xp, yp;
						x = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(4);
						xp = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2);
						x = x / 2;
						y = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(5);
						yp = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(3);
						y = y / 2;
						H_Game.Layers[1]->Physics_Objects[0]->Translate_Physics_Object(-xp, -yp, 0.0);
						H_Game.Layers[1]->Physics_Objects[0]->Physics->New_Colored_Object(4, x, y, 1.0, 1.0, 1.0, 1.0, 1);
						H_Game.Layers[1]->Physics_Objects[0]->Translate_Physics_Object(xp, yp, 0.0);
					}
					if (Power_Ups[a].Power == 1){
						float x, y, xp, yp;
						x = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(4);
						xp = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(2);
						x = x * 2;
						y = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(5);
						yp = H_Game.Layers[1]->Physics_Objects[0]->Physics->Return_Float_Value(3);
						y = y * 2;
						H_Game.Layers[1]->Physics_Objects[0]->Translate_Physics_Object(-xp, -yp, 0.0);
						H_Game.Layers[1]->Physics_Objects[0]->Physics->New_Colored_Object(4, x, y, 1.0, 1.0, 1.0, 1.0, 1);
						H_Game.Layers[1]->Physics_Objects[0]->Translate_Physics_Object(xp, yp, 0.0);
					}
					if (Power_Ups[a].Power == 2){
						float y, xp, yp;
						int Object = 0;
						if (Power_Ups[a].Left == false){
							Object = 1;
						}
						xp = H_Game.Layers[1]->Colored_Objects[Object]->Return_Float_Value(2);
						y = H_Game.Layers[1]->Colored_Objects[Object]->Return_Float_Value(5);
						yp = H_Game.Layers[1]->Colored_Objects[Object]->Return_Float_Value(3);
						y = y / 1.5;
						H_Game.Layers[1]->Colored_Objects[Object]->Translate_Object(-xp, -yp, 0.0);
						H_Game.Layers[1]->Colored_Objects[Object]->New_Colored_Object(4, 0.01, y, 1.0, 1.0, 1.0, 1.0, 1);
						H_Game.Layers[1]->Colored_Objects[Object]->Translate_Object(xp, yp, 0.0);
					}
					if (Power_Ups[a].Power == 3){
						float y, xp, yp;
						int Object = 0;
						if (Power_Ups[a].Left == false){
							Object = 1;
						}
						xp = H_Game.Layers[1]->Colored_Objects[Object]->Return_Float_Value(2);
						y = H_Game.Layers[1]->Colored_Objects[Object]->Return_Float_Value(5);
						yp = H_Game.Layers[1]->Colored_Objects[Object]->Return_Float_Value(3);
						y = y * 1.5;
						H_Game.Layers[1]->Colored_Objects[Object]->Translate_Object(-xp, -yp, 0.0);
						H_Game.Layers[1]->Colored_Objects[Object]->New_Colored_Object(4, 0.01, y, 1.0, 1.0, 1.0, 1.0, 1);
						H_Game.Layers[1]->Colored_Objects[Object]->Translate_Object(xp, yp, 0.0);
					}
					if (Power_Ups[a].Power == 4){
						float vx, vy;
						vx = H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(1);
						vy = H_Game.Layers[1]->Physics_Objects[0]->Return_Physics_Data(2);
						vx = vx / 2;
						vy = vy / 2;
						H_Game.Layers[1]->Physics_Objects[0]->Add_Velocity_Physics_Object(-vx, -vy, 0.0);
					}
					if (Power_Ups[a].Power == 5){
						if (Power_Ups[a].Left == false){
							Paddle_Speed_2 = Paddle_Speed_2 / 1.5;
						}
						if (Power_Ups[a].Left == true){
							Paddle_Speed = Paddle_Speed / 1.5;
						}
					}
					Power_Ups.erase(Power_Ups.begin() + a);
				}
			}
			if (rand() % 2 == 0){
				int power = (rand() % 6);
				float x, y;
				string Name = "Textures/Game/";
				Power_Up temp;
				x = (float)(rand() % 150) / (float)(100);
				x = x - 0.75;
				y = (float)(rand() % 150) / (float)(100);
				y = y - 0.75;
				temp.Power = power;
				temp.Active = false;
				temp.Life = 10;
				if (power == 0){
					Name = Name + "Larger Ball";
				}
				if (power == 1){
					Name = Name + "Smaller Ball";
				}
				if (power == 2){
					Name = Name + "Larger Paddle";
				}
				if (power == 3){
					Name = Name + "Smaller Paddle";
				}
				if (power == 4){
					Name = Name + "Super Ball";
				}
				if (power == 5){
					Name = Name + "Super Paddle";
				}
				temp.Index = H_Game.Layers[2]->Textured_Objects.size();
				Pick_Ups.push_back(temp);
				H_Game.Layers[2]->Initilize_Object(2);
				H_Game.Layers[2]->Textured_Objects[temp.Index]->New_Textured_Object(Name, 4, 0.05, 0.05, 0);
				H_Game.Layers[2]->Textured_Objects[temp.Index]->Translate_Object(x, y, 0.0);
			}
		}
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
			for (unsigned a = 0; a < Pick_Ups.size(); a++){
				H_Game.Layers[2]->Textured_Objects.erase(H_Game.Layers[2]->Textured_Objects.begin() + Pick_Ups[a].Index);
				Pick_Ups.erase(Pick_Ups.begin() + a);
				for (int b = a; b < Pick_Ups.size(); b++){
					Pick_Ups[b].Index--;
				}
			}
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
int Game::PowerUP(){
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