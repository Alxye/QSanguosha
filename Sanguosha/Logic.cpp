#include "Game.h"
void Game::Logic() {

	if (gamestart) {
		if (gamestart_go.is_disabled) {
			gamechoose = true;
			gamestart = false;

			// restore attributes
			gamestart_go.enable_normal_button();
			gamestart_info.enable_normal_button();
			gamestart_quit.enable_normal_button();

			return;
		}
		else if (gamestart_info.is_disabled) {
			gameinfo = true;
			gamestart = false;

			// restore attributes
			gamestart_go.enable_normal_button();
			gamestart_info.enable_normal_button();
			gamestart_quit.enable_normal_button();

			return;
		}
		else if (gamestart_quit.is_disabled) {
			gamestart = false;
			gamequit = true;
			restart = true;
		}
	}
	
	if (gameinfo) {
		if (return_button.is_disabled) {
			gameinfo = false;
			if (message_amount) gamepause = true;
			else gamestart = true;

			// Restore attributes
			return_button.enable_normal_button();
			gameinfo_thanks.enable_normal_button();
			gameinfo_gameinfo.enable_normal_button();
			gameinfo_phaseinfo.enable_normal_button();
			gameinfo_cardinfo.enable_normal_button();

			return;
		}
	}

	if (gamechoose) {
		if (return_button.is_disabled) {
			gamechoose = false;
			gamestart = true;

			// Restore attributes
			return_button.enable_normal_button();
			button_gamechoose.enable_normal_button();

			return;
		}
		else if (button_gamechoose.is_down) {

			gamechoose = false;
			gamerun = true;
			restart = false;
			// set new data

	        // for original round
			new_round = true;
			// extra turn initialize
			exturn = normal;
			exturn_backup = exturn;
			// record who set signal of begging peach
			peach_begger = -1; // default no one beg for peach
			// get cards shuffled (originally)

			// get all card to pile card
			Single_Card* ptr = discard_pile.Pile_Card_Total->next;
			while (ptr) {
				ptr = ptr->next;
				int card_number;
				card_number = discard_pile.Pile_Card_Total->next->card_info.single_card_number;
				discard_pile.Delete_Card(card_number);
				piles.Insert_Card(card_number, rand() % 4);
			}
            
			// clear all player's card
			Human.cards.clear();
			for (int i = 0; i < 4; i++) Machine[i].cards.clear();

			// insert message of sending signal of game start
			Insert_Message(L"         ��  ��Ϸ��ʼ ��");


			switch (machine_number)
			{
			case 1:
				Human.HP = 2;
				Human.limited_HP = 2;
				// for machine-0
				Machine[0].location_one.x = window_width * 2 / 5;
				Machine[0].location_one.y = window_height / 15;
				Machine[0].location_two.x = Machine[0].location_one.x + 142;
				Machine[0].location_two.y = Machine[0].location_one.y + 195;
				break;
			case 2:
				Human.HP = 2;
				Human.limited_HP = 2;
				// for machine-0
				Machine[0].location_one.x = 290;
				Machine[0].location_one.y = 36;
				Machine[0].location_two.x = Machine[0].location_one.x + 142;
				Machine[0].location_two.y = Machine[0].location_one.y + 195;
				// for machine-1
				Machine[1].location_one.x = 550;
				Machine[1].location_one.y = 36;
				Machine[1].location_two.x = Machine[1].location_one.x + 142;
				Machine[1].location_two.y = Machine[1].location_one.y + 195;
				break;
			case 3:
				Human.HP = 3;
				Human.limited_HP = 3;
				// for machine-0
				Machine[0].location_one.x = 100;
				Machine[0].location_one.y = 300;
				Machine[0].location_two.x = Machine[0].location_one.x + 142;
				Machine[0].location_two.y = Machine[0].location_one.y + 195;
				// for machine-1
				Machine[1].location_one.x = window_width * 2 / 5;
				Machine[1].location_one.y = window_height / 15;
				Machine[1].location_two.x = Machine[1].location_one.x + 142;
				Machine[1].location_two.y = Machine[1].location_one.y + 195;
				// for machine-2
				Machine[2].location_one.x = 750;
				Machine[2].location_one.y = 300;
				Machine[2].location_two.x = Machine[2].location_one.x + 142;
				Machine[2].location_two.y = Machine[2].location_one.y + 195;
				break;
			case 4:
				Human.HP = 4;
				Human.limited_HP = 4;
				// for machine-0
				Machine[0].location_one.x = 100;
				Machine[0].location_one.y = 300;
				Machine[0].location_two.x = Machine[0].location_one.x + 142;
				Machine[0].location_two.y = Machine[0].location_one.y + 195;
				// for machine-1
				Machine[1].location_one.x = 290;
				Machine[1].location_one.y = 36;
				Machine[1].location_two.x = Machine[1].location_one.x + 142;
				Machine[1].location_two.y = Machine[1].location_one.y + 195;
				// for machine-2
				Machine[2].location_one.x = 550;
				Machine[2].location_one.y = 36;
				Machine[2].location_two.x = Machine[2].location_one.x + 142;
				Machine[2].location_two.y = Machine[2].location_one.y + 195;
				// for machine-3
				Machine[3].location_one.x = 750;
				Machine[3].location_one.y = 300;
				Machine[3].location_two.x = Machine[3].location_one.x + 142;
				Machine[3].location_two.y = Machine[3].location_one.y + 195;
				break;
			default:
				break;
			}
			//---->> initialize pile card
			turn = Previous_Draw_Phase();            // first round is effected in initial function , then it goes a loop
			exturn = normal;                         // original set is mean normal 
			//---->> initialize killing number
			Human.killing_number = 0;
			Machine[0].killing_number = 0;
			Machine[1].killing_number = 0;
			Machine[2].killing_number = 0;
			Machine[3].killing_number = 0;

			// Restore attributes
			return_button.enable_normal_button();
			button_gamechoose.enable_normal_button();

			return;
		}
	}

	if (gamerun) {
		if (pause_button.is_disabled) {
			gamerun = false;
			gamepause = true;

			// Restore attributes
			pause_button.enable_normal_button();

			return;
		}

		if (new_round) Round_Initialize(turn);     // where exist new round ,there a turn to judge & initialize player's data
		if (!animator_running && (exturn == normal || exturn == human)) Human_Round();
		switch (machine_number)
		{
		case 1:
			if (!animator_running && (exturn == normal || exturn == machine_0)) Machine_Round(Machine[0]);
			break;
		case 2:
			if (!animator_running && (exturn == normal || exturn == machine_0)) Machine_Round(Machine[0]);
			if (!animator_running && (exturn == normal || exturn == machine_1)) Machine_Round(Machine[1]);
			break;
		case 3:
			if (!animator_running && (exturn == normal || exturn == machine_0)) Machine_Round(Machine[0]);
			if (!animator_running && (exturn == normal || exturn == machine_1)) Machine_Round(Machine[1]);
			if (!animator_running && (exturn == normal || exturn == machine_2)) Machine_Round(Machine[2]);
			break;
		case 4:
			if (!animator_running && (exturn == normal || exturn == machine_0)) Machine_Round(Machine[0]);
			if (!animator_running && (exturn == normal || exturn == machine_1)) Machine_Round(Machine[1]);
			if (!animator_running && (exturn == normal || exturn == machine_2)) Machine_Round(Machine[2]);
			if (!animator_running && (exturn == normal || exturn == machine_3))	Machine_Round(Machine[3]);
			break;
		}
		// gameover state judgment
		if (Human.die) {
			if (Human.killing_number > Machine[0].killing_number &&
				Human.killing_number > Machine[1].killing_number &&
				Human.killing_number > Machine[2].killing_number &&
				Human.killing_number > Machine[3].killing_number) {
				gameover_state = 1;       // human win 
			}
			else gameover_state = 0;
			gameover = true;
			gamerun = false;
		}
	}

	if (gamepause) {
		if (pause_continue.is_disabled) {
			gamepause = false;
			gamerun = true;

			// restore attributes
			pause_continue.enable_normal_button();
			pause_info.enable_normal_button();
			pause_return_menu.enable_normal_button();

			return;
		}
		else if (pause_info.is_disabled) {
			gamepause = false;
			gameinfo = true;

			// restore attributes
			pause_continue.enable_normal_button();
			pause_info.enable_normal_button();
			pause_return_menu.enable_normal_button();

			return;
		}
		else if (pause_return_menu.is_disabled) {
			gamepause = false;
			restart = true;
		}
	}

	if (gameover) {
		if (return_menu.is_disabled) {

			gameover = false;
			gamestart = true;
			restart = true;
			gameover_state = -1;

			// Restore attributes
			return_menu.enable_normal_button();

			return;
		}
	}
}

void Game::Round_Initialize(int &turn) {
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