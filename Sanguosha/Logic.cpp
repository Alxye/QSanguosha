#include "Game.h"
void Game::Logic() {
	if (new_round) Round_Initialize(turn);     // where exist new round ,there a turn to judge & initialize player's data
	if (!animator_running) {
		if(!Human.die && (exturn == normal||exturn==human)) Human_Round();
		if (!Machine[0].die && (exturn == normal || exturn == machine_0)) Machine_Round(Machine[0]);
		if (!Machine[1].die && (exturn == normal || exturn == machine_1)) Machine_Round(Machine[1]);
		if (!Machine[2].die && (exturn == normal || exturn == machine_2)) Machine_Round(Machine[2]);
		if (!Machine[3].die && (exturn == normal || exturn == machine_3)) Machine_Round(Machine[3]);
	}
	// gameover state judgment ===>> that need to be improved
	if (Human.die) { 
		cout << "machine win!!!" << endl;
		cout << "machine win!!!" << endl;
		cout << "machine win!!!" << endl;
		cout << "machine win!!!" << endl;
		gameover = true;
		gamequit = true;
	}
	else  {
		cout << "human win!!!" << endl;
		cout << "human win!!!" << endl;
		cout << "human win!!!" << endl;
		cout << "human win!!!" << endl;
		gameover = true;
		gamequit = true;
	}
}

void Game::Round_Initialize(int &turn) { // about turn :  0！！machine || 1！！Human player
	switch (turn)
	{
	case human:          // humans round
		Human.round_draw_phase = true;
		Human.round_play_phase = true;
	    break;
	case machine_0:      // machine's round--->0		
		Machine[0].round_draw_phase = true;
		Machine[0].round_play_phase = true;
		break;
	case machine_1:      // machine's round--->1	
		Machine[1].round_draw_phase = true;
		Machine[1].round_play_phase = true;
		break;
	case machine_2:      // machine's round--->2		
		Machine[2].round_draw_phase = true;
		Machine[2].round_play_phase = true;
		break;
	case machine_3:      // machine's round--->3		
		Machine[3].round_draw_phase = true;
		Machine[3].round_play_phase = true;
		break;
	default:
		break;
	}
	new_round = false;
}