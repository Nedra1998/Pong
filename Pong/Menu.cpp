#include "Libraries.h"
#include "Logging.h"
#include "Hephaestus.h"
#include "Game.h"
#include "Menu.h"
using namespace std;
Game G_Menu;
bool Menu::Close(){
	if (glfwWindowShouldClose(W_Menu)){
		Good = false;
		return(true);
	}
	return(false);
}
void Menu::Run_Menu_Program(Hephaestus H, GLFWwindow* W){
	H_Menu = H;
	W_Menu = W;
	int Load = 1, Stage = 1, Delay = 15;
	int Layer = -1, Button = -1, Action = -1;
	Mouse = false;
	Difficulty = 3;
	while (!glfwWindowShouldClose(W_Menu) && Good == true){
		/*>>>>>Place While Running Code Here<<<<<*/
		if (Load != 0 && Load < 10){
			Stage = Load;
			H_Menu.Clear_All_Layers();
			if (Load == 1){
				Main_Menu();
			}
			if (Load == 2){
				Single_Player_Menu_1();
			}
			if (Load == 3){
				Multi_Player_Menu();
			}
			if (Load == 4){
				Settings_Menu();
			}
			if (Load == 6){
				Single_Player_Menu_2();
			}
			Load = 0;
			Delay = 10;
		}
		if (Load >= 10 && Load < 20){
			if (Control == 1){
				Mouse = true;
			}
			else{
				Mouse = false;
			}
			G_Menu.Run_Game_Program_Single_Player(Load - 9, H_Menu, W_Menu, Mouse, Difficulty);
			Load = 1;
			Stage = 1;
			Delay = 10;
		}
		if (Load >= 20){
		
			G_Menu.Run_Game_Program_Multi_Player(Load - 19, H_Menu, W_Menu);
			Load = 1;
			Stage = 1;
			Delay = 10;
		}
		while (Load == 0){
			if (Delay > 0){
				Delay--;
				H_Menu.Set_Mouse(-1, -1);
				Layer = -1;
			}
			else{
				H_Menu.Check_All_Buttons(Layer, Button, Action);
			}
			if (Layer == 1){
				if (Stage == 1){
					if (Button == 0){
						Load = 2;
					}
					if (Button == 1){
						Load = 3;
					}
					if (Button == 2){
						Load = 4;
					}
					if (Button == 3){
						Good = false;
						Load = -1;
					}
				}
				else if (Stage == 2){
					if (Button == 0){
						Mode = 10;
						Load = 6;
					}
					if (Button == 1){
						Mode = 11;
						Load = 6;
					}
					if (Button == 2){
						Mode = 12;
						Load = 6;
					}
					if (Button == 3){
						Mode = 13;
						Load = 6;
					}
					if (Button == 4){
						Mode = 14;
						Load = 6;
					}
					if (Button == 5){
						Load = 1;
					}
				}
				else if (Stage == 3){
					if (Button == 0){
						Load = 20;
					}
					if (Button == 1){
						Load = 22;
					}
					if (Button == 2){
						Load = 1;
					}
				}
				else if (Stage == 4){
					if (Button == 4){
						Load = 1;
					}
					if (Button == 0){
						int i = H_Menu.Win.Get_Window_Size(1);
						int f = H_Menu.Win.Get_Window_Size(2);
						i++;
						if (i > 7){
							i = 1;
						}
						H_Menu.Win.Set_Window(i, f);
						Load = 4;
					}
					if (Button == 1){
						int i = H_Menu.Win.Get_Window_Size(1);
						int f = H_Menu.Win.Get_Window_Size(2);
						if (f == 1){
							f = 0;
						}
						else{
							f = 1;
						}
						H_Menu.Win.Set_Window(i, f);
						Load = 4;
					}
					if (Button == 2 && Control == 0){
						Control = 1;
						ofstream Save("Game Data.txt");
						if (Save.is_open()){
							Save << Control;
							Save.close();
						}
						Load = 4;
					}
					if (Button == 3 && Control == 1){
						Control = 0;
						ofstream Save("Game Data.txt");
						if (Save.is_open()){
							Save << Control;
							Save.close();
						}
						Load = 4;
					}
				}
				else if (Stage == 6){
					if (Button != 4 && Button != -1){
						Difficulty = Button;
						Load = Mode;
					}
					if (Button == 4){
						Load = 2;
					}
				}
			}
			if (Close() == true){
				Load = -1;
			}
			H_Menu.Display_All_Layers();
			H_Menu.Frame();
		}
	}
}
void Menu::Mouse_Call(GLFWwindow* Win, int button, int action, int mods){
	G_Menu.H_Game.Mouse_Call_Back(Win, button, action, mods);
}
void Menu::Main_Menu(){
	H_Menu.Layers[0]->Initilize_Object(4);
	H_Menu.Layers[0]->Button_Objects[0]->New_Button_Object("PONG", "Textures/Buttons/Transparent", "Basic/White", 1.0, 0.4);
	H_Menu.Layers[0]->Button_Objects[0]->Translate_Button_Object(0.05, 0.7, 0.0);
	H_Menu.Create_New_Layer();
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object("/Single Player/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, 0.2, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object("/Multi Player/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.0, 0.0, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("/Settings/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.0, -0.2, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("/Quit/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(0.0, -0.4, 0.0);
}
void Menu::Settings_Menu(){
	int x, y;
	ifstream Load("Game Data.txt");
	if (Load.is_open()){
		Load >> Control;
		Load.close();
	}
	H_Menu.Layers[0]->Initilize_Object(4);
	H_Menu.Layers[0]->Button_Objects[0]->New_Button_Object("SETTINGS", "Textures/Buttons/Transparent", "Basic/White", 1.0, 0.5);
	H_Menu.Layers[0]->Button_Objects[0]->Translate_Button_Object(0.0, 0.6, 0.0);
	H_Menu.Create_New_Layer();
	H_Menu.Layers[0]->Initilize_Object(4);
	H_Menu.Layers[0]->Button_Objects[1]->New_Button_Object("/Resolution/", "Textures/Buttons/Transparent", "Basic/White", 0.5, .1);
	H_Menu.Layers[0]->Button_Objects[1]->Translate_Button_Object(0.0, 0.2, 0.0);
	H_Menu.Win.Window_Res(x, y);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object(to_string(x) + "x" + to_string(y), "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, 0.0, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	if (H_Menu.Win.Get_Window_Size(2) == 1){
		H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object("/Full Screen X /", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	}
	else{
		H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object("/Full Screen   /", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	}
	H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.0, -0.2, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	if (Control == 1){
		H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("", "Textures/Buttons/MouseS 1", "Basic/White", 0.1, .1);
	}
	else{
		H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("", "Textures/Buttons/MouseN", "Basic/White", 0.1, .1);
	}
	H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(-0.2, -0.4, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	if (Control == 1){
		H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("", "Textures/Buttons/KeyN", "Basic/White", 0.1, .1);
	}
	else{
		H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("", "Textures/Buttons/KeyS 1", "Basic/White", 0.1, .1);
	}
	H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(0.2, -0.4, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[4]->New_Button_Object("BACK", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[4]->Translate_Button_Object(0.0, -0.6, 0.0);
}
void Menu::Single_Player_Menu_1(){
	H_Menu.Layers[0]->Initilize_Object(4);
	H_Menu.Layers[0]->Button_Objects[0]->New_Button_Object("SINGLE PLAYER", "Textures/Buttons/Transparent", "Basic/White", 1.0, 0.4);
	H_Menu.Layers[0]->Button_Objects[0]->Translate_Button_Object(0.0, 0.7, 0.0);
	H_Menu.Create_New_Layer();
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object("/Classic/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, 0.2, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object("/Timed/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.0, 0.0, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("/Power Up/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.0, -0.2, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("/Arena/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(0.0, -0.4, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[4]->New_Button_Object("/1V3/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[4]->Translate_Button_Object(0.0, -0.6, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[5]->New_Button_Object("/Back/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[5]->Translate_Button_Object(0.0, -0.8, 0.0);
}
void Menu::Single_Player_Menu_2(){
	H_Menu.Layers[0]->Initilize_Object(4);
	H_Menu.Layers[0]->Button_Objects[0]->New_Button_Object("SINGLE PLAYER", "Textures/Buttons/Transparent", "Basic/White", 1.0, 0.4);
	H_Menu.Layers[0]->Button_Objects[0]->Translate_Button_Object(0.0, 0.7, 0.0);
	H_Menu.Create_New_Layer();
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object("/Insane/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, 0.2, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object("/Hard/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.0, 0.0, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("/Normal/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.0, -0.2, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("/Easy/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(0.0, -0.4, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[4]->New_Button_Object("/Back/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[4]->Translate_Button_Object(0.0, -0.6, 0.0);
}
void Menu::Multi_Player_Menu(){
	H_Menu.Layers[0]->Initilize_Object(4);
	H_Menu.Layers[0]->Button_Objects[0]->New_Button_Object("MULTI PLAYER", "Textures/Buttons/Transparent", "Basic/White", 1.0, 0.4);
	H_Menu.Layers[0]->Button_Objects[0]->Translate_Button_Object(0.0, 0.7, 0.0);
	H_Menu.Create_New_Layer();
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object("/Classic/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, 0.2, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object("/Power Up/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.0, 0.0, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("/Back/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.0, -0.2, 0.0);
}