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
	if (Human.HP > 0) {
		Human.is_dying = false;
		Human.die = false;
		Human.self_save = false;
		exturn = normal;
	}
}
void Game::Human_Round_enable_dying_state() {
	if (Human.HP <= 0) {
		Human.is_dying = true;
		cout << "Human-->>��������" << endl;
		cout << "Human-->>��������" << endl;
		cout << "Human-->>��������" << endl;
		cout << "Human-->>��������" << endl;
		cout << "Human-->>��������" << endl;
	}
	if (Human.is_dying == true) {
		// sent begging for peach signal to other machines(all of them)
		for (int number; number < 4; number++) {
			Machine[number].skill.begging_peach = true;
		}
		exturn = turn;
		round_loop_starter = turn;
		peach_begger = Human.charactor_code;
		cout << "Human.skill.begging_peach --->>������" << endl;
	}
}

int Game::Human_Round_Skill_Judgment(Vector2i mouse_select_vector) {
	// when its first time to defense , set cancel button enable
	if ((exturn==human||Human.self_save|| Human.skill.begging_peach) && button_cancel.is_disabled && button_ok.is_disabled && button_discard.is_disabled) {
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
				//human_defense = false;
				exturn = normal;
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
				return 0;
			}
		}
		if (button_cancel.is_down) {
			// result
			if (Human.skill.defense_analeptic_kill) Human.HP -= 2;
			else if (Human.skill.need_jink) Human.HP--;
			// judge human is dying?
			if (Human.HP <= 0) Human_Round_enable_dying_state();
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
			//human_defense = false;
			exturn = normal;
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
			return 0;
		}
		return 0;
	}
	
	if (Human.skill.receive_peach==true) {
		if (Human.HP < Human.limited_HP) Human.HP++;
		Human.skill.receive_peach = false;
		if (Human.HP <= 0) {
			exturn = exturn_backup;
			exturn_backup = -1;
		}
		else {
			exturn = normal;
			exturn_backup = -1; 
			Human.skill.asking_peach = false;
			Machine[0].skill.begging_peach = false;
			Machine[1].skill.begging_peach = false;
			Machine[2].skill.begging_peach = false;
			Machine[3].skill.begging_peach = false;
			peach_begger = -1;    // default one is -1 in case unknown error
			Human.self_save = false;
			Human.is_dying = false;
		}
	}
	
	if (Human.skill.begging_peach) {
		cout << "�Ƿ���Ҿ�machine����" << endl;
		round_loop = true;
		Single_Card* ptr = Human.cards.Pile_Card_Total->next;
		for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
			switch (ptr->card_info.single_card_number) {
			case peach:
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
				// result
				// figure out who sent begging peach signal then give it
				switch (peach_begger)
				{
				case human:
					Human.skill.receive_peach = true;
					break;
				case machine_0:
					Machine[0].skill.receive_peach = true;
					break;
				case machine_1:
					Machine[1].skill.receive_peach = true;
					break;
				case machine_2:
					Machine[2].skill.receive_peach = true;
					break;
				case machine_3:
					Machine[3].skill.receive_peach = true;
					break;
				default:
					break;
				}
				// round change
				exturn_backup = exturn;
				exturn = peach_begger;
				Human.cards.Detete_Card_Selected();
				Human.skill.begging_peach = false;
				// initialize data
				Human.select_card = false;
				Human.selecet_card_amount = 0;
				// change button unable
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				button_discard.enable_diabled_button();
				return 0;
			}
		}
		if (button_cancel.is_down) {
			// result
			/** where exist more player, it turn to next player */
			if (exturn == machine_3) exturn = human;  // meaning going to a loop
			else exturn++;
			Human.skill.begging_peach = false;
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
			return 0;
		}
		cout << "come yet??" << endl;
		return 0;
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
				// result
				int which_animator = ptr->card_info.single_card_number;
				if (which_animator == peach || which_animator == analeptic) {
					out_put(*ptr);
					Human.cards.Detete_Card_Selected();
					Human.skill.receive_peach = true;
					exturn_backup = exturn;
				}
				// initialize data
				Human.select_card = false;
				Human.selecet_card_amount = 0;
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
				return 0;
			}
		}
		if (button_cancel.is_down) {
			// result
			if (exturn == machine_3) exturn = human;  // meaning going to a loop
			else exturn++;
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
			return 0;
		}
	}
	return 1;
}
void Game::Human_Round() {
	Vector2i mouse_select_vector = Input();  // in general there only exist one input function  * wtf! that is matter most
	Human_Round_Initialize();
	if(Human_Round_Skill_Judgment(mouse_select_vector)==0) return;

	// Human play card
	if (Human.HP <= 0) Human.self_save = true;
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
					Machine[0].being_choose = false;
					Machine[1].being_choose = false;
					Machine[2].being_choose = false;
					Machine[3].being_choose = false;
				}
				return;   // once select one card, return to draw  ?that is needed?
			}
		}
		if (Human.select_card) {
			// find node which card is chosen
			Single_Card* ptr = Human.cards.Pile_Card_Total->next;
			for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
				if (ptr->mouse_select_card) break;
				ptr = ptr->next;
			}
			if (ptr != NULL && ptr->card_info.can_attck) {    // if the select card then choose enemy  (window_width - 143) / 2, 40 // �� 143 || �� 195
				// machine-0 to machine-3 Traverse each situation;though it seem a little bit inefficient;looking for further improvement
				for (int number = 0; number < 4; number++) {
					if (mouse_select_vector.x > Machine[number].location_one.x && 
						mouse_select_vector.x < Machine[number].location_two.x &&
						mouse_select_vector.y > Machine[number].location_one.y && 
						mouse_select_vector.y < Machine[number].location_two.y && 
						Machine[number].being_choose == false) {     // when it tends to choose enemy
						Machine[number].being_choose = true;
						button_ok.enable_normal_button();
						button_cancel.enable_diabled_button();
						button_discard.enable_diabled_button();
					}
					else if (mouse_select_vector.x > Machine[number].location_one.x && 
						mouse_select_vector.x < Machine[number].location_two.x && 
						mouse_select_vector.y>Machine[number].location_one.y && 
						mouse_select_vector.y < Machine[number].location_two.y && 
						Machine[number].being_choose == true) {       // when it tends to cancel choose
						Machine[number].being_choose = false;
						button_ok.enable_diabled_button();
						button_cancel.enable_normal_button();
						button_discard.enable_diabled_button();
					}
					else if (mouse_select_vector.x > 807 && mouse_select_vector.x < (807 + 61) && mouse_select_vector.y > 604 && mouse_select_vector.y < (604 + 75) && Machine[number].being_choose == true) {  // when it choose enemy & tends to click assure button to fight   the assure button area is 
						Machine[number].being_choose = false;
						if (ptr->card_info.single_card_number == kill && Human.drank_analeptic)
						{
							//  animator running
							Human.animator_kill = true;
							Human.animator_kill_counter = 0;
							animator_running = true;
							// result
							Machine[number].skill.defense_analeptic_kill = true;
							switch (number)
							{
							case 0:
								exturn = machine_0;
							case 1:
								exturn = machine_1;
							case 2:
								exturn = machine_2;
							case 3:
								exturn = machine_3;
							default:
								break;
							}
							Human.kill_times++;
							Human.cards.Detete_Card_Selected();
						}
						else if (ptr->card_info.single_card_number == kill)
						{
							//  animator running
							Human.animator_kill = true;
							Human.animator_kill_counter = 0;
							animator_running = true;
							// result
							Machine[number].skill.need_jink = true;
							switch (number)
							{
							case 0:
								exturn = machine_0;
							case 1:
								exturn = machine_1;
							case 2:
								exturn = machine_2;
							case 3:
								exturn = machine_3;
							default:
								break;
							}
							Human.kill_times++;
							Human.cards.Detete_Card_Selected();
						}
						Human.select_card = false;
						// then change button state
						button_ok.enable_diabled_button();
						button_cancel.enable_diabled_button();
						button_discard.enable_diabled_button();
						return;
					}
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
					Machine[0].being_choose = false;
					Machine[1].being_choose = false;
					Machine[2].being_choose = false;
					Machine[3].being_choose = false;
					Human.cards.Detete_Card_Selected();
					Human.select_card = false;
					// then change button state
					button_ok.enable_diabled_button();
					button_cancel.enable_diabled_button();
					button_discard.enable_normal_button();

				}
			}
			if (mouse_select_vector.x > 807 && mouse_select_vector.x < (807 + 61) && mouse_select_vector.y > 694 && mouse_select_vector.y < (694 + 73)) {  // when it go to cancel ,change all anyway
				Machine[0].being_choose = false;
				Machine[1].being_choose = false;
				Machine[2].being_choose = false;
				Machine[3].being_choose = false;
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
			if (turn == machine_3) turn = human;  // meaning going to a loop
			else turn++;
		}
	}

	// button unable when animator start & go
	if (animator_running) {
		button_ok.enable_diabled_button();
		button_cancel.enable_diabled_button();
		button_discard.enable_diabled_button();
	}
}