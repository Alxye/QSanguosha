#include "Game.h"
void Game::Machine_Round_Initialize(Player& machine) {
	if (piles.Pile_Card_Amount < 20) piles.Shuffle_Card(); // if card few ,shuffle
	// machine get 2 cards each time when it is its round
	if (machine.round_draw_phase) {
		for (int i = 0; i < 2; i++) {
			machine.cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
			machine.cards.Get_Node(machine.cards.Pile_Card_Amount - 1)->mouse_select_card = false;
			piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
		}
		machine.round_draw_phase = false;
		cout << "机器摸了两张牌" << endl;

		machine.kill_times = 0;    // set original kill number is 0 when a new round start
		machine.kill_power = 1;
		machine.drank_analeptic = false;
	}
	if (machine.HP > 0 && machine.is_dying) {
		machine.is_dying = false;
		machine.die = false;
		machine.self_save = false;
		exturn = normal;
	}
}

void Game::Machine_Round_enable_dying_state(Player& machine) {
	if (machine.HP <= 0) {
		machine.is_dying = true;
		cout << "Machine "<<machine.charactor_code-1<<" is begging for peach ! " << endl;
	}
	if (machine.is_dying == true) {
		// sent a begging peach signal to human player
		Human.skill.begging_peach = true;
		// sent a begging peach signal to other machine player
		for (int number=0; number < machine_number; number++) {
			if (Machine[number].charactor_code != machine.charactor_code) Machine[number].skill.begging_peach = true;
		}
		// change round to extra turn so that it can be in passive round
		exturn = turn;
		//round_loop = true;
		round_loop_starter = turn;
		// record who set signal of begging peach
		peach_begger = machine.charactor_code;
		cout << "Machine.skill.begging_peach --->>进来了" << endl;
	}
}

int Game::Machine_Round_Skill_Judgment(Player& machine) {
	// about begger-life
	if (machine.skill.begging_peach == false && round_loop && round_loop_starter == machine.charactor_code) {
		switch (peach_begger)
		{
		case human:
			if (Human.HP <= 0) Human.die = true;
			break;
		case machine_0:
			if (Machine[0].HP <= 0) {
				//Machine[0].die = true;
				Machine[0].die = false;
				Machine[0].skill.begging_peach = false;
				Machine[0].self_save = false;
				Machine[0].HP = 2;
				Machine[0].limited_HP = 2;
				killing_number++;
			}
			break;
		case machine_1:
			if (Machine[1].HP <= 0) {
				//Machine[1].die = true;
				Machine[1].die = false;
				Machine[1].skill.begging_peach = false;
				Machine[1].self_save = false;
				Machine[1].HP = 2;
				Machine[1].limited_HP = 2;
				killing_number++;
			}
			break;
		case machine_2:
			if (Machine[2].HP <= 0){
				//Machine[2].die = true;
				Machine[2].die = false;
				Machine[2].skill.begging_peach = false;
				Machine[2].self_save = false;
				Machine[2].HP = 2;
				Machine[2].limited_HP = 2;
				killing_number++;
			}
			break;
		case machine_3:
			if (Machine[3].HP <= 0) {
				//Machine[3].die = true;
				Machine[3].die = false;
				Machine[3].skill.begging_peach = false;
				Machine[3].self_save = false;
				Machine[3].HP = 2;
				Machine[3].limited_HP = 2;
				killing_number++;
			}
			break;
		default:
			break;
		}
		round_loop = false;
		round_loop_starter = -1; // default value is -1 to escape & found unknown error
		exturn = normal;
		exturn_backup = -1;
		return 0;
	}
	if (machine.skill.need_jink) {
		if (machine.cards.Search_Card(jink)) {
			machine.animator_jink = true;
			machine.animator_jink_counter = 0;
			animator_running = true;
			machine.cards.Delete_Card(jink);
			discard_pile.Insert_Card(jink, 1);
		}
		else {
			machine.HP--;
			machine.animator_damage = true;
			machine.animator_damage_counter = 0;
			animator_running = true;
		}
		machine.skill.need_jink = false;
		exturn = normal;
		Machine_Round_enable_dying_state(machine);
		return 0;
	}
	if (machine.skill.defense_analeptic_kill) {
		if (machine.cards.Search_Card(jink)) {
			machine.animator_jink = true;
			machine.animator_jink_counter = 0;
			animator_running = true;
			machine.cards.Delete_Card(jink);
			discard_pile.Insert_Card(jink, 1);
		}
		else {
			machine.HP -= 2;
			machine.animator_damage = true;
			machine.animator_damage_counter = 0;
			animator_running = true;
		}
		machine.skill.defense_analeptic_kill = false;
		exturn = normal;
		Machine_Round_enable_dying_state(machine);
		return 0;
	}
	
	if (machine.skill.receive_peach) {
		if (machine.HP < machine.limited_HP) machine.HP++;
		machine.skill.receive_peach = false;
		if (machine.HP <= 0) {
			/**
			 *  for the question why don't set the value of next turning one ?
			 *  answer is >>> make player plays more peach to save player possible
			 */
			//Machine_Round_enable_dying_state(machine);
			switch (exturn_backup)
			{
			case human:
				Human.skill.begging_peach = true;
				break;
			case machine_0:
				Machine[0].skill.begging_peach = true;
				break;
			case machine_1:
				Machine[1].skill.begging_peach = true;
				break;
			case machine_2:
				Machine[2].skill.begging_peach = true;
				break;
			case machine_3:
				Machine[3].skill.begging_peach = true;
				break;
			default:
				break;
			}
			exturn = exturn_backup;
			exturn_backup = -1;    // default exturn_backup value in case there got unknown error
		}
		else {
			exturn = normal;
			exturn_backup = -1;    // default exturn_backup value in case there got unknown error
			// reset begging peach value

			//Human.skill.asking_peach = false;
			Human.skill.begging_peach = false;
			Machine[0].skill.begging_peach = false;
			Machine[1].skill.begging_peach = false;
			Machine[2].skill.begging_peach = false;
			Machine[3].skill.begging_peach = false;
			peach_begger = -1;    // default one is -1 in case unknown error
			round_loop_starter = -1;
			round_loop = false;
			machine.self_save = false;
			machine.is_dying = false;
		}
		return 0;
	}
	
	if (machine.skill.begging_peach) {
		round_loop = true;
		if (machine.cards.Search_Card(peach)) {
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
			machine.cards.Delete_Card(peach);
			discard_pile.Insert_Card(peach, 1);
			cout << "Machine  machine.charactor_code ==" << machine.charactor_code << " give a peach ！" << endl;
			// go to peach-begger then having peach;also back up current state of turn for the situation that peach-begger is still in dying state even after get one blood recovered
			exturn_backup = exturn;
			exturn = peach_begger;

			cout << exturn << endl;
		}
		else {  // when machine don't mean to give peach ,ask next one
			// if there exist more machine then change it another machine to judge 
			if (exturn == machine_number+1) exturn = human;  // meaning going to a loop
			else exturn++;

			cout << exturn << endl;

			cout << "Machine  machine.charactor_code ==" << machine.charactor_code << " 拒绝出桃 ！" << endl;
		}
		machine.skill.begging_peach = false;
		return 0;
	}

	// dying & self_save
	if (machine.self_save) {
		if (machine.cards.Search_Card(peach)) {
			// animator start
			machine.animator_peach = true;
			machine.animator_peach_counter = 0;
			animator_running = true;
			// result
			machine.cards.Delete_Card(peach);
			discard_pile.Insert_Card(peach, 1);
			machine.skill.receive_peach = true;
			exturn_backup = exturn;
		}
		else if (machine.cards.Search_Card(analeptic)) {
			// animator start
			machine.animator_analeptic = true;
			machine.animator_analeptic_counter = 0;
			animator_running = true;
			// result
			machine.cards.Delete_Card(analeptic);
			discard_pile.Insert_Card(analeptic, 1);
			machine.skill.receive_peach = true;
			exturn_backup = exturn;
		}
		else {
			if (exturn == machine_number+1) exturn = human;  // meaning going to a loop
			else exturn++;
			machine.is_dying = true;
			machine.self_save = false;
		}
		return 0;
	}

	return 1;  // if it don't get any kind of passive skill then default return 1 to get normal round
}

void Game::Machine_Round(Player& machine) {

	Machine_Round_Initialize(machine);

	if (Machine_Round_Skill_Judgment(machine) == 0) return;

	if (machine.HP <= 0 && peach_begger==machine.charactor_code) {
		machine.self_save = true;
		return;
	}
	if (exturn == normal && turn == machine.charactor_code) {
		if (machine.round_play_phase) {
			if (machine.drank_analeptic == false) {
				if (machine.cards.Search_Card(analeptic)) {
					// animator start
					machine.animator_analeptic = true;
					machine.animator_analeptic_counter = 0;
					animator_running = true;
					// result
					machine.cards.Delete_Card(analeptic);
					discard_pile.Insert_Card(analeptic, 1);
					machine.drank_analeptic = true;
					machine.kill_power++;
					return;
				}
			}
			if (machine.kill_times < machine.kill_limit) {
				if (machine.cards.Search_Card(kill)) {
					// animator start
					machine.animator_kill = true;
					machine.animator_kill_counter = 0;
					animator_running = true;
					// result
					if (machine.drank_analeptic) {
						int emeny_code = rand() % (machine_number+1) + 1;
						while (emeny_code == machine.charactor_code) emeny_code = rand() % (machine_number + 1) + 1;
						cout << "emeny_code::::" << emeny_code << endl;
						switch (emeny_code)
						{
						case human:
							Human.skill.defense_analeptic_kill = true;
							break;
						case machine_0:
							Machine[0].skill.defense_analeptic_kill = true;
							break;
						case machine_1:
							Machine[1].skill.defense_analeptic_kill = true;
							break;
						case machine_2:
							Machine[2].skill.defense_analeptic_kill = true;
							break;
						case machine_3:
							Machine[3].skill.defense_analeptic_kill = true;
							break;
						default:
							break;
						}
						machine.cards.Delete_Card(kill);
						discard_pile.Insert_Card(kill, 1);
						machine.kill_times++;
						// change exturn
						exturn = emeny_code;
					}
					else {
						int emeny_code = rand() % (machine_number + 1) + 1;
						while (emeny_code == machine.charactor_code) emeny_code = rand() % (machine_number + 1) + 1;
						cout << "emeny_code::::" << emeny_code << endl;
						switch (emeny_code)
						{
						case human:
							Human.skill.need_jink = true;
							break;
						case machine_0:
							Machine[0].skill.need_jink = true;
							break;
						case machine_1:
							Machine[1].skill.need_jink = true;
							break;
						case machine_2:
							Machine[2].skill.need_jink = true;
							break;
						case machine_3:
							Machine[3].skill.need_jink = true;
							break;
						default:
							break;
						}
						machine.cards.Delete_Card(kill);
						discard_pile.Insert_Card(kill, 1);
						machine.kill_times++;
						// change exturn
						exturn = emeny_code;
					}
					return;
				}
			}
			if (machine.HP < machine.limited_HP) {
				if (machine.cards.Search_Card(peach)) {
					// animator start
					machine.animator_peach = true;
					machine.animator_peach_counter = 0;
					animator_running = true;
					// result
					machine.cards.Delete_Card(peach);
					discard_pile.Insert_Card(peach, 1);
					machine.HP++;
					return;
				}
			}
			machine.round_play_phase = false;
			machine.round_discard_phase = true;
		}
		if (machine.round_discard_phase) {
			if (machine.cards.Pile_Card_Amount <= machine.HP) {   // no need to discard
				machine.round_discard_phase = false;
				new_round = true;
				if (turn == machine_number + 1) turn = human;  // meaning going to a loop
				else turn++;
				return;
			}
			else {
				// discard normal button set
				while (machine.cards.Pile_Card_Amount > machine.HP){
					int temp_delete_number = machine.cards.Pile_Card_Total->next->card_info.single_card_number;
					machine.cards.Delete_Card(temp_delete_number);
					discard_pile.Insert_Card(temp_delete_number, 1);
				}
				machine.round_discard_phase = false;
				new_round = true;
				if (turn == machine_number + 1) turn = human;  // meaning going to a loop
				else turn++;
				return;
			}
		}

	}
}
