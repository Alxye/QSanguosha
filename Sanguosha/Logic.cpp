#include "Game.h"
void Game::Logic() {
	if (new_round) Round_Initialize(turn);     // where exist new round ,there a turn to judge & initialize player's data
	if (!animator_running) {
		if(!Human.die && (exturn == normal||exturn==human)) Human_Round();
		if(!Machine.die && (exturn == normal || exturn == machine_1)) Machine_Round();
		//if(!Machine.die && (exturn == normal || exturn == machine_2)) Machine_Round();
		//if(!Machine.die && (exturn == normal || exturn == machine_3)) Machine_Round();
	}
	// gameover state judgment
	if (Human.die && !Machine.die) { 
		cout << "machine win!!!" << endl;
		cout << "machine win!!!" << endl;
		cout << "machine win!!!" << endl;
		cout << "machine win!!!" << endl;
		gameover = true;
		gamequit = true;
	}
	else if (Machine.die && !Human.die) {
		cout << "human win!!!" << endl;
		cout << "human win!!!" << endl;
		cout << "human win!!!" << endl;
		cout << "human win!!!" << endl;
		gameover = true;
		gamequit = true;
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