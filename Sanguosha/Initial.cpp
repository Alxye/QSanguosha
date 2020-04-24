#include "Game.h"

Game::Game() {
	window_width = 1035;
	window_height = 770;
	virtual_vector.x = -999;
	virtual_vector.y = -999;
	human_defense = false;
	animator_running = false;
	window.create(sf::VideoMode(window_width, window_height), L"Èý¹úÉ±_BY_ÕÔÜçÜç");
}
void Game::Initial() {
	// initialize game state
	gamestart = true;
	gameover = false;
	gamequit = false;
	new_round = true;
	// initialize round state
	Machine.round_draw_phase = false;
	Human.round_draw_phase = false;
	// extra turn initialize
	exturn = normal;
	exturn_backup = exturn;
	// get cards shuffled
	piles.Shuffle_Card();
	Load_Image(texture_background, sprite_background, "image/back_stable/background.jpg", 0, 0, 1, 1); // ¼ÓÔØ±³¾°
	Load_Image(texture_player_equip_board, sprite_player_equip_board, "image/back_stable/playerboard-equip.png");
	Load_Image(texture_player_hand_board, sprite_player_hand_board, "image/back_stable/playerboard-hand.png");
	Load_Image(texture_player_button_background, sprite_player_button_background, "image/back_stable/playerbutton_background.png");
	Load_Image(texture_npcboard, sprite_npcboard, "image/back_stable/npcboard.png");
	Load_Image(texture_npc_cards, sprite_npc_cards, "image/back_stable/handcard.png");
	Load_Image(texture_player_role_background, sprite_player_role_background, "image/back_stable/playerboard-role.png");
	Load_Image(texture_piles_back, sprite_piles_back, "image/back_stable/pile_back.png");
	// load npc_being chosen
	Load_Image(texture_being_chosen, sprite_being_chosen, "image/back_stable/sos.png", 0, 0, 1, 1);
	// load button 
	//---->> cancel button
	Load_Image(button_cancel.texture_disabled, button_cancel.sprite_disabled, "image/back_stable/button/cancel-disabled.png", 0, 0, 1, 1);
	Load_Image(button_cancel.texture_down, button_cancel.sprite_down, "image/back_stable/button/cancel-down.png", 0, 0, 1, 1);
	Load_Image(button_cancel.texture_hover, button_cancel.sprite_hover, "image/back_stable/button/cancel-hover.png", 0, 0, 1, 1);
	Load_Image(button_cancel.texture_normal, button_cancel.sprite_normal, "image/back_stable/button/cancel-normal.png", 0, 0, 1, 1);
	//---->> discard button
	Load_Image(button_discard.texture_disabled, button_discard.sprite_disabled, "image/back_stable/button/discard-disabled.png", 0, 0, 1, 1);
	Load_Image(button_discard.texture_down, button_discard.sprite_down, "image/back_stable/button/discard-down.png", 0, 0, 1, 1);
	Load_Image(button_discard.texture_hover, button_discard.sprite_hover, "image/back_stable/button/discard-hover.png", 0, 0, 1, 1);
	Load_Image(button_discard.texture_normal, button_discard.sprite_normal, "image/back_stable/button/discard-normal.png", 0, 0, 1, 1);
	//---->> assure button
	Load_Image(button_ok.texture_disabled, button_ok.sprite_disabled, "image/back_stable/button/ok-disabled.png", 0, 0, 1, 1);
	Load_Image(button_ok.texture_down, button_ok.sprite_down, "image/back_stable/button/ok-down.png", 0, 0, 1, 1);
	Load_Image(button_ok.texture_hover, button_ok.sprite_hover, "image/back_stable/button/ok-hover.png", 0, 0, 1, 1);
	Load_Image(button_ok.texture_normal, button_ok.sprite_normal, "image/back_stable/button/ok-normal.png", 0, 0, 1, 1);
	//---->> Human & Machine Player HP
	Load_Image(texture_Human_HP, sprite_Human_HP, "image/HP/green_big.png", 0, 0, 1, 1);
	Load_Image(texture_Machine_HP, sprite_Machine_HP, "image/HP/green_small.png", 0, 0, 1, 1);
	//---->> Human's dying state saving me
	Load_Image(texture_Human_save_me, sprite_Human_save_me, "image/gameover/save-me.png", 0, 0, 1, 1);
	turn = Previous_Draw_Phase();            // first round is effected in initial function , then it goes a loop
	exturn = 0; // where exturn=0 that mean normal 

	Human.HP = 5;
	Human.limited_HP = 5;
}


// change string to lpcwstr so that string can display on warning windows
LPCWSTR Game::string_To_LPCWSTR(string _string) {
	size_t origsize = _string.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* _LPCWSTR = (wchar_t*)malloc(sizeof(wchar_t) * (_string.length() - 1));
	mbstowcs_s(&convertedChars, _LPCWSTR, origsize, _string.c_str(), _TRUNCATE);
	return _LPCWSTR;
}
// load image
void Game::Load_Image(Texture& texture, Sprite& sprite, string filename, float originX, float originY, float factorX, float factorY) {
	if (!texture.loadFromFile(filename)) {
		int result = MessageBox(NULL, string_To_LPCWSTR("Invalid Path , image is missing : " + filename), TEXT("Error ! Failed to load !"), MB_RETRYCANCEL);
		switch (result) {
		case IDRETRY:
			return Load_Image(texture, sprite, filename, originX, originY, factorX, factorY);
		case IDCANCEL:
			exit(0);
		}
	}
	else {
		cout << "ÌùÍ¼¼ÓÔØ³É¹¦" << endl;
		sprite.setTexture(texture);
		sprite.setOrigin(originX, originY);
		sprite.setScale(factorX, factorY);
	}
}
// for test to printout
void Game::out_put(Single_Card single) {
	cout << "³öµÄ¿¨ÅÆ£º" << single.card_name << endl;
	cout << "¿¨ÅÆºÅÂë£º" << single.card_info.single_card_number << endl;
	cout << "¿¨ÅÆ»¨É«£º" << single.card_name << endl;
	cout << "¿¨ÅÆÄÜ·ñ¹¥»÷£º" << single.card_info.can_attck << endl;
}
// load font & text

void Game::Load_Font(Font& font, Text& text, string filename) {
	if (!font.loadFromFile(filename)) {
		int result = MessageBox(NULL, string_To_LPCWSTR("Invalid Path , font is missing : " + filename), TEXT("Error ! Failed to load !"), MB_RETRYCANCEL);
		switch (result) {
		case IDRETRY:
			return Load_Font(font, text, filename);
		case IDCANCEL:
			exit(0);
		}
	}
	else {
		cout << "×ÖÌå¼ÓÔØ³É¹¦" << endl;
		text.setFont(font);
	}
}