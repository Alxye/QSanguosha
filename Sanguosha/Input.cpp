#include "Game.h"

void Game::Input_Globe() {
	cout << "so>?" << endl;
}

Vector2i Game::Input() {
	//Event event_global;
	while (window.pollEvent(event_global)) {
		// globe quit for console game
		if (event_global.type == Event::Closed) {
			window.close();
			gamequit = true;
		}

		// when game begin yet is showing the main menu
		if (gamestart) {
			// change style
			if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::A) {
				change_bg = true;
			}
			if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::S) {
				gamestart = false;
				gamerun = true;
			}
			if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
				mouse_count_clock_two = Mouse::getPosition(window);
				if (mouse_count_clock_two.x > 570 && mouse_count_clock_two.x < (570 + 80) && mouse_count_clock_two.y > 50 && mouse_count_clock_two.y < (50 + 400)){ 
					gamestart_go.enable_down_button();
				}
				else if (mouse_count_clock_two.x > 470 && mouse_count_clock_two.x < (470+ 80) && mouse_count_clock_two.y > 90 && mouse_count_clock_two.y < (90 + 400)){
					gamestart_info.enable_down_button();
				}
				else if (mouse_count_clock_two.x > 370 && mouse_count_clock_two.x < (370 + 80) && mouse_count_clock_two.y > 130 && mouse_count_clock_two.y < (130 + 400))	{
					gamestart_quit.enable_down_button();
				}
			}
			if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
				mouse_count_clock_two = Mouse::getPosition(window);
				if (mouse_count_clock_two.x > 570 && mouse_count_clock_two.x < (570 + 80) && mouse_count_clock_two.y > 50 && mouse_count_clock_two.y < (50 + 400)) {
					gamestart_go.enable_diabled_button();
				}
				else if (mouse_count_clock_two.x > 470 && mouse_count_clock_two.x < (470 + 80) && mouse_count_clock_two.y > 90 && mouse_count_clock_two.y < (90 + 400)) {
					gamestart_info.enable_diabled_button();
				}
				else if (mouse_count_clock_two.x > 370 && mouse_count_clock_two.x < (370 + 80) && mouse_count_clock_two.y > 130 && mouse_count_clock_two.y < (130 + 400)) {
					gamestart_quit.enable_diabled_button();
				}
			}
			if (!gamestart_go.is_down && !gamestart_info.is_down && !gamestart_quit.is_down) {

				if (event_global.type == sf::Event::MouseMoved)
				{
					// control button of cancel in hover state
					if (event_global.mouseMove.x > 570 && event_global.mouseMove.x < (570 + 80) && event_global.mouseMove.y > 50 && event_global.mouseMove.y < (50 + 400))
					{
						if (gamestart_go.is_normal) button_animate_count = 0;
						gamestart_go.enable_hover_button();
					}
					else {
						gamestart_go.enable_normal_button();
					}
					// control button of assure
					if (event_global.mouseMove.x > 470 && event_global.mouseMove.x < (470 + 80) && event_global.mouseMove.y > 90 && event_global.mouseMove.y < (90 + 400))
					{
						if (gamestart_info.is_normal) button_animate_count = 0;
						gamestart_info.enable_hover_button();
					}
					else {
						gamestart_info.enable_normal_button();
					}
					// control button of discard in hover state
					if (event_global.mouseMove.x > 370 && event_global.mouseMove.x < (370 + 80) && event_global.mouseMove.y > 130 && event_global.mouseMove.y < (130 + 400))
					{
						if (gamestart_quit.is_normal) button_animate_count = 0;
						gamestart_quit.enable_hover_button();
					}
					else {
						gamestart_quit.enable_normal_button();
					}
				}
			}

		}
		// when begin to choose start game , choose game mode for double player or more
		if (gamechoose) {

		}
		// when game pause --only when game is running can it be enabled
		if (gamepause) {

		}
        // human operate of gameover
		if (gameover) {

		}

		if (gamerun) {
			// change image
			if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::A) {
				if (img_bg_number == 4) img_bg_number = 0;
				else img_bg_number++;
				change_bg = true;
			}

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
					//cout << "��갴��ȷ��" << endl;
				}
				else if (mouse_count_clock_two.x > 807 && mouse_count_clock_two.x < (807 + 61) && mouse_count_clock_two.y > 694 && mouse_count_clock_two.y < (694 + 73) && !button_cancel.is_disabled)
				{ // the button of cancel //(807, 604)++(61,75)  
					button_cancel.enable_down_button();
					//cout << "��갴��ȡ��" << endl;
				}
				else if (mouse_count_clock_two.x > 874 && mouse_count_clock_two.x < (874 + 33) && mouse_count_clock_two.y > 644 && mouse_count_clock_two.y < (644 + 81) && !button_discard.is_disabled)
				{ // the button of discard //(807, 604)++(61,75)  
					button_discard.enable_down_button();
					//cout << "��갴�½���" << endl;
				}

			}
			if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
				mouse_count_clock_one = Mouse::getPosition(window);
				//bool card_selected = Human.cards.Search_Card_Position(mouse_count_clock_one);
				mouse_click_timer.restart();
				return mouse_count_clock_one;
			}

			if (event_global.type == sf::Event::MouseMoved)
			{
				// control button of cancel in hover state
				if (!button_cancel.is_disabled) {
					if (event_global.mouseMove.x > 807 && event_global.mouseMove.x < (807 + 61) && event_global.mouseMove.y > 694 && event_global.mouseMove.y < (694 + 73))
					{ // the button of cancel //(807, 694)++(61,73)
						//cout << "new mouse x: " << event_global.mouseMove.x << endl;
						//cout << "new mouse y: " << event_global.mouseMove.y << endl;
						button_cancel.enable_hover_button();
						//cout << "���λ��ȡ����" << endl;
					}
					else {
						//cout << "new mouse x: " << event_global.mouseMove.x << endl;
						//cout << "new mouse y: " << event_global.mouseMove.y << endl;
						button_cancel.enable_normal_button();
						//cout << "��겻��ȡ����" << endl;
					}
				}
				// control button of assure
				if (!button_ok.is_disabled) {
					if (event_global.mouseMove.x > 807 && event_global.mouseMove.x < (807 + 61) && event_global.mouseMove.y > 604 && event_global.mouseMove.y < (604 + 75))
					{ // the button of ok //(807, 604)++(61,75)
						//cout << "new mouse x: " << event_global.mouseMove.x << endl;
						//cout << "new mouse y: " << event_global.mouseMove.y << endl;
						button_ok.enable_hover_button();
						//cout << "���λ��ȷ����" << endl;
						//return virtual_vector;
					}
					else {
						//cout << "new mouse x: " << event_global.mouseMove.x << endl;
						//cout << "new mouse y: " << event_global.mouseMove.y << endl;
						button_ok.enable_normal_button();
						//cout << "��겻��ȷ����" << endl;
					}
				}
				// control button of discard in hover state
				if (!button_discard.is_disabled) {
					if (event_global.mouseMove.x > 874 && event_global.mouseMove.x < (874 + 33) && event_global.mouseMove.y > 644 && event_global.mouseMove.y < (644 + 81))
					{ // the button of ok //(874, 644)++(33,81)
						//cout << "new mouse x: " << event_global.mouseMove.x << endl;
						//cout << "new mouse y: " << event_global.mouseMove.y << endl;
						button_discard.enable_hover_button();
						//cout << "���λ�ڽ�����" << endl;
					}
					else {
						//cout << "new mouse x: " << event_global.mouseMove.x << endl;
						//cout << "new mouse y: " << event_global.mouseMove.y << endl;
						button_discard.enable_normal_button();
						//cout << "��겻�ڽ�����" << endl;
					}
				}
			}

		}
	}
}
