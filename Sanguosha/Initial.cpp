#include "Game.h"

Game::Game() {
	window_width = 1035;
	window_height = 770;
	virtual_vector.x = -999;
	virtual_vector.y = -999;
	human_defense = false;
	animator_running = false;
	round_loop = false;
	window.create(sf::VideoMode(window_width, window_height), L"Èý¹úÉ±_BY_ÕÔÜçÜç", sf::Style::Close);
	Human.HP = 2;
	Human.limited_HP = Human.HP;
}
void Game::Initial() {
	// initialize game state
	gamestart = true;
	gameover = false;
	gamequit = false;
	new_round = true;
	// extra turn initialize
	exturn = normal;
	exturn_backup = exturn;
	// record who set signal of begging peach
	peach_begger=-1; // default no one beg for peach
	// get cards shuffled (originally)
	piles.Shuffle_Card();
	// load background
	Load_Image(texture_background, sprite_background, "image/back_stable/background.jpg", 0, 0, 1, 1);
	// load equipment background in player's interface
	Load_Image(texture_player_equip_board, sprite_player_equip_board, "image/back_stable/playerboard-equip.png");
	// load hand background in player's interface
	Load_Image(texture_player_hand_board, sprite_player_hand_board, "image/back_stable/playerboard-hand.png");
	// load button container in player's interface
	Load_Image(texture_player_button_background, sprite_player_button_background, "image/back_stable/playerbutton_background.png");
	// load player's information in player's interface
	Load_Image(texture_player_role_background, sprite_player_role_background, "image/back_stable/playerboard-role.png");
	// load npc's interface
	Load_Image(texture_npcboard, sprite_npcboard, "image/back_stable/npcboard.png");
	Load_Image(texture_npc_cards, sprite_npc_cards, "image/back_stable/handcard.png");
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
    //---->> Phase mask border for machine
	for (int number = 0; number < 4; number++) {
		Load_Image(Machine[number].texture_draw_phase, Machine[number].sprite_draw_phase, "image/phase/draw.png", 0, 0, 1, 1);
		Load_Image(Machine[number].texture_play_phase, Machine[number].sprite_play_phase, "image/phase/play.png", 0, 0, 1, 1);
		Load_Image(Machine[number].texture_discard_phase, Machine[number].sprite_discard_phase, "image/phase/discard.png", 0, 0, 1, 1);
		Load_Image(Machine[number].texture_judge_phase, Machine[number].sprite_judge_phase, "image/phase/judge.png", 0, 0, 1, 1);
		Load_Image(Machine[number].texture_response_phase, Machine[number].sprite_response_phase, "image/phase/response.png", 0, 0, 1, 1);
		Load_Image(Machine[number].texture_sos_phase, Machine[number].sprite_sos_phase, "image/phase/sos.png", 0, 0, 1, 1);
	}
	Load_Image(texture_Human_save_me, sprite_Human_save_me, "image/gameover/save-me.png", 0, 0, 1, 1);
	//---->> initialize charactor code to get catch of each member
	Human.charactor_code = human;
	Machine[0].charactor_code = machine_0;
	Machine[1].charactor_code = machine_1;
	Machine[2].charactor_code = machine_2;
	Machine[3].charactor_code = machine_3;
	//---->> initialize charactor location
	Human.location_one.x = -1;
	Human.location_one.y = -1;
	Human.location_two.x = -1;
	Human.location_two.y = -1;
	// for machine-0
	Machine[0].location_one.x = 100;
	Machine[0].location_one.y = 300;
	Machine[0].location_two.x = 242;
	Machine[0].location_two.y = 495;
	// for machine-1
	Machine[1].location_one.x = 290;
	Machine[1].location_one.y = 36;
	Machine[1].location_two.x = 432;
	Machine[1].location_two.y = 231;
	// for machine-2
	Machine[2].location_one.x = 550;
	Machine[2].location_one.y = 36;
	Machine[2].location_two.x = 692;
	Machine[2].location_two.y = 231;
	// for machine-3
	Machine[3].location_one.x = 750;
	Machine[3].location_one.y = 300;
	Machine[3].location_two.x = 892;
	Machine[3].location_two.y = 495;
	//---->> initialize pile card
	turn = Previous_Draw_Phase();            // first round is effected in initial function , then it goes a loop
	exturn = normal;                         // original set is mean normal 
	//---->> initialize killing number
	killing_number = 0;
    //---->> diable all the button
	button_ok.enable_diabled_button();
	button_discard.enable_diabled_button();
	button_cancel.enable_diabled_button();
	//---->> machine number
	machine_number = 2;                     // default is 4 yeh
}

int Game::Previous_Draw_Phase() {
	// each machine get 4 cards
	for (int number = 0; number < 4; number++) {
		for (int i = 0; i < 4; i++) {
			Machine[number].cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
			piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
		}
	}
	// human get 4 cards
	for (int i = 0; i < 4; i++) {
		Human.cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
		Human.cards.Get_Node(Human.cards.Pile_Card_Amount - 1)->mouse_select_card = false;
		piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
	}
	//return rand() % 5 +1;  // the rand function would detenmine which one to play first
	//return human;    // test for human to start whatever situation is
	return machine_0;    // test for human to start whatever situation is
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
		cout << "Image Load Successfully" << endl;
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
		cout << "Font Load Successfully" << endl;
		text.setFont(font);
	}
}