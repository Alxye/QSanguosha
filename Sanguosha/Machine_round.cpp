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
		return 0;
	}
	if (Machine.skill.need_peach) {
		if (Machine.HP < Machine.limited_HP) Machine.HP++;
		Machine.skill.need_peach = false;
	}
	if (Machine.skill.begging_peach) {
		if (Machine.cards.Search_Card(peach)) {
			Human.skill.need_peach = true;
			Machine.cards.Delete_Card(peach);
			cout << "机器给了一个桃！" << endl;
		}
		Machine.skill.begging_peach = false;
		return 0;
	}
	return 1;
}

void Game::Machine_Round() {

	Machine_Round_Initialize();
	if (Machine_Round_Skill_Judgment() == 0) return;

	if (Machine.round_play_phase && human_defense == false && Human.self_save == false) {

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
				human_defense = true;
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