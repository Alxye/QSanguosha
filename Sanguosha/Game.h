#pragma once
#include "core.h"

class Game
{
public:
	RenderWindow window;
	int window_width, window_height;
	int turn;                             // 轮到谁的 记录量
	int exturn;
	int exturn_backup;
	bool round_loop;                      // flag to judge if a loop have been existed
	int round_loop_starter;               // mark loop starter
	bool gamestart, gameover, gamequit;
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
	int killing_number;


	// basic function
	// change string to lpcwstr so that string can display on warning windows
	LPCWSTR string_To_LPCWSTR(string _string);
	// load image
	void Load_Image(Texture& texture, Sprite& sprite, string filename, float originX = 0, float originY = 0, float factorX = 1, float factorY = 1);
	// load font & text
	void Load_Font(Font& font, Text& text, string filename);

	void Initial();
	int Previous_Draw_Phase();

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
	void Draw_HumanPlayer_Button();
	void Draw_HumanPlayer();
	void Draw_Animator_Single(int set_frame, bool& animator, int& animator_counter, string file, int limited, int _x, int _y);
	void Draw_Animator_Machine(Player& Machine);
	void Draw_Animator_Human();
	void Draw_Machine(Player& Machine);
	void Draw_Stable_Background();
	Game();
};
