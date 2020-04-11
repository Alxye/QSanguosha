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
	void Initial() {
		// initialize game state
		gamestart = true;
		gameover = false;
		gamequit = false;
		new_round = true;
		// initialize round state
		Machine.round_draw_phase = false;
		Human.round_draw_phase = false;
		// get cards shuffled
		piles.Shuffle_Card();
		Load_Image(texture_background, sprite_background, "image/back_stable/background.jpg", 0, 0, 1, 1); // 加载背景
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
		Load_Image(button_cancel.texture_disabled,button_cancel.sprite_disabled, "image/back_stable/button/cancel-disabled.png", 0, 0, 1, 1);
		Load_Image(button_cancel.texture_down,button_cancel.sprite_down, "image/back_stable/button/cancel-down.png", 0, 0, 1, 1);
		Load_Image(button_cancel.texture_hover,button_cancel.sprite_hover, "image/back_stable/button/cancel-hover.png", 0, 0, 1, 1);
		Load_Image(button_cancel.texture_normal,button_cancel.sprite_normal, "image/back_stable/button/cancel-normal.png", 0, 0, 1, 1);
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

		turn = Previous_Draw_Phase();            // first round is effected in initial function , then it goes a loop
	}

	Vector2i Input() {
		//Event event_global;
		while (window.pollEvent(event_global)) {
			if (event_global.type == Event::Closed) {
				window.close();
				gamequit = true;
			}
			if (Human.round_play_phase){
				if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
					mouse_count_clock_two = Mouse::getPosition(window);
					if (mouse_click_timer.getElapsedTime().asMilliseconds() < 500 && mouse_count_clock_two.x - mouse_count_clock_one.x < 10 && mouse_count_clock_two.y - mouse_count_clock_one.y < 10) {
						cout << "Mouse::Left double click" << endl;
						cout << mouse_count_clock_two.x << " || " << mouse_count_clock_two.y<<endl;
						return mouse_count_clock_two;
					}
					else if (mouse_count_clock_two.x > 807 && mouse_count_clock_two.x < (807 + 61) && mouse_count_clock_two.y > 604 && mouse_count_clock_two.y < (604 + 75)&&!button_ok.is_disabled)
					{ // the button of ok //(807, 604)++(61,75)
						button_ok.enable_down_button();
						cout << "鼠标按下确定" << endl;
					}
					else if (mouse_count_clock_two.x > 807 && mouse_count_clock_two.x < (807 + 61) && mouse_count_clock_two.y > 694 && mouse_count_clock_two.y < (694 + 73)&&!button_cancel.is_disabled)
					{ // the button of cancel //(807, 604)++(61,75)  
						button_cancel.enable_down_button();
						cout << "鼠标按下取消" << endl;
					}
					else if (mouse_count_clock_two.x > 874 && mouse_count_clock_two.x < (874 + 33) && mouse_count_clock_two.y > 644 && mouse_count_clock_two.y < (644 + 81) && !button_discard.is_disabled)
					{ // the button of discard //(807, 604)++(61,75)  
						button_discard.enable_down_button();
						cout << "鼠标按下结束" << endl;
					}

				}
				if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
					mouse_count_clock_one = Mouse::getPosition(window);
					//bool card_selected = Human.cards.Search_Card_Position(mouse_count_clock_one);
					mouse_click_timer.restart();
					cout << "Mouse::Left Release" << endl;
					cout << " released:mouse_two:" << mouse_count_clock_two.x << " || " << mouse_count_clock_two.y << endl;
					cout <<" released:mouse_one:" <<mouse_count_clock_one.x << " || " << mouse_count_clock_one.y << endl;
					if (button_ok.is_down) button_ok.enable_normal_button();
					if (button_cancel.is_down) button_cancel.enable_normal_button();
					if (button_discard.is_down) button_discard.enable_normal_button();
					return mouse_count_clock_one;
				}
				
				if (event_global.type == sf::Event::MouseMoved)
				{
					// control button of cancel in hover state
					if (!button_cancel.is_disabled) {
						if (event_global.mouseMove.x > 807 && event_global.mouseMove.x < (807 + 61) && event_global.mouseMove.y > 694 && event_global.mouseMove.y < (694 + 73))
						{ // the button of cancel //(807, 694)++(61,73)
							cout << "new mouse x: " << event_global.mouseMove.x << endl;
							cout << "new mouse y: " << event_global.mouseMove.y << endl;
							button_cancel.enable_hover_button();
							cout << "鼠标位于取消上" << endl;
						}
						else{
							cout << "new mouse x: " << event_global.mouseMove.x << endl;
							cout << "new mouse y: " << event_global.mouseMove.y << endl;
							button_cancel.enable_normal_button();
							cout << "鼠标不在取消上" << endl;
						}
					}
					// control button of assure
					if (!button_ok.is_disabled) {
						if (event_global.mouseMove.x > 807 && event_global.mouseMove.x < (807 + 61) && event_global.mouseMove.y > 604 && event_global.mouseMove.y < (604 + 75))
						{ // the button of ok //(807, 604)++(61,75)
							cout << "new mouse x: " << event_global.mouseMove.x << endl;
							cout << "new mouse y: " << event_global.mouseMove.y << endl;
							button_ok.enable_hover_button();
							cout << "鼠标位于确定上" << endl;
							//return virtual_vector;
						}
						else{
							cout << "new mouse x: " << event_global.mouseMove.x << endl;
							cout << "new mouse y: " << event_global.mouseMove.y << endl;
							button_ok.enable_normal_button();
							cout << "鼠标不在确定上" << endl;
						}
					}
					// control button of discard in hover state
					if (!button_discard.is_disabled) {
						if (event_global.mouseMove.x > 874 && event_global.mouseMove.x < (874 + 33) && event_global.mouseMove.y > 644 && event_global.mouseMove.y < (644 + 81))
						{ // the button of ok //(874, 644)++(33,81)
							cout << "new mouse x: " << event_global.mouseMove.x << endl;
							cout << "new mouse y: " << event_global.mouseMove.y << endl;
							button_discard.enable_hover_button();
							cout << "鼠标位于结束上" << endl;
						}
						else{
							cout << "new mouse x: " << event_global.mouseMove.x << endl;
							cout << "new mouse y: " << event_global.mouseMove.y << endl;
							button_discard.enable_normal_button();
							cout << "鼠标不在结束上" << endl;
						}
					}
				}
			}
			
			if (Human.round_discard_phase) {
				if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
					mouse_count_clock_two = Mouse::getPosition(window);
					if (mouse_click_timer.getElapsedTime().asMilliseconds() < 500 && mouse_count_clock_two.x - mouse_count_clock_one.x < 10 && mouse_count_clock_two.y - mouse_count_clock_one.y < 10) {
						cout << "Mouse::Left double click" << endl;
						cout << mouse_count_clock_two.x << " || " << mouse_count_clock_two.y << endl;
						return mouse_count_clock_two;
					}
					else if (mouse_count_clock_two.x > 807 && mouse_count_clock_two.x < (807 + 61) && mouse_count_clock_two.y > 604 && mouse_count_clock_two.y < (604 + 75) && !button_ok.is_disabled)
					{ // the button of ok //(807, 604)++(61,75)
						button_ok.enable_down_button();
						cout << "鼠标按下确定" << endl;
					}

				}
				if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
					return Mouse::getPosition(window);
				}
			
			}
		}
	}

	int Previous_Draw_Phase() {
		// machine get 4 cards
		for (int i = 0; i < 4; i++) {
			Machine.cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
			piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
		}
		// human get 4 cards
		for (int i = 0; i < 4; i++) {
			Human.cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
			Human.cards.Get_Node(Human.cards.Pile_Card_Amount - 1)->mouse_select_card = false;
			piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
		}
		//return rand() % 2;  // the rand function would detenmine which one to play first
		return 1;
	}
	void Round_Initialize(int turn) { // about turn :  0——machine || 1——Human player
		if (turn == 0) {  // machine's round
			Machine.round_draw_phase = true;
		}
		else if (turn == 1) { // humans round
			Human.round_draw_phase = true;
			Human.round_play_phase = true;
		}
		new_round = false;
	}
	void Human_Round() {
		Vector2i mouse_select_vector = Input();  // in general there only exist one input function  * wtf! that is matter most
		if (piles.Pile_Card_Amount < 20) piles.Shuffle_Card(); // if card few ,shuffle

		if (Human.skill.need_peach) {
			if (Human.HP < Human.limited_HP) Human.HP++;
			Human.skill.need_peach = false;
		}
		if (Human.skill.need_analeptic)	{
			//if (Human.is_dying) { Human.HP++;}
			Human.kill_power++;
		}
		if (Human.is_dying==true){ // when player is dying , begging for peach
			Machine.skill.begging_peach = true;
		}

		// human get 2 cards each time is its round
		if (Human.round_draw_phase) {
			for (int i = 0; i < 2; i++) {
				Human.cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
				Human.cards.Get_Node(Human.cards.Pile_Card_Amount - 1)->mouse_select_card = false;
				piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
			}
			Human.round_draw_phase = false;
		}
		// to update player's card with card_texture,card_sprite,card_vector;
		Single_Card* ptr = Human.cards.Pile_Card_Total->next;
		for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
			if (!ptr->file_loaded) {
				stringstream ss;
				ss << "image/skill&equip_card/small_card/" << ptr->card_info.single_card_number << ".jpg";
				Load_Image(ptr->texture_card, ptr->sprite_card, ss.str(), 0, 0, 1, 1);
				ptr->file_loaded = true;
			}
			ptr = ptr->next;
		}
		// Human play card
		if (Human.round_play_phase) {
			// button stage initialize
			if ((Human.select_card == false)&&!(button_discard.is_hover||button_discard.is_down)){ // there exist tow kind of situation -- original initialize and no hover & no down
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				button_discard.enable_normal_button();
			}
			if (Human.cards.Search_Card_Position(mouse_select_vector)){        //play choose cards ,only once each time   also  it can change button state according to card attribute
				Single_Card* ptr = nullptr;
				ptr = Human.cards.Search_Card_Position_locate(mouse_select_vector);
				if (ptr->mouse_select_card==false&&Human.select_card==false) {
					ptr->mouse_select_card = true;
					Human.select_card = true;
					if (ptr->card_info.can_attck){
						button_ok.enable_diabled_button();
						button_cancel.enable_normal_button();
						button_discard.enable_diabled_button();
					}
					else {
						button_ok.enable_normal_button();
						button_cancel.enable_normal_button();
						button_discard.enable_diabled_button();
					}
				}
				else if(ptr->mouse_select_card == true && Human.select_card == true){
					ptr->mouse_select_card = false;
					Human.select_card = false;
					Machine.being_choose = false;
				}
				return;   // once select one card, return to draw  ?that is needed?
			}
			if (Human.select_card){
				// find node that is chose
				Single_Card* ptr = Human.cards.Pile_Card_Total->next;
				for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
					if (ptr->mouse_select_card) break;
					ptr = ptr->next;
				}
				if (ptr!=NULL&&ptr->card_info.can_attck) {    // if the select card then choose enemy  (window_width - 143) / 2, 40 // 宽 143 || 高 195
				    if (mouse_select_vector.x> (window_width - 143) / 2&&mouse_select_vector.x< (window_width - 143) / 2+143&&mouse_select_vector.y>40&&mouse_select_vector.y<195+40&&Machine.being_choose==false) {     // when it tends to choose enemy
						Machine.being_choose = true;
						button_ok.enable_normal_button();
						button_cancel.enable_diabled_button();
						button_discard.enable_diabled_button();
					}
					else if (mouse_select_vector.x > (window_width - 143) / 2 && mouse_select_vector.x < (window_width - 143) / 2 + 143 && mouse_select_vector.y>40 && mouse_select_vector.y < 195 + 40 && Machine.being_choose==true) {       // when it tends to cancel choose
						Machine.being_choose = false;
						button_ok.enable_diabled_button();
						button_cancel.enable_normal_button();
						button_discard.enable_diabled_button();
					}
					else if (mouse_select_vector.x > 807 && mouse_select_vector.x < (807 + 61) && mouse_select_vector.y > 604 && mouse_select_vector.y < (604 + 75) && Machine.being_choose == true) {  // when it choose enemy & tends to click assure button to fight   the assure button area is 
						Machine.being_choose = false;
						if (ptr->card_info.single_card_number==kill)
						{
							Human.animator_kill = true;
							Human.animator_kill_counter = 0;
							Machine.skill.need_jink = true;
						}
						Human.cards.Detete_Card_Selected();
						Human.select_card = false;
						// then change button state
						button_ok.enable_diabled_button();
						button_cancel.enable_diabled_button();
						button_discard.enable_normal_button();
					}
				}
				else {
					if (mouse_select_vector.x > 807 && mouse_select_vector.x < (807 + 61) && mouse_select_vector.y > 604 && mouse_select_vector.y < (604 + 75)) {  // when it play card & the card is non_choosen   the assure button area is 
						if (ptr->card_info.single_card_number == peach) {
							Human.animator_peach = true;
							Human.animator_peach_counter = 0;
							Human.skill.need_peach;
						}
						else if (ptr->card_info.single_card_number == analeptic) {
							Human.animator_analeptic = true;
							Human.animator_analeptic_counter = 0;
						}
						Machine.being_choose = false;
						Human.cards.Detete_Card_Selected();
						Human.select_card = false;
						// then change button state
						button_ok.enable_diabled_button();
						button_cancel.enable_diabled_button();
						button_discard.enable_normal_button();
						
					}
				}
				if (mouse_select_vector.x > 807 && mouse_select_vector.x < (807 + 61) && mouse_select_vector.y > 694 && mouse_select_vector.y < (694 + 73)) {  // when it go to cancel ,change all anyway
					Machine.being_choose = false;
					Human.select_card = false;
					ptr->mouse_select_card = false;
					// then change button state
					button_ok.enable_diabled_button();
					button_cancel.enable_diabled_button();
					button_discard.enable_normal_button();
				}
				return;
			}
			if (button_discard.is_down) {
				Human.round_play_phase = false;
				Human.round_discard_phase = true;
			}
		}
		// Human discard
		if (Human.round_discard_phase) {
			// there exist tow kind of situation -- original initialize and no hover & no down
			if (Human.selecet_card_amount < Human.cards.Pile_Card_Amount - Human.HP) {
				// discard normal button set
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				button_discard.enable_diabled_button();
			}
			else {
				button_ok.enable_normal_button();
				button_cancel.enable_diabled_button();
				button_discard.enable_diabled_button();
			}
			if (Human.cards.Search_Card_Position(mouse_select_vector)) {
				Single_Card* ptr = nullptr;
				ptr = Human.cards.Search_Card_Position_locate(mouse_select_vector);
				if (ptr->mouse_select_card == false) {
					ptr->mouse_select_card = true;
					Human.selecet_card_amount++;
				}
				else if (ptr->mouse_select_card == true) {
					ptr->mouse_select_card = false;
					Human.selecet_card_amount--;
				}
			}
		}

    }


	void Machine_Round() {
		if (Machine.skill.need_jink) {
			if (Machine.cards.Search_Card(jink)) {
				Machine.animator_jink = true;
				Machine.animator_jink_counter = 0;
				Machine.cards.Delete_Card(jink);
			}
			else {
				Machine.HP--;
				Machine.animator_damage = true;
				Machine.animator_damage_counter = 0;
			}
			Machine.skill.need_jink = false;
		}
		if (Machine.skill.need_peach){
			if (Machine.HP < Machine.limited_HP) Machine.HP++;
			Machine.skill.need_peach = false;
		}
		if (Machine.skill.begging_peach){
			if (Machine.cards.Search_Card(peach)) {
				Human.skill.need_peach = true;
				Machine.cards.Delete_Card(peach);
			}
			else Machine.skill.begging_peach = false;
		}
	}

	void Draw() {
		Draw_Stable_Background();
		Draw_HumanPlayer();
		Draw_Machine();
		Draw_Animator();
		window.display();
	}
	void Draw_HumanPlayer_Button() {
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
	void Draw_HumanPlayer() {
		Single_Card* ptr = Human.cards.Pile_Card_Total->next;
		for (int i=0;i<Human.cards.Pile_Card_Amount;i++){  // each card:  width 93 || height 130
			if (ptr->mouse_select_card) { 
				ptr->point_one.x = 165 + i * 93;
				ptr->point_one.y = window_height - 170;
				ptr->point_two.x = 165 + (i + 1) * 93;
				ptr->point_two.y = window_height - 170 + 130;
				ptr->sprite_card.setPosition(ptr->point_one.x, ptr->point_one.y);
				window.draw(ptr->sprite_card);
			}
			else {
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
			//window.draw(ptr->sprite_card);
			ptr = ptr->next;
		} 
		Draw_HumanPlayer_Button();
		// draw Human HP
		for (int i = 0; i < Human.HP; i++){
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
	}
	void Draw_Animator_Single(bool & animator,int & animator_counter,string file,int limited,int _x,int _y) {
		window.setFramerateLimit(8);
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
			window.setFramerateLimit(30);
		}
	}
	void Draw_Animator() {
		if (Human.animator_kill) { Draw_Animator_Single(Human.animator_kill, Human.animator_kill_counter, "image/animator/killer/", 13, 500, 470);}
		else if (Machine.animator_kill) { Draw_Animator_Single(Machine.animator_kill, Machine.animator_kill_counter, "image/animator/killer/", 13, 450, 200);}
		else if (Human.animator_jink) {	Draw_Animator_Single(Human.animator_jink, Human.animator_jink_counter, "image/animator/jink/", 12, 500, 470);}
		else if (Machine.animator_jink) { Draw_Animator_Single(Machine.animator_jink, Machine.animator_jink_counter, "image/animator/jink/", 12, 450, 240);}
		else if (Human.animator_peach) { Draw_Animator_Single(Human.animator_peach, Human.animator_peach_counter, "image/animator/peach/", 17, 500, 340);}
		else if (Machine.animator_peach) { Draw_Animator_Single(Machine.animator_peach,Machine.animator_peach_counter, "image/animator/peach/", 17, 450,140);}
		else if (Human.animator_analeptic) { Draw_Animator_Single(Human.animator_analeptic, Human.animator_analeptic_counter, "image/animator/analeptic/", 17, 500, 380);}
		else if (Machine.animator_analeptic) { Draw_Animator_Single(Machine.animator_analeptic,Machine.animator_analeptic_counter, "image/animator/analeptic/", 17, 450, 180);}
		else if (Human.animator_damage) { Draw_Animator_Single(Human.animator_damage, Human.animator_damage_counter, "image/animator/damage/", 6, 910, window_height - 170); }
		else if (Machine.animator_damage) {	Draw_Animator_Single(Machine.animator_damage, Machine.animator_damage_counter, "image/animator/damage/", 6, (window_width - 143) / 2 - 30, 50);	}
	}
	void Draw_Machine() {

		// draw Machine HP
		for (int i = 0; i < Machine.HP; i++) {
			sprite_Machine_HP.setPosition((window_width - 143) / 2 +18+ 14 * i, 118);  // the width of image named green small is 14
			window.draw(sprite_Machine_HP);
		}
		if (Machine.being_choose){
			sprite_being_chosen.setPosition((window_width - 143) / 2, 40);  // 宽 1140 || 高 600
			window.draw(sprite_being_chosen);
		}
	}
	void Draw_Stable_Background() {
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
		// draw npc board
		sprite_npcboard.setPosition((window_width - 143) / 2, 40); // 宽 143 || 高 195
		window.draw(sprite_npcboard);
		// draw npc cards board
		sprite_npc_cards.setPosition((window_width - 143) / 2, 103); // 宽 143 || 高 195
		window.draw(sprite_npc_cards);
		// draw piles & cards background
		sprite_piles_back.setPosition(window_width / 3, 300); // 宽 93 || 高 130
		window.draw(sprite_piles_back);
	}
	Game() {
		window_width = 1035;
		window_height = 770;
		virtual_vector.x = -999;
		virtual_vector.y = -999;
		window.create(sf::VideoMode(window_width, window_height), L"三国杀_BY_赵茜茜");
	}
};
