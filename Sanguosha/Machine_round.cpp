#include "Game.h"
void Game::Machine_Round_Initialize() {
	if (piles.Pile_Card_Amount < 20) piles.Shuffle_Card(); // if card few ,shuffle
	// human get 2 cards each time is its round
	if (Machine.round_draw_phase) {
		for (int i = 0; i < 2; i++) {
			Machine.cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
			Machine.cards.Get_Node(Machine.cards.Pile_Card_Amount - 1)->mouse_select_card = false;
			piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
		}
		Machine.round_draw_phase = false;
		cout << "机器摸了两张牌" << endl;

		Machine.kill_times = 0;    // set original kill number is 0 when a new round start
		Machine.kill_power = 1;
		Machine.drank_analeptic = false;
	}
	if (Machine.HP > 0) {
		Machine.is_dying = false;
		Machine.die = false;
		Machine.self_save = false;
	}
}

void Game::Machine_Round_enable_dying_state() {
	if (Machine.HP <= 0) {
		Machine.is_dying = true;
		cout << "machine濒死求桃" << endl;
		cout << "machine濒死求桃" << endl;
		cout << "machine濒死求桃" << endl;
		cout << "machine濒死求桃" << endl;
		cout << "machine濒死求桃" << endl;
		cout << "machine濒死求桃" << endl;
		cout << "machine濒死求桃" << endl;
		cout << "machine濒死求桃" << endl;
	}
	if (Machine.is_dying == true) {
		Human.skill.begging_peach = true;
		//...Machine2.skill.begging_peach = true;
		//...Machine3.skill.begging_peach = true;
		//...Machine4.skill.begging_peach = true;
		exturn = human;
		cout << "Machine.skill.begging_peach --->>进来了" << endl;
	}
}
int Game::Machine_Round_Skill_Judgment() {
	if (Machine.skill.need_jink) {
		if (Machine.cards.Search_Card(jink)) {
			Machine.animator_jink = true;
			Machine.animator_jink_counter = 0;
			animator_running = true;
			Machine.cards.Delete_Card(jink);
		}
		else {
			Machine.HP--;
			Machine.animator_damage = true;
			Machine.animator_damage_counter = 0;
			animator_running = true;
		}
		Machine.skill.need_jink = false;
		exturn = normal;
		Machine_Round_enable_dying_state();
		return 0;
	}
	if (Machine.skill.defense_analeptic_kill) {
		if (Machine.cards.Search_Card(jink)) {
			Machine.animator_jink = true;
			Machine.animator_jink_counter = 0;
			animator_running = true;
			Machine.cards.Delete_Card(jink);
		}
		else {
			Machine.HP -= 2;
			Machine.animator_damage = true;
			Machine.animator_damage_counter = 0;
			animator_running = true;
		}
		Machine.skill.defense_analeptic_kill = false;
		exturn = normal;
		Machine_Round_enable_dying_state();
		return 0;
	}
	if (Machine.skill.receive_peach) {
		if (Machine.HP < Machine.limited_HP) Machine.HP++;
		Machine.skill.receive_peach = false;
		if (Machine.HP <= 0) {
			exturn = machine_1;
			Machine.self_save = true;
			Machine.is_dying = true;
		}
		else {
			exturn = normal;
			Machine.self_save = false;
			Machine.is_dying = false;
		}
	}
	
	if (Machine.skill.begging_peach) {
		if (Machine.cards.Search_Card(peach)) {
			Human.skill.receive_peach = true;
			Machine.cards.Delete_Card(peach);
			cout << "机器给了一个桃！" << endl;
		}
		// if there exist more machine then change it another machine to judge
		Machine.skill.begging_peach = false;
		exturn = human;
		return 0;
	}
	
	// dying & self_save
	if (Machine.self_save) {
		if (Machine.cards.Search_Card(peach)) {
			// animator start
			Machine.animator_peach = true;
			Machine.animator_peach_counter = 0;
			animator_running = true;
			// result
			Machine.cards.Delete_Card(peach);
			Machine.HP++;
			exturn = normal;
		}
		if(Machine.HP<=0){
			Machine.die = true;
			Machine.is_dying = true;
			Machine.self_save = false;
		}
		return 0;
	}
	return 1;
}

void Game::Machine_Round() {

	Machine_Round_Initialize();
	if (Machine_Round_Skill_Judgment() == 0) return;
	if (Machine.HP <= 0) Machine.self_save = true;
	if (Machine.round_play_phase && Human.self_save == false) {
		if (Machine.drank_analeptic == false) {
			if (Machine.cards.Search_Card(analeptic)) {
				// animator start
				Machine.animator_analeptic = true;
				Machine.animator_analeptic_counter = 0;
				animator_running = true;
				// result
				Machine.cards.Delete_Card(analeptic);
				Machine.drank_analeptic = true;
				Machine.kill_power++;
				return;
			}
		}
		if (Machine.kill_times < Machine.kill_limit) {
			if (Machine.cards.Search_Card(kill)) {
				// animator start
				Machine.animator_kill = true;
				Machine.animator_kill_counter = 0;
				animator_running = true;
				// result
				if (Machine.drank_analeptic) {
					Human.skill.defense_analeptic_kill = true;
					Machine.cards.Delete_Card(kill);
					Machine.kill_times++;
				}
				else {
					Human.skill.need_jink = true;
					Machine.cards.Delete_Card(kill);
					Machine.kill_times++;
				}
				exturn_backup = exturn;
				exturn = human;
				return;
			}
		}
		if (Machine.HP < Machine.limited_HP) {
			if (Machine.cards.Search_Card(peach)) {
				// animator start
				Machine.animator_peach = true;
				Machine.animator_peach_counter = 0;
				animator_running = true;
				// result
				Machine.cards.Delete_Card(peach);
				Machine.HP++;
				return;
			}
		}
		Machine.round_play_phase = false;
		Machine.round_discard_phase = true;
	}
	if (Machine.round_discard_phase) {
		if (Machine.cards.Pile_Card_Amount <= Machine.HP) {   // no need to discard
			Machine.round_discard_phase = false;
			new_round = true;
			turn = 1;
			return;
		}
		else if (Machine.selecet_card_amount < Machine.cards.Pile_Card_Amount - Machine.HP) {
			// discard normal button set
			for (int i = 0; i < Machine.cards.Pile_Card_Amount - Machine.HP; i++) {
				Machine.cards.Delete_Card(Machine.cards.Pile_Card_Total->next->card_info.single_card_number);
			}
			Machine.round_discard_phase = false;
			new_round = true;
			turn = 1;
			return;
		}
	}

}