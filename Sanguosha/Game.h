#pragma once
#include "core.h"

class Game
{
public:
	RenderWindow window;

	// style mode
	int globe_style_mode;
	int gamestart_style;
	int gameinfo_style;
	int gamechoose_style;
	int gameover_state;                   // for gameover to judge lose or win 0--lose;1--win;default value is -1;
	/// <for-style-change>
	bool change_bg;
	int button_animate_count;
	/// </for-style-change>

	int window_width, window_height;
	int turn;                             // the mask of turning
	int exturn;
	int exturn_backup;

	int round_loop_starter;               // mark loop starter
	// dying round loop
	bool dying_loop;                      // flag to judge if a loop have been existed
	bool amazing_grace_loop;
	bool archery_attack_loop;

	bool restart;                         // signal of gamer restart
	bool gamestart, gameover, gamequit,gamerun,gamechoose,gamepause,gameinfo;
	bool new_round;
	bool human_defense;                   // bool to see its turn to human defense
	bool animator_running;                // judge animator is running ,so that machine play wont play so fast
	// for human player to decide how many machines he&she want play with
	int machine_number;                   // also limited number is 4
	Vector2i virtual_vector;              // a virtual coordinate for overflow error
    // record who set signal of begging peach
	int peach_begger;
	Event event_global;
	Pile_Card piles;
	Player Human, Machine[4];
	Vector2i mouse_count_clock_one, mouse_count_clock_two;
	Clock mouse_click_timer;
	// for stable background
	Texture texture_background, texture_player_equip_board, texture_player_hand_board, texture_player_button_background, texture_player_role_background, texture_npcboard, texture_npc_cards, texture_piles_back;
	Sprite sprite_background, sprite_player_equip_board, sprite_player_hand_board, sprite_player_button_background, sprite_player_role_background, sprite_npcboard, sprite_npc_cards, sprite_piles_back;
	// for npc
	Texture texture_being_chosen;
	Sprite sprite_being_chosen;
	// for button
	Button button_cancel, button_discard, button_ok;
	// for HP
	Texture texture_Human_HP, texture_Machine_HP;
	Sprite sprite_Human_HP, sprite_Machine_HP;
	// for dying state
	Texture texture_Human_save_me;
	Sprite sprite_Human_save_me;
	// Game Class
	void out_put(Single_Card single);
	// for count the killing number
	//int killing_number;
	// display discard pile
	Pile_Card discard_pile;
	Texture texture_discard_pile;
	Sprite sprite_discard_pile;
	// for message boxes
	Message_Box message;
	int message_amount;

	// temp piles card (using in amazing grace or any other situation that is needed card displayed
	Pile_Card temp_pile;


	// globe input sent
	Vector2i input_sent;

	int img_bg_number;         // when game run ,change background

    // GAME-START texture & sprite
	Texture texture_gamestart_bg;
	Sprite sprite_gamestart_bg;
	// GAME-START Button
	Button gamestart_go;
	Button gamestart_info;
	Button gamestart_quit;

    // GAME-INFO texture & sprite
	Texture texture_gameinfo_bg, texture_gameinfo_thanks, texture_gameinfo_gameinfo, texture_gameinfo_phaseinfo, texture_gameinfo_cardinfo;
	Sprite sprite_gameinfo_bg, sprite_gameinfo_thanks, sprite_gameinfo_gameinfo, sprite_gameinfo_phaseinfo, sprite_gameinfo_cardinfo;
	// GAME-INFO Button
	Button gameinfo_thanks;
	Button gameinfo_gameinfo;
	Button gameinfo_phaseinfo;
	Button gameinfo_cardinfo;
	Button return_button;

	// GAME-CHOOSE Button
	Button button_gamechoose;
	Texture texture_gamechoose_contain;
	Sprite sprite_gamechoose_contain;

	// GAME-OVER texture & sprite
	Texture texture_gameover_bg_good, texture_gameover_bg_bad;
	Sprite sprite_gameover_bg_good, sprite_gameover_bg_bad;
	Button return_menu;

	// GAME-PAUSE button
	Button pause_button;

	// GAME-PAUSE surface
	Texture texture_gamepause_bg;
	Sprite sprite_gamepause_bg;
	Button pause_continue;
	Button pause_info;
	Button pause_return_menu;

	// Music
	Music music_bg;
	int sound_volume;


	// basic function
	// change string to lpcwstr so that string can display on warning windows
	LPCWSTR string_To_LPCWSTR(string _string);
	// load image
	void Load_Image(Texture& texture, Sprite& sprite, string filename, float originX = 0, float originY = 0, float factorX = 1, float factorY = 1);
	// load font & text
	void Load_Font(Font& font, Text& text, string filename);
	void Load_Sound(Sound& sound, SoundBuffer& soundbuffer, string filename);
	void Load_Music(Music& music, string filename);

	void Initial();
	int Previous_Draw_Phase();

	void Input_Globe();
	Vector2i Input();

	// global logic control
	void Logic();
	void Round_Initialize(int & turn);
	// human round logic
	void Human_Round_Initialize();
	int Human_Round_Skill_Judgment(Vector2i mouse_select_vector);
	void Human_Round_enable_dying_state();
	void Human_Round();
	// machine round logic
	void Machine_Round_Initialize(Player& machine);
	int Machine_Round_Skill_Judgment(Player& machine);
	void Machine_Round_enable_dying_state(Player& machine);
	void Machine_Round(Player & machine);

	void Draw();
	void Draw_Discard_Pile();
	void Draw_Text_Console();
	void Draw_HumanPlayer_Button();
	void Draw_HumanPlayer();
	void Draw_Animator_Single(int set_frame, bool& animator, int& animator_counter, string file, int limited, int _x, int _y);
	void Draw_Animator_Machine(Player& Machine);
	void Draw_Animator_Human();
	void Draw_Machine(Player& Machine);
	void Draw_Stable_Background();

	//message function
	void Insert_Message(wstring str) {
		//尾插法 新增 结点
		Message_Box S = new Message;
		S->next = NULL;
		//赋值
		S->single_message = str;
		Message_Box P = message;
		while (P->next)
			P = P->next;  // find tail node
		P->next = S;
		P = S;
		//cout << "***********yes insert message succeed!!!" << endl;
		message_amount++;
	}
	void Delete_Message() {
		Message_Box T = message;
		while (T->next) {
			Message_Box p = T->next;
			T->next = p->next;
			delete p;
			message_amount--;
			//cout << "<<<<message card succeed!!!" << endl;
			break;
		}
		return;
	}

	Game();
};
