#include "Libraries.h"
#include "Logging.h"
#include "Hephaestus.h"
#include "Menu.h"
#include "Game.h"
using namespace std;
bool Menu::Close(){
	if (glfwWindowShouldClose(W_Menu)){
		Good = false;
		return(true);
	}
	return(false);
}
void Menu::Run_Menu_Program(Hephaestus H, GLFWwindow* W){
	Game G_Menu;
	H_Menu = H;
	W_Menu = W;
	int Load = 1, Stage = 1, Delay = 15;
	int Layer = -1, Button = -1, Action = -1;
	while (!glfwWindowShouldClose(W_Menu) && Good == true){
		/*>>>>>Place While Running Code Here<<<<<*/
		if (Load != 0 && Load < 10){
			H_Menu.Clear_All_Layers();
			if (Load == 1){
				Main_Menu();
			}
			if (Load == 2){
				Single_Player_Menu();
			}
			if (Load == 3){
				Multi_Player_Menu_1();
			}
			if (Load == 4){
				Settings_Menu();
			}
			if (Load == 5){
				Multi_Player_Menu_2();
			}
			Load = 0;
			Delay = 10;
		}
		if (Load >= 10){
			G_Menu.Run_Game_Program(Load - 9, H_Menu, W_Menu);
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
						Stage = 2;
					}
					if (Button == 1){
						Load = 3;
						Stage = 3;
					}
					if (Button == 2){

					}
					if (Button == 3){
						Load = 4;
						Stage = 4;
					}
					if (Button == 4){
						Good = false;
						Load = -1;
					}
				}
				else if (Stage == 2){
					if (Button == 0){
						Load = 10;
					}
					if (Button == 1){
						Load = 11;
					}
					if (Button == 2){
						Load = 12;
					}
					if (Button == 3){
						Load = 13;
					}
					if (Button == 4){
						Load = 1;
						Stage = 1;
					}
				}
				else if (Stage == 3){
					if (Button == 0 || Button == 1 || Button == 2){
						Load = 5;
						Stage = 5;
					}
					if (Button == 3){
						Load = 1;
						Stage = 1;
					}
				}
				else if (Stage == 4){
					if (Button == 2){
						Load = 1;
						Stage = 1;
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
				}
				else if (Stage == 5){
					if (Button == 2){
						Load = 3;
						Stage = 3;
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
	H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("/High Scores/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.0, -0.2, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("/Settings/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(0.0, -0.4, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[4]->New_Button_Object("/Quit/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[4]->Translate_Button_Object(0.0, -0.6, 0.0);
}
void Menu::Settings_Menu(){
	int x, y;
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
	H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("BACK", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.0, -0.4, 0.0);
}
void Menu::Single_Player_Menu(){
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
	H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("/Special/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.0, -0.2, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("/Arena/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(0.0, -0.4, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[4]->New_Button_Object("/Back/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[4]->Translate_Button_Object(0.0, -0.6, 0.0);
}
void Menu::Multi_Player_Menu_1(){
	H_Menu.Layers[0]->Initilize_Object(4);
	H_Menu.Layers[0]->Button_Objects[0]->New_Button_Object("MULTI PLAYER", "Textures/Buttons/Transparent", "Basic/White", 1.0, 0.4);
	H_Menu.Layers[0]->Button_Objects[0]->Translate_Button_Object(0.0, 0.7, 0.0);
	H_Menu.Create_New_Layer();
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object("/2/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, 0.2, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object("/3/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.0, 0.0, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("/4/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.0, -0.2, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[3]->New_Button_Object("/Back/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[3]->Translate_Button_Object(0.0, -0.4, 0.0);
}
void Menu::Multi_Player_Menu_2(){
	H_Menu.Layers[0]->Initilize_Object(4);
	H_Menu.Layers[0]->Button_Objects[0]->New_Button_Object("MULTI PLAYER", "Textures/Buttons/Transparent", "Basic/White", 1.0, 0.4);
	H_Menu.Layers[0]->Button_Objects[0]->Translate_Button_Object(0.0, 0.7, 0.0);
	H_Menu.Create_New_Layer();
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[0]->New_Button_Object("/Classic/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[0]->Translate_Button_Object(0.0, 0.2, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[1]->New_Button_Object("/Special/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[1]->Translate_Button_Object(0.0, 0.0, 0.0);
	H_Menu.Layers[1]->Initilize_Object(4);
	H_Menu.Layers[1]->Button_Objects[2]->New_Button_Object("/Back/", "Textures/Buttons/Selection", "Basic/White", 0.5, .1);
	H_Menu.Layers[1]->Button_Objects[2]->Translate_Button_Object(0.0, -0.2, 0.0);
}