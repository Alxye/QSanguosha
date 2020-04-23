#pragma once
#include "core.h"

class Game
{
public:
	RenderWindow window;
	int window_width, window_height;
	int turn;                             // 轮到谁的 记录量
	bool gamestart, gameover, gamequit;
	bool new_round;
	bool human_defense;                   // bool to see its turn to human defense
	bool animator_running;                // judge animator is running ,so that machine play wont play so fast
	Vector2i virtual_vector;
	Event event_global;
	Pile_Card piles;
	Player Human, Machine;
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
	// Game Class
	void out_put(Single_Card& single);

	// basic function
	// change string to lpcwstr so that string can display on warning windows
	LPCWSTR string_To_LPCWSTR(string _string);
	// load image
	void Load_Image(Texture& texture, Sprite& sprite, string filename, float originX = 0, float originY = 0, float factorX = 1, float factorY = 1);
	// load font & text
	void Load_Font(Font& font, Text& text, string filename);

	void Initial();

	Vector2i Input();

	void Logic();
	int Previous_Draw_Phase();
	void Round_Initialize(int turn);
	void Human_Round_Initialize();
	void Human_Round_Skill_Judgment(Vector2i mouse_select_vector);
	void Human_Round();
	void Machine_Round_Initialize();
	void Machine_Round_Skill_Judgment();

	void Machine_Round();

	void Draw();
	void Draw_HumanPlayer_Button();
	void Draw_HumanPlayer();
	void Draw_Animator_Single(int set_frame, bool& animator, int& animator_counter, string file, int limited, int _x, int _y);
	void Draw_Animator();
	void Draw_Machine();
	void Draw_Stable_Background();
	Game();
};
