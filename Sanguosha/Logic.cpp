#include "Game.h"
void Game::Logic() {
	if (new_round) Round_Initialize(turn);     // where exist new round ,there a turn to judge & initialize player's data
	if (!animator_running) {
		Human_Round();
		Machine_Round();
	}
}

int Game::Previous_Draw_Phase() {
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

void Game::Round_Initialize(int turn) { // about turn :  0！！machine || 1！！Human player
	if (turn == 0) {  // machine's round
		Machine.round_draw_phase = true;
		Machine.round_play_phase = true;
	}
	else if (turn == 1) { // humans round
		Human.round_draw_phase = true;
		Human.round_play_phase = true;
	}
	new_round = false;
}