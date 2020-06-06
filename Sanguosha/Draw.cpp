#include "Game.h"

void Game::Draw() {

	if (gamestart) {
        // draw background
		if (change_bg) {
			button_animate_count = 0;
			if (start_style_mode==0){
				// for background
				Load_Image(texture_gamestart_bg, sprite_gamestart_bg, "image/back_stable/start-surface/start_bg_dark.png", 0, 0, 1, 1);
				// for normal button
				Load_Image(gamestart_go.texture_normal, gamestart_go.sprite_normal, "image/back_stable/start-surface/start-light-button-go.png", 0, 0, 1, 1);
				Load_Image(gamestart_info.texture_normal, gamestart_info.sprite_normal, "image/back_stable/start-surface/start-light-button-info.png", 0, 0, 1, 1);
				Load_Image(gamestart_quit.texture_normal, gamestart_quit.sprite_normal, "image/back_stable/start-surface/start-light-button-quit.png", 0, 0, 1, 1);
				// for high light button
				Load_Image(gamestart_go.texture_hover, gamestart_go.sprite_hover, "image/back_stable/start-surface/start-dark-button-go.png", 0, 0, 1, 1);
				Load_Image(gamestart_info.texture_hover, gamestart_info.sprite_hover, "image/back_stable/start-surface/start-dark-button-info.png", 0, 0, 1, 1);
				Load_Image(gamestart_quit.texture_hover, gamestart_quit.sprite_hover, "image/back_stable/start-surface/start-dark-button-quit.png", 0, 0, 1, 1);
				start_style_mode = 1;
			}
			else if (start_style_mode == 1) {
				// for background
				Load_Image(texture_gamestart_bg, sprite_gamestart_bg, "image/back_stable/start-surface/start_bg_light.png", 0, 0, 1, 1);
				// for normal button
				Load_Image(gamestart_go.texture_normal, gamestart_go.sprite_normal, "image/back_stable/start-surface/start-dark-button-go.png", 0, 0, 1, 1);
				Load_Image(gamestart_info.texture_normal, gamestart_info.sprite_normal, "image/back_stable/start-surface/start-dark-button-info.png", 0, 0, 1, 1);
				Load_Image(gamestart_quit.texture_normal, gamestart_quit.sprite_normal, "image/back_stable/start-surface/start-dark-button-quit.png", 0, 0, 1, 1);
				// for high light button
				Load_Image(gamestart_go.texture_hover, gamestart_go.sprite_hover, "image/back_stable/start-surface/start-light-button-go.png", 0, 0, 1, 1);
				Load_Image(gamestart_info.texture_hover, gamestart_info.sprite_hover, "image/back_stable/start-surface/start-light-button-info.png", 0, 0, 1, 1);
				Load_Image(gamestart_quit.texture_hover, gamestart_quit.sprite_hover, "image/back_stable/start-surface/start-light-button-quit.png", 0, 0, 1, 1);
				start_style_mode = 0;
			}
			change_bg = false;
		}

		sprite_gamestart_bg.setPosition(0, 0);
		window.draw(sprite_gamestart_bg);
		if (button_animate_count < 81) {
			window.setFramerateLimit(200);
			if(gamestart_go.is_hover)	gamestart_go.sprite_hover.setTextureRect(IntRect(0, 0, 80, button_animate_count * 5));
			if (gamestart_info.is_hover)gamestart_info.sprite_hover.setTextureRect(IntRect(0, 0, 80, button_animate_count * 5));
			if (gamestart_quit.is_hover)gamestart_quit.sprite_hover.setTextureRect(IntRect(0, 0, 80, button_animate_count * 5));
			button_animate_count++;
			if (button_animate_count == 81)
				window.setFramerateLimit(300);
		}
		/// for start go button
		gamestart_go.sprite_normal.setPosition(570, 50);
		window.draw(gamestart_go.sprite_normal);
		if (gamestart_go.is_hover) {
			gamestart_go.sprite_hover.setPosition(570, 50);
			window.draw(gamestart_go.sprite_hover);
		}
		else if (gamestart_go.is_down) {
			gamestart_go.sprite_down.setPosition(570, 50);
			window.draw(gamestart_go.sprite_down);
		}
		/// for start info button
		gamestart_info.sprite_normal.setPosition(470, 90);
		window.draw(gamestart_info.sprite_normal);
		if (gamestart_info.is_hover) {
			gamestart_info.sprite_hover.setPosition(470, 90);
			window.draw(gamestart_info.sprite_hover);
		}
		else if (gamestart_info.is_down) {
			gamestart_info.sprite_down.setPosition(470, 90);
			window.draw(gamestart_info.sprite_down);
		}
		/// for start quit button
		gamestart_quit.sprite_normal.setPosition(370, 130);
		window.draw(gamestart_quit.sprite_normal);
		if (gamestart_quit.is_hover) {
			gamestart_quit.sprite_hover.setPosition(370, 130);
			window.draw(gamestart_quit.sprite_hover);
		}
		else if (gamestart_quit.is_down) {
			gamestart_quit.sprite_down.setPosition(370, 130);
			window.draw(gamestart_quit.sprite_down);
		}
	}

	if (gamechoose) {

	}

	if (gamepause) {

	}

	if (gameover) {

	}

	if (gamerun) {
		// draw stable part
		Draw_Stable_Background();

		// draw text console
		Draw_Text_Console();

		// draw discard pile
		Draw_Discard_Pile();

		// draw human part
		Draw_HumanPlayer();
		Draw_Animator_Human();

		//draw machine part
		for (int number = 0; number < machine_number; number++) {

			Draw_Machine(Machine[number]);
			Draw_Animator_Machine(Machine[number]);
		}
	}

	window.display();
}

void Game::Draw_Text_Console() {
	RectangleShape rect(Vector2f(330,230)); // draw rectangle
	rect.setFillColor(Color(0, 0, 0, 100));
	rect.setPosition(700, 60);
	window.draw(rect);
	// when message amount is out of 15 ,then delete previous message in case the latest message is overflow
	while (message_amount > 15) {
		Delete_Message();
	}
	// show each message in message box
	Message_Box ptr = message->next;
	int dx = 0;
	while (ptr) {
		Font text_font;
		Text text;
		Load_Font(text_font, text, "font/simsun.ttc");
		text.setCharacterSize(15);
		text.setFillColor(Color(255, 255, 255, 255));
		text.setStyle(Text::Bold);
		text.setPosition(705, 60+dx*15);
		wstring each_line = L"";
		each_line = each_line + ptr->single_message;
		text.setString(each_line);
		window.draw(text);
		dx++;
		ptr = ptr->next;
	}
}

void Game::Draw_Discard_Pile() {
	Single_Card* ptr = discard_pile.Pile_Card_Total->next;
	int start_draw = 1;
	if (discard_pile.Pile_Card_Amount - start_draw > 6) {
		Load_Image(texture_discard_pile, sprite_discard_pile, "image/back_stable/pile_back.png");
		sprite_discard_pile.setPosition(window_width / 2, 300);
		window.draw(sprite_discard_pile);
	}
	while (discard_pile.Pile_Card_Amount - start_draw > 6) {
		start_draw++;
		ptr = ptr->next;
	}
	int dx = 1;
	while (ptr) {
		switch (ptr->card_info.single_card_number)
		{
		case kill:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/0.jpg");
			break;
		case jink:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/1.jpg");
			break;
		case analeptic:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/2.jpg");
			break;
		case peach:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/3.jpg");
			break;
		default:
			break;
		}
		sprite_discard_pile.setPosition(window_width / 2 + dx * 15, 300);
		window.draw(sprite_discard_pile);
		dx++;
		ptr = ptr->next;
	}
}

void Game::Draw_HumanPlayer_Button() {
	//--->> judge which kind of state of button
	if (button_cancel.is_disabled) {
		button_cancel.sprite_disabled.setPosition(807, 694);
		window.draw(button_cancel.sprite_disabled);
	}
	else if (button_cancel.is_hover) {
		button_cancel.sprite_hover.setPosition(807, 694);
		window.draw(button_cancel.sprite_hover);
	}
	else if (button_cancel.is_down) {
		button_cancel.sprite_down.setPosition(807, 694);
		window.draw(button_cancel.sprite_down);
	}
	else if (button_cancel.is_normal) {
		button_cancel.sprite_normal.setPosition(807, 694);
		window.draw(button_cancel.sprite_normal);
	}
	if (button_discard.is_disabled) {
		button_discard.sprite_disabled.setPosition(874, 644);
		window.draw(button_discard.sprite_disabled);
	}
	else if (button_discard.is_hover) {
		button_discard.sprite_hover.setPosition(874, 644);
		window.draw(button_discard.sprite_hover);
	}
	else if (button_discard.is_down) {
		button_discard.sprite_down.setPosition(874, 644);
		window.draw(button_discard.sprite_down);
	}
	else if (button_discard.is_normal) {
		button_discard.sprite_normal.setPosition(874, 644);
		window.draw(button_discard.sprite_normal);
	}
	if (button_ok.is_disabled) {
		button_ok.sprite_disabled.setPosition(807, 604);
		window.draw(button_ok.sprite_disabled);
	}
	else if (button_ok.is_hover) {
		button_ok.sprite_hover.setPosition(807, 604);
		window.draw(button_ok.sprite_hover);
	}
	else if (button_ok.is_down) {
		button_ok.sprite_down.setPosition(807, 604);
		window.draw(button_ok.sprite_down);
	}
	else if (button_ok.is_normal) {
		button_ok.sprite_normal.setPosition(807, 604);
		window.draw(button_ok.sprite_normal);
	}
}
void Game::Draw_HumanPlayer() {
	// draw human_player_card
	Single_Card* ptr = Human.cards.Pile_Card_Total->next;
	for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {  // each card:  width 93 || height 130
		if (ptr->mouse_select_card) {
			ptr->point_one.x = 165 + i * 93;
			ptr->point_one.y = window_height - 170;
			ptr->point_two.x = 165 + (i + 1) * 93;
			ptr->point_two.y = window_height - 170 + 130;
			ptr->sprite_card.setPosition(ptr->point_one.x, ptr->point_one.y);
			window.draw(ptr->sprite_card);
		}
		else if (ptr->enable_to_play == false) {
			ptr->point_one.x = 165 + i * 93;
			ptr->point_one.y = window_height - 135;
			ptr->point_two.x = 165 + (i + 1) * 93;
			ptr->point_two.y = window_height - 135 + 130;
			ptr->sprite_card.setPosition(ptr->point_one.x, ptr->point_one.y);
			window.draw(ptr->sprite_card);

			RectangleShape rect(Vector2f(93, 130)); // draw rectangle
			rect.setFillColor(Color(0, 0, 0, 100));
			rect.setPosition(ptr->point_one.x, ptr->point_one.y);
			window.draw(rect);
		}
		else {
			ptr->point_one.x = 165 + i * 93;
			ptr->point_one.y = window_height - 135;
			ptr->point_two.x = 165 + (i + 1) * 93;
			ptr->point_two.y = window_height - 135 + 130;
			ptr->sprite_card.setPosition(ptr->point_one.x, ptr->point_one.y);
			window.draw(ptr->sprite_card);
		}
		//window.draw(ptr->sprite_card);
		ptr = ptr->next;
	}
	Draw_HumanPlayer_Button();
	// draw Human HP
	for (int i = 0; i < Human.HP; i++) {
		sprite_Human_HP.setPosition(918 + i * 22, window_height - 166);  // the width of image named green big is 23
		window.draw(sprite_Human_HP);
	}
	// draw remained note
	if (Human.round_discard_phase) {
		if (Human.cards.Pile_Card_Amount - Human.HP > Human.selecet_card_amount) {

			RectangleShape rect(Vector2f(180, 30)); // draw rectangle
			rect.setFillColor(Color(0, 0, 0, 100));
			rect.setPosition(370, 500);
			window.draw(rect);

			Font reminded_note_font;
			Text reminded_note;
			Load_Font(reminded_note_font, reminded_note, "font/simsun.ttc");
			reminded_note.setCharacterSize(20);
			reminded_note.setFillColor(Color(255, 255, 255, 255));
			reminded_note.setStyle(Text::Bold);
			reminded_note.setPosition(370, 500);
			wstring reminded = L"请弃置";
			std::stringstream temp_string;
			temp_string << Human.cards.Pile_Card_Amount - Human.HP;
			reminded = reminded + temp_string.str() + L"张牌";

			reminded_note.setString(reminded);
			window.draw(reminded_note);
		}
	}
	// draw dying state

	if (Human.is_dying == true && Human.die == false) {
		sprite_Human_save_me.setPosition(500, 530);
		window.draw(sprite_Human_save_me);
	}
}
void Game::Draw_Animator_Single(int set_frame, bool& animator, int& animator_counter, string file, int limited, int _x, int _y) {
	window.setFramerateLimit(set_frame);
	Texture texture_temp;
	Sprite sprite_temp;
	stringstream ss;
	ss << file << animator_counter << ".png";
	Load_Image(texture_temp, sprite_temp, ss.str(), 0, 0, 1, 1);
	sprite_temp.setPosition(_x, _y);
	animator_counter++;
	window.draw(sprite_temp);
	if (animator_counter == limited) {
		animator = false;
		animator_running = false;
		//Sleep(500);
		window.setFramerateLimit(30);
	}
}

void Game::Draw_Animator_Machine(Player& Machine) {
	if (Machine.animator_kill) { Draw_Animator_Single(16, Machine.animator_kill, Machine.animator_kill_counter, "image/animator/killer/", 13, Machine.location_two.x, Machine.location_two.y); }
	else if (Machine.animator_jink) { Draw_Animator_Single(16, Machine.animator_jink, Machine.animator_jink_counter, "image/animator/jink/", 12, Machine.location_two.x, Machine.location_two.y); }
	else if (Machine.animator_peach) { Draw_Animator_Single(16, Machine.animator_peach, Machine.animator_peach_counter, "image/animator/peach/", 17, Machine.location_two.x - 150, Machine.location_two.y - 50); }
	else if (Machine.animator_analeptic) { Draw_Animator_Single(16, Machine.animator_analeptic, Machine.animator_analeptic_counter, "image/animator/analeptic/", 17, Machine.location_two.x - 150, Machine.location_two.y - 50); }
	else if (Machine.animator_damage) { Draw_Animator_Single(22, Machine.animator_damage, Machine.animator_damage_counter, "image/animator/damage/", 6, Machine.location_one.x, Machine.location_one.y); }
}
void Game::Draw_Animator_Human() {
	if (Human.animator_kill) { Draw_Animator_Single(16, Human.animator_kill, Human.animator_kill_counter, "image/animator/killer/", 13, 500, 470); }
	else if (Human.animator_jink) { Draw_Animator_Single(16, Human.animator_jink, Human.animator_jink_counter, "image/animator/jink/", 12, 500, 470); }
	else if (Human.animator_peach) { Draw_Animator_Single(16, Human.animator_peach, Human.animator_peach_counter, "image/animator/peach/", 17, 500, 340); }
	else if (Human.animator_analeptic) { Draw_Animator_Single(16, Human.animator_analeptic, Human.animator_analeptic_counter, "image/animator/analeptic/", 17, 500, 380); }
	else if (Human.animator_damage) { Draw_Animator_Single(22, Human.animator_damage, Human.animator_damage_counter, "image/animator/damage/", 6, 910, window_height - 170); }
}
void Game::Draw_Machine(Player& Machine) {
	// draw Machine backboard & info
	sprite_npcboard.setPosition(Machine.location_one.x, Machine.location_one.y); // 宽 143 || 高 195
	window.draw(sprite_npcboard);
	// draw npc cards board
	sprite_npc_cards.setPosition(Machine.location_one.x, Machine.location_one.y + 60); // 宽 143 || 高 195
	window.draw(sprite_npc_cards);

	// draw npc card-number
	Font reminded_note_font;
	Text reminded_note;
	Load_Font(reminded_note_font, reminded_note, "font/simsun.ttc");
	reminded_note.setCharacterSize(20);
	reminded_note.setFillColor(Color(0, 0, 0, 255));
	reminded_note.setStyle(Text::Bold);
	reminded_note.setPosition(Machine.location_one.x + 5, Machine.location_one.y + 60);
	wstring reminded;
	std::stringstream temp_string;
	temp_string << Machine.cards.Pile_Card_Amount;
	reminded = reminded + temp_string.str();

	reminded_note.setString(reminded);
	window.draw(reminded_note);

	// draw Machine HP
	for (int i = 0; i < Machine.HP; i++) {
		sprite_Machine_HP.setPosition(Machine.location_one.x + 18 + 14 * i, Machine.location_one.y + 30);  // the width of image named green small is 14
		window.draw(sprite_Machine_HP);
	}

	if (Machine.being_choose) {
		sprite_being_chosen.setPosition(Machine.location_one.x, Machine.location_one.y);  // 宽 1140 || 高 600
		window.draw(sprite_being_chosen);
	}
	// draw machine round state
	if (Machine.round_draw_phase) {
		Machine.sprite_draw_phase.setPosition(Machine.location_two.x - 25, Machine.location_one.y);  // 宽 1140 || 高 600
		window.draw(Machine.sprite_draw_phase);
	}
	else if (Machine.round_play_phase) {
		Machine.sprite_play_phase.setPosition(Machine.location_two.x - 25, Machine.location_one.y);  // 宽 1140 || 高 600
		window.draw(Machine.sprite_play_phase);
	}
	else if (Machine.round_discard_phase) {
		Machine.sprite_discard_phase.setPosition(Machine.location_two.x - 25, Machine.location_one.y);  // 宽 1140 || 高 600
		window.draw(Machine.sprite_discard_phase);
	}
	else if (Machine.is_dying) {
		Machine.sprite_sos_phase.setPosition(Machine.location_two.x - 25, Machine.location_one.y);  // 宽 1140 || 高 600
		window.draw(Machine.sprite_sos_phase);
	}
	else if (exturn == Machine.charactor_code) {
		Machine.sprite_response_phase.setPosition(Machine.location_two.x - 25, Machine.location_one.y);  // 宽 1140 || 高 600
		window.draw(Machine.sprite_response_phase);
	}
}
void Game::Draw_Stable_Background() {
	// draw background
	if (change_bg) {
		stringstream ss;
		ss << "image/back_stable/background-cover" << img_bg_number << ".jpg";
		Load_Image(texture_background, sprite_background, ss.str(), 0, 0, 1, 1);
		change_bg = false;
	}
	sprite_background.setPosition(0, 0);  // 宽 1140 || 高 770
	window.draw(sprite_background);
	// draw player equipment board
	sprite_player_equip_board.setPosition(0, window_height - 170);//宽 164 || 高 170
	window.draw(sprite_player_equip_board);
	// draw player hand-cards board
	sprite_player_hand_board.setPosition(164, window_height - 170);//宽 764 || 高 170
	window.draw(sprite_player_hand_board);
	// draw player button background
	sprite_player_button_background.setPosition(804, window_height - 168);//宽 106 || 高 168
	window.draw(sprite_player_button_background);
	// draw player general & role board
	sprite_player_role_background.setPosition(910, window_height - 170); // 宽 125 || 高 170
	window.draw(sprite_player_role_background);

	// draw piles & cards background
	sprite_piles_back.setPosition(window_width / 3, 300); // 宽 93 || 高 130
	window.draw(sprite_piles_back);

	// draw killing enemy note
	RectangleShape rect(Vector2f(140, 30)); // draw rectangle
	rect.setFillColor(Color(0, 0, 0, 100));
	rect.setPosition(800, 20);
	window.draw(rect);

	Font reminded_note_font;
	Text reminded_note;
	Load_Font(reminded_note_font, reminded_note, "font/simsun.ttc");
	reminded_note.setCharacterSize(20);
	reminded_note.setFillColor(Color(255, 255, 255, 255));
	reminded_note.setStyle(Text::Bold);
	reminded_note.setPosition(810, 20);
	wstring reminded = L"已杀敌：";
	std::stringstream temp_string;
	temp_string << killing_number;
	reminded = reminded + temp_string.str() ;

	reminded_note.setString(reminded);
	window.draw(reminded_note);
}