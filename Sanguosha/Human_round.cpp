#include "Game.h"
void Game::Human_Round_Initialize() {
	if (piles.Pile_Card_Amount < 20) piles.Shuffle_Card(); // if card few ,shuffle
	// human get 2 cards each time is its round
	if (Human.round_draw_phase) {
		for (int i = 0; i < 2; i++) {
			Human.cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
			Human.cards.Get_Node(Human.cards.Pile_Card_Amount - 1)->mouse_select_card = false;
			piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
		}
		// original position set
		Single_Card* ptr = Human.cards.Pile_Card_Total->next;
		for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {  // each card:  width 93 || height 130
			ptr->point_one.x = 165 + i * 93;
			ptr->point_one.y = window_height - 135;
			ptr->point_two.x = 165 + (i + 1) * 93;
			ptr->point_two.y = window_height - 135 + 130;
			ptr = ptr->next;
		}
		Human.kill_times = 0;    // set original kill number is 0 when a new round start
		Human.drank_analeptic = false;   // each round no use analeptic
		Human.round_draw_phase = false;
	}
	// to update player's card with card_texture,card_sprite,card_vector where there add new card in * or update card info
	Single_Card* ptr = Human.cards.Pile_Card_Total->next;
	for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
		if (!ptr->file_loaded) {
			stringstream ss;
			ss << "image/skill&equip_card/small_card/" << ptr->card_info.single_card_number << ".jpg";
			Load_Image(ptr->texture_card, ptr->sprite_card, ss.str(), 0, 0, 1, 1);
			ptr->file_loaded = true;
		}
		ptr->enable_to_play = false;
		ptr = ptr->next;
	}
}
void Game::Human_Round_enable_dying_state() {
	if (Human.HP <= 0) {
		Human.is_dying = true;
		cout << "±ôËÀÇóÌÒ" << endl;
		cout << "±ôËÀÇóÌÒ" << endl;
		cout << "±ôËÀÇóÌÒ" << endl;
		cout << "±ôËÀÇóÌÒ" << endl;
		cout << "±ôËÀÇóÌÒ" << endl;
		cout << "±ôËÀÇóÌÒ" << endl;
	}
	if (Human.is_dying == true && Human.skill.begging_peach == false) {
		Machine.skill.begging_peach = true;
		Human.skill.begging_peach = true;
		cout << "Human.skill.begging_peach --->>½øÀ´ÁË" << endl;
	}
}

void Game::Human_Round_Skill_Judgment(Vector2i mouse_select_vector) {
	// when its first time to defense , set cancel button enable
	if ((human_defense||Human.self_save) && button_cancel.is_disabled && button_ok.is_disabled && button_discard.is_disabled) {
		button_cancel.enable_normal_button();
	}
	// skill judgment
	if (Human.skill.need_jink || Human.skill.defense_analeptic_kill) {
		// set jink card enable to play
		Single_Card* ptr = Human.cards.Pile_Card_Total->next;
		for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
			switch (ptr->card_info.single_card_number) {
			case jink:
				ptr->enable_to_play = true;
				break;
			default:
				ptr->enable_to_play = false;
				break;
			}
			ptr = ptr->next;
		}
		if (Human.cards.Search_Card_Position(mouse_select_vector)) {
			Single_Card* ptr = nullptr;
			ptr = Human.cards.Search_Card_Position_locate(mouse_select_vector);
			if (ptr->enable_to_play) {
				if (ptr->mouse_select_card == false && Human.select_card == false) {
					ptr->mouse_select_card = true;
					Human.select_card = true;
					button_ok.enable_normal_button();
					button_cancel.enable_normal_button();
				}
				else if (ptr->mouse_select_card == true && Human.select_card == true) {
					ptr->mouse_select_card = false;
					Human.select_card = false;
					button_ok.enable_diabled_button();
					button_cancel.enable_normal_button();
				}
			}
		}
		if (Human.select_card == true) {

			if (button_ok.is_down) {
				// result
				Human.cards.Detete_Card_Selected();
				// initialize data
				Human.select_card = false;
				Human.selecet_card_amount = 0;
				human_defense = false;
				Human.skill.need_jink = false;
				Human.skill.defense_analeptic_kill = false;
				// animator go
				Human.animator_jink = true;
				Human.animator_jink_counter = 0;
				animator_running = true;
				// change button unable
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				button_discard.enable_diabled_button();
				return;
			}
		}
		if (button_cancel.is_down) {
			// result
			if (Human.skill.defense_analeptic_kill) Human.HP -= 2;
			else if (Human.skill.need_jink) Human.HP--;
			// find node that is chose card
			Single_Card* ptr = Human.cards.Pile_Card_Total->next;
			for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
				if (ptr->mouse_select_card) break;
				ptr = ptr->next;
			}
			if (ptr != nullptr)
			{
				ptr->mouse_select_card = false;
			}
			// initialize data
			Human.select_card = false;
			Human.selecet_card_amount = 0;
			human_defense = false;
			Human.skill.need_jink = false;
			Human.skill.defense_analeptic_kill = false;
			// animator go
			Human.animator_damage = true;
			Human.animator_damage_counter = 0;
			animator_running = true;
			// change button unable
			button_ok.enable_diabled_button();
			button_cancel.enable_diabled_button();
			button_discard.enable_diabled_button();
			// judge human is dying?
			if (Human.HP <= 0) Human_Round_enable_dying_state();
			return;
		}
	}
	
	if (Human.skill.need_peach) {
		if (Human.HP < Human.limited_HP) Human.HP++;
		Human.skill.need_peach = false;
	}
	if (Human.skill.need_analeptic) {   //  when human tends to die , enable card playing analeptic to save life
		//if (Human.is_dying) { Human.HP++;}
	}

	// dying & self_save
	if (Human.self_save) {
		Single_Card* ptr = Human.cards.Pile_Card_Total->next;
		for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
			switch (ptr->card_info.single_card_number) {
			case peach:
				ptr->enable_to_play = true;
				break;
			case analeptic:
				ptr->enable_to_play = true;
				break;
			default:
				ptr->enable_to_play = false;
				break;
			}
			ptr = ptr->next;
		}
		if (Human.cards.Search_Card_Position(mouse_select_vector)) {
			Single_Card* ptr = nullptr;
			ptr = Human.cards.Search_Card_Position_locate(mouse_select_vector);
			if (ptr->enable_to_play) {
				if (ptr->mouse_select_card == false && Human.select_card == false) {
					ptr->mouse_select_card = true;
					Human.select_card = true;
					button_ok.enable_normal_button();
					button_cancel.enable_normal_button();
				}
				else if (ptr->mouse_select_card == true && Human.select_card == true) {
					ptr->mouse_select_card = false;
					Human.select_card = false;
					button_ok.enable_diabled_button();
					button_cancel.enable_normal_button();
				}
			}
		}
		if (Human.select_card == true) {
			if (button_ok.is_down) {
				// find node that is chose card
				Single_Card* ptr = Human.cards.Pile_Card_Total->next;
				for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
					if (ptr->mouse_select_card) break;
					ptr = ptr->next;
				}
				if (ptr != nullptr)
				{
					ptr->mouse_select_card = false;
				}
				// result
				int which_animator = ptr->card_info.single_card_number;
				if (ptr->card_info.single_card_number == peach) Human.HP++;
				else if (ptr->card_info.single_card_number == analeptic) Human.HP++;
				out_put(* ptr);
				Human.cards.Detete_Card_Selected();
				// initialize data
				Human.select_card = false;
				Human.selecet_card_amount = 0;
				if (Human.HP > 0) {
					Human.die = false;
					Human.is_dying = false;
					Human.self_save = false;
				}
				// animator go
				if (which_animator == peach) {
					Human.animator_peach = true;
					Human.animator_peach_counter = 0;
					animator_running = true;
				}
				else if (which_animator == analeptic) {
					Human.animator_analeptic = true;
					Human.animator_analeptic_counter = 0;
					animator_running = true;
				}
				// change button unable
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				button_discard.enable_diabled_button();
				return;
			}
		}
		if (button_cancel.is_down) {
			// result
			Human.die = true;
			Human.is_dying = true;
			Human.self_save = false;
			// find node that is chose card
			Single_Card* ptr = Human.cards.Pile_Card_Total->next;
			for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
				if (ptr->mouse_select_card) break;
				ptr = ptr->next;
			}
			if (ptr != nullptr)
			{
				ptr->mouse_select_card = false;
			}
			// initialize data
			Human.select_card = false;
			Human.selecet_card_amount = 0;
			// animator go
			// change button unable
			button_ok.enable_diabled_button();
			button_cancel.enable_diabled_button();
			button_discard.enable_diabled_button();
			return;
		}
	}
}
void Game::Human_Round() {
	Vector2i mouse_select_vector = Input();  // in general there only exist one input function  * wtf! that is matter most
	Human_Round_Initialize();
	Human_Round_Skill_Judgment(mouse_select_vector);
	// Human play card

	// where all machine have decided to save or not ,player themselves start save themselves ; for fundation there exist one machine to test
	if (Machine.skill.begging_peach == false && Human.is_dying == true) {
		Human.self_save = true;
	}

	if (Human.round_play_phase) {
		// set each card enable to play or cant 
		Single_Card* ptr = nullptr;
		ptr = Human.cards.Pile_Card_Total->next;
		for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
			switch (ptr->card_info.single_card_number) {
			case kill:
				if (Human.kill_times < Human.kill_limit) ptr->enable_to_play = true;
				else  ptr->enable_to_play = false;
				break;
			case jink:
				ptr->enable_to_play = false;
				break;
			case analeptic:
				if (Human.drank_analeptic)	ptr->enable_to_play = false;
				else	ptr->enable_to_play = true;
				break;
			case peach:
				ptr->enable_to_play = true;
				break;
			default:
				break;
			}
			ptr = ptr->next;
		}
		// button stage initialize
		if ((Human.select_card == false) && !(button_discard.is_hover || button_discard.is_down)) { // there exist tow kind of situation -- original initialize and no hover & no down
			button_ok.enable_diabled_button();
			button_cancel.enable_diabled_button();
			button_discard.enable_normal_button();
		}
		if (Human.cards.Search_Card_Position(mouse_select_vector)) {        //play choose cards ,only once each time   also  it can change button state according to card attribute
			Single_Card* ptr = nullptr;
			ptr = Human.cards.Search_Card_Position_locate(mouse_select_vector);
			if (ptr->enable_to_play) {
				if (ptr->mouse_select_card == false && Human.select_card == false) {
					ptr->mouse_select_card = true;
					Human.select_card = true;
					if (ptr->card_info.can_attck) {
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
				else if (ptr->mouse_select_card == true && Human.select_card == true) {
					ptr->mouse_select_card = false;
					Human.select_card = false;
					Machine.being_choose = false;
				}
				return;   // once select one card, return to draw  ?that is needed?
			}
		}
		if (Human.select_card) {
			// find node that is chose
			Single_Card* ptr = Human.cards.Pile_Card_Total->next;
			for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
				if (ptr->mouse_select_card) break;
				ptr = ptr->next;
			}
			if (ptr != NULL && ptr->card_info.can_attck) {    // if the select card then choose enemy  (window_width - 143) / 2, 40 // ¿í 143 || ¸ß 195
				if (mouse_select_vector.x > (window_width - 143) / 2 && mouse_select_vector.x < (window_width - 143) / 2 + 143 && mouse_select_vector.y>40 && mouse_select_vector.y < 195 + 40 && Machine.being_choose == false) {     // when it tends to choose enemy
					Machine.being_choose = true;
					button_ok.enable_normal_button();
					button_cancel.enable_diabled_button();
					button_discard.enable_diabled_button();
				}
				else if (mouse_select_vector.x > (window_width - 143) / 2 && mouse_select_vector.x < (window_width - 143) / 2 + 143 && mouse_select_vector.y>40 && mouse_select_vector.y < 195 + 40 && Machine.being_choose == true) {       // when it tends to cancel choose
					Machine.being_choose = false;
					button_ok.enable_diabled_button();
					button_cancel.enable_normal_button();
					button_discard.enable_diabled_button();
				}
				else if (mouse_select_vector.x > 807 && mouse_select_vector.x < (807 + 61) && mouse_select_vector.y > 604 && mouse_select_vector.y < (604 + 75) && Machine.being_choose == true) {  // when it choose enemy & tends to click assure button to fight   the assure button area is 
					Machine.being_choose = false;
					if (ptr->card_info.single_card_number == kill && Human.drank_analeptic)
					{
						Human.animator_kill = true;
						Human.animator_kill_counter = 0;
						animator_running = true;
						Machine.skill.defense_analeptic_kill = true;
						Human.kill_times++;
						Human.cards.Detete_Card_Selected();
					}
					else if (ptr->card_info.single_card_number == kill)
					{
						Human.animator_kill = true;
						Human.animator_kill_counter = 0;
						animator_running = true;
						Machine.skill.need_jink = true;
						Human.kill_times++;
						Human.cards.Detete_Card_Selected();
					}
					Human.select_card = false;
					// then change button state
					button_ok.enable_diabled_button();
					button_cancel.enable_diabled_button();
					button_discard.enable_normal_button();
					return;
				}
			}
			else {
				if (mouse_select_vector.x > 807 && mouse_select_vector.x < (807 + 61) && mouse_select_vector.y > 604 && mouse_select_vector.y < (604 + 75)) {  // when it play card & the card is non_choosen   the assure button area is 
					if (ptr->card_info.single_card_number == peach) {
						Human.animator_peach = true;
						Human.animator_peach_counter = 0;
						animator_running = true;
						if (Human.HP < Human.limited_HP) Human.HP++;
						//Human.skill.need_peach=true;
					}
					else if (ptr->card_info.single_card_number == analeptic) { // when human have not die,this kill can doubled kill power
						Human.kill_power++;
						Human.drank_analeptic = true;
						Human.animator_analeptic = true;
						Human.animator_analeptic_counter = 0;
						animator_running = true;
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
		if (mouse_select_vector.x > 874 && mouse_select_vector.x < (874 + 33) && mouse_select_vector.y > 644 && mouse_select_vector.y < (644 + 81)) {
			Human.round_play_phase = false;
			Human.round_discard_phase = true;
		}
	}
	// Human discard
	if (Human.round_discard_phase) {

		// there exist tow kind of situation -- original initialize and no hover & no down

		if (Human.cards.Pile_Card_Amount <= Human.HP) {   // no need to discard
			button_ok.enable_diabled_button();
			button_cancel.enable_diabled_button();
			button_discard.enable_diabled_button();
			Human.round_discard_phase = false;
			new_round = true;
			turn = 0;
			return;
		}
		else if (Human.selecet_card_amount < Human.cards.Pile_Card_Amount - Human.HP) {
			// discard normal button set
			button_ok.enable_diabled_button();
			button_cancel.enable_diabled_button();
			button_discard.enable_diabled_button();
		}
		else if (button_ok.is_disabled)	button_ok.enable_normal_button();

		if (Human.cards.Search_Card_Position(mouse_select_vector)) {
			Single_Card* ptr = nullptr;
			ptr = Human.cards.Search_Card_Position_locate(mouse_select_vector);
			if (ptr->mouse_select_card == false && Human.selecet_card_amount < Human.cards.Pile_Card_Amount - Human.HP) {  // only select limited cards
				ptr->mouse_select_card = true;
				Human.selecet_card_amount++;
			}
			else if (ptr->mouse_select_card == true) {
				ptr->mouse_select_card = false;
				Human.selecet_card_amount--;
			}
		}
		if (button_ok.is_down) {
			for (int i = 0; i < Human.selecet_card_amount; i++) {
				Human.cards.Detete_Card_Selected();
			}
			Human.selecet_card_amount = 0;
			button_ok.enable_diabled_button();
			Human.round_discard_phase = false;
			new_round = true;
			turn = 0;
		}
	}


	// button unable when animator start & go
	if (animator_running) {
		button_ok.enable_diabled_button();
		button_cancel.enable_diabled_button();
		button_discard.enable_diabled_button();
	}
}