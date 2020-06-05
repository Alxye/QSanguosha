#include "Game.h"

void Game::Draw() {
	Draw_Stable_Background();
	Draw_HumanPlayer();
	for (int number=0; number < 4; number++) {
		Draw_Machine(Machine[number]);
		Draw_Animator_Machine(Machine[number]);
	}
	Draw_Animator_Human();
	window.display();
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

	if (Human.is_dying==true&&Human.die==false){
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
		window.setFramerateLimit(30);
	}
}

void Game::Draw_Animator_Machine(Player & Machine) {
	if (Machine.animator_kill) { Draw_Animator_Single(16, Machine.animator_kill, Machine.animator_kill_counter, "image/animator/killer/", 13, Machine.location_two.x, Machine.location_two.y); }
	else if (Machine.animator_jink) { Draw_Animator_Single(16, Machine.animator_jink, Machine.animator_jink_counter, "image/animator/jink/", 12, Machine.location_two.x, Machine.location_two.y); }
	else if (Machine.animator_peach) { Draw_Animator_Single(16, Machine.animator_peach, Machine.animator_peach_counter, "image/animator/peach/", 17, Machine.location_two.x, Machine.location_two.y); }
	else if (Machine.animator_analeptic) { Draw_Animator_Single(16, Machine.animator_analeptic, Machine.animator_analeptic_counter, "image/animator/analeptic/", 17, Machine.location_two.x, Machine.location_two.y); }
	else if (Machine.animator_damage) { Draw_Animator_Single(22, Machine.animator_damage, Machine.animator_damage_counter, "image/animator/damage/", 6, Machine.location_one.x, Machine.location_one.y); }
}
void Game::Draw_Animator_Human() {
	if (Human.animator_kill) { Draw_Animator_Single(16, Human.animator_kill, Human.animator_kill_counter, "image/animator/killer/", 13, 500, 470); }
	else if (Human.animator_jink) { Draw_Animator_Single(16, Human.animator_jink, Human.animator_jink_counter, "image/animator/jink/", 12, 500, 470); }
	else if (Human.animator_peach) { Draw_Animator_Single(16, Human.animator_peach, Human.animator_peach_counter, "image/animator/peach/", 17, 500, 340); }
	else if (Human.animator_analeptic) { Draw_Animator_Single(16, Human.animator_analeptic, Human.animator_analeptic_counter, "image/animator/analeptic/", 17, 500, 380); }
	else if (Human.animator_damage) { Draw_Animator_Single(22, Human.animator_damage, Human.animator_damage_counter, "image/animator/damage/", 6, 910, window_height - 170); }
}
void Game::Draw_Machine(Player & Machine) {
	// draw Machine HP
	for (int i = 0; i < Machine.HP; i++) {
		sprite_Machine_HP.setPosition(Machine.location_one.x + 18 + 14 * i, Machine.location_one.y+30);  // the width of image named green small is 14
		window.draw(sprite_Machine_HP);
	}
	if (Machine.being_choose) {
		sprite_being_chosen.setPosition(Machine.location_one.x, Machine.location_one.y);  // 宽 1140 || 高 600
		window.draw(sprite_being_chosen);
	}
}
void Game::Draw_Stable_Background() {
	// draw background
	sprite_background.setPosition(0, 0);  // 宽 1140 || 高 600
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
	// draw npc info
	for (int number=0;number<4;number++)	{
		// draw npc board
		sprite_npcboard.setPosition(Machine[number].location_one.x, Machine[number].location_one.y); // 宽 143 || 高 195
		window.draw(sprite_npcboard);
		// draw npc cards board
		sprite_npc_cards.setPosition(Machine[number].location_one.x, Machine[number].location_one.y+60); // 宽 143 || 高 195
		window.draw(sprite_npc_cards);
	}
	// draw piles & cards background
	sprite_piles_back.setPosition(window_width / 3, 300); // 宽 93 || 高 130
	window.draw(sprite_piles_back);
}